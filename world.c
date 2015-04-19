#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geomesh.c"

#include "noise.c"


// CHOOSE YOUR OWN PERSPECTIVE
//
// 0: first person perspective, X Y movement
// 1: polar, focus on origin, Y radius
// 2: orthographic from above, X Y panning
static int PERSPECTIVE = 0;


// size of window in OS
static int windowWidth = 800;
static int windowHeight = 400;


// INPUT HANDLING
static unsigned int UP_PRESSED = 0;    // KEY UP:0   KEY DOWN:1
static unsigned int DOWN_PRESSED = 0;
static unsigned int RIGHT_PRESSED = 0;
static unsigned int LEFT_PRESSED = 0;
static int mouseDragOffsetX = 0;  // how far mouse is dragged during one session (between click and release)
static int mouseDragOffsetY = 0;
static int mouseTotalOffsetX = 0;  // how far mouse has been dragged since program began
static int mouseTotalOffsetY = 0;
// helpers
static int mouseDragStartX = 0;
static int mouseDragStartY = 0;
static int mouseTotalOffsetStartX = 0;
static int mouseTotalOffsetStartY = 0;


#define STEP .10f  // WALKING SPEED. @60fps, walk speed = 6 units/second

// PERSPECTIVES
// FIRST PERSON PERSPECTIVE USING KEYBOARD (WASD), MOUSE (LOOK)
static float walkX = 0.0f;
static float walkY = 0.0f;
// POLAR PERSPECTIVE
static float cameraRadius = 15.0f;
// ORTHOGRAPHIC
static float panX = 0.0f;
static float panY = 0.0f;


// LIGHTING
static GLfloat light_position1[] = { 5.0, 5.0, 5.0, 0.0 };
static GLfloat light_position2[] = { -5.0, 5.0, -5.0, 0.0 };
static GLfloat light_position3[] = { -5.0, -5.0, 5.0, 0.0 };
static GLfloat std_light_pos[] = {0.0, 0.0, 5.0, 0.0};

geodesic g;
geomeshTriangles m;

#define frand() ((double) rand() / (RAND_MAX+1.0))
#define NUM_SOLIDS 100
float objcts[3*NUM_SOLIDS];
unsigned short objctsType[NUM_SOLIDS];

void initRender(){
	for(int i = 0; i < NUM_SOLIDS; i++){
		objcts[0+i*3] = frand()*30-15;
		objcts[1+i*3] = frand()*100-50;
		objcts[2+i*3] = frand()*30-15;
		objctsType[i] = rand()%3;
	}

	// for(int i = 0; i < ICOSAHEDRON_FACES; i++){
	// 	printf("(%.2f, %.2f, %.2f)\n",_icosahedron_points[i*3],_icosahedron_points[i*3+1],_icosahedron_points[i*3+2]);
	// }
	for(int i = 0; i < ICOSAHEDRON_FACES; i++){
		printf("(%d %d %d)  (%.2f, %.2f, %.2f) (%.2f, %.2f, %.2f) (%.2f, %.2f, %.2f)\n",
			_icosahedron_faces[i*3+0],
			_icosahedron_faces[i*3+1],
			_icosahedron_faces[i*3+2],

			_icosahedron_points[_icosahedron_faces[i*3+0]*3+0],
			_icosahedron_points[_icosahedron_faces[i*3+0]*3+1],
			_icosahedron_points[_icosahedron_faces[i*3+0]*3+2],
			_icosahedron_points[_icosahedron_faces[i*3+1]*3+0],
			_icosahedron_points[_icosahedron_faces[i*3+1]*3+1],
			_icosahedron_points[_icosahedron_faces[i*3+1]*3+2],
			_icosahedron_points[_icosahedron_faces[i*3+2]*3+0],
			_icosahedron_points[_icosahedron_faces[i*3+2]*3+1],
			_icosahedron_points[_icosahedron_faces[i*3+2]*3+2]
			);
	}

	g = icosahedron(3);
	m = makeMeshTriangles(&g, .8);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 5.0 };
	GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, green);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	// glShadeModel(GL_FLAT);
	glShadeModel (GL_SMOOTH);

}


// void init(){
// 	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
// 	glShadeModel(GL_FLAT);
// }

void reshape(int w, int h){
	float a = (float)windowWidth / windowHeight;
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(PERSPECTIVE == 0 || PERSPECTIVE == 1)
		glFrustum (-.1, .1, -.1/a, .1/a, .1, 100.0);
	else if (PERSPECTIVE == 2)
		glOrtho(-20.0f, 20.0f, 
				-20.0f/a, 20.0f/a, 
				-100.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// draws a XY 1x1 square in the Z = 0 plane
void unitSquare(float x, float y, float width, float height){
	static const GLfloat _unit_square_vertex[] = { -0.5f, 0.5f, 0.0f,     0.5f, 0.5f, 0.0f,    -0.5f, -0.5f, 0.0f,    0.5f, -0.5f, 0.0f };
	static const GLfloat _unit_square_normals[] = { 0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f  };
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(width, height, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _unit_square_vertex);
	glNormalPointer(GL_FLOAT, 0, _unit_square_normals);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
		// apply perspective inside this matrix
		if(PERSPECTIVE == 0){
			glRotatef(mouseTotalOffsetY, -1, 0, 0);
			glRotatef(mouseTotalOffsetX, 0, 0, -1);
			glTranslatef(walkX, walkY, 0);
		}
		if(PERSPECTIVE == 1){
			glTranslatef(0, 0, -cameraRadius);
			glRotatef(mouseTotalOffsetY, -1, 0, 0);
			glRotatef(mouseTotalOffsetX, 0, 0, -1);
		}
		if(PERSPECTIVE == 2){
			glTranslatef(-mouseTotalOffsetX * .05 - panX*2, mouseTotalOffsetY * .05 - panY*2, 0.0f);
		}

		// perspective has been established
		// draw stuff below

		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -1.0f);
			int XOffset = 0;
			int ZOffset = 0;
			if(PERSPECTIVE == 0){
				XOffset = walkX;  // math.floor
				ZOffset = walkY;
			}
			for(int i = -8; i <= 8; i++){
				for(int j = -8; j <= 8; j++){
					int b = abs(((i+j+XOffset+ZOffset)%2));
					if(b) glColor3f(0.0, 0.0, 0.0);
					else glColor3f(1.0, 1.0, 1.0);
					unitSquare(i-XOffset, j-ZOffset, 1, 1);
				}
			}
		glPopMatrix();


	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float dist = 2;
	static float step1, step2, step3, step4, step5, step6;
	step1 += .0055;
	step2 += .0045;
	step3 += .00711;
	step4 += .00666;
	step5 += .0049;
	step6 += .00821;
	glPushMatrix();
		float x, y, z;
		// x = cos(-mouseRotationX / 180) * cos(-mouseRotationY / 180);
		// z = sin(-mouseRotationX / 180) * cos(-mouseRotationY / 180);
		// y = sin(-mouseRotationY / 180);
		// gluLookAt(	x*dist, y*dist, z*dist,
		// 			0.0f, 0.0f, 0.0f,
		// 			0.0f, 1.0f, 0.0f);
		glPushMatrix();
			mouseTotalOffsetX = noise1(step1*.75+10)*360;
			mouseTotalOffsetY = noise1(step6*.75)*360;

			glTranslatef(0.0, 0.0, -3.0);
   			glRotatef(mouseTotalOffsetY, -1, 0, 0);
	    	glRotatef(mouseTotalOffsetX, 0, -1, 0);
	    	glPushMatrix();
	    		static float lightRotate = 0.0f;
	    		lightRotate += 1.0;
	    		glRotatef(lightRotate, 0.11111, 0.3, 1.0);
	    		glPushMatrix();
					glRotatef(360*noise1(step1), 0.0, 1.0, 0.0);
					glRotatef(360*noise1(step2), 1.0, 0.0, 0.0);
					glRotatef(360*noise1(step3), 0.0, 0.0, 1.0);
					glLightfv(GL_LIGHT0, GL_POSITION, std_light_pos);
	    		glPopMatrix();
	    		glPushMatrix();
					glRotatef(360*noise1(step2), 0.0, 1.0, 0.0);
					glRotatef(360*noise1(step3), 1.0, 0.0, 0.0);
					glRotatef(360*noise1(step4), 0.0, 0.0, 1.0);
					glLightfv(GL_LIGHT1, GL_POSITION, std_light_pos);
	    		glPopMatrix();
	    		glPushMatrix();
					glRotatef(360*noise1(step4), 0.0, 1.0, 0.0);
					glRotatef(360*noise1(step5), 1.0, 0.0, 0.0);
					glRotatef(360*noise1(step6), 0.0, 0.0, 1.0);
					glLightfv(GL_LIGHT2, GL_POSITION, std_light_pos);
	    		glPopMatrix();
				// glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
				// glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
				// glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
			glPopMatrix();
			// glEnable(GL_LIGHTING);
			// geodesicDrawTriangles(&g);
			// glDisable(GL_LIGHTING);
			// glColor4f(0.0, 0.0, 0.0);
			// geodesicDrawLines(&g);
	for(int i = 0; i < NUM_SOLIDS; i++){
		glPushMatrix();
			glTranslatef(objcts[i*3+0], objcts[i*3+1], objcts[i*3+2]);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// glColor3f(0.5f, 1.0f, 0.5f);
			// glNormalPointer(GL_FLOAT, 0, g.pointNormals);
			if(objctsType[i] == 0){
				glVertexPointer(3, GL_FLOAT, 0, _tetrahedron_points);
				glNormalPointer(GL_FLOAT, 0, _tetrahedron_points);
				glDrawElements(GL_TRIANGLES, 3*TETRAHEDRON_FACES, GL_UNSIGNED_SHORT, _tetrahedron_faces);
			}
			else if(objctsType[i] == 1){
				glVertexPointer(3, GL_FLOAT, 0, _octahedron_points);
				glNormalPointer(GL_FLOAT, 0, _octahedron_points);
				glDrawElements(GL_TRIANGLES, 3*OCTAHEDRON_FACES, GL_UNSIGNED_SHORT, _octahedron_faces);
			}
			if(objctsType[i] == 2){
				glVertexPointer(3, GL_FLOAT, 0, _icosahedron_points);
				glNormalPointer(GL_FLOAT, 0, _icosahedron_points);
				glDrawElements(GL_TRIANGLES, 3*ICOSAHEDRON_FACES, GL_UNSIGNED_SHORT, _icosahedron_faces);
			}
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	geodesicDrawTriangles(&g);
	glEnable(GL_LIGHTING);

	    	glRotatef(noise1(step1)*360, 0, 1, 0);
	    	glRotatef(noise1(step3)*360, 1, 0, 0);
	    	glRotatef(noise1(step5)*360, 0, 0, 1);

			geodesicMeshDrawExtrudedTriangles(&m);

			// glPushMatrix();
				// glEnableClientState(GL_VERTEX_ARRAY);
				// glEnableClientState(GL_NORMAL_ARRAY);
				// // glColor3f(0.5f, 1.0f, 0.5f);
				// glVertexPointer(3, GL_FLOAT, 0, _icosahedron_points);
				// glNormalPointer(GL_FLOAT, 0, g.pointNormals);
				// glDrawElements(GL_TRIANGLES, 3*ICOSAHEDRON_FACES, GL_UNSIGNED_SHORT, _icosahedron_faces);
				// glDisableClientState(GL_NORMAL_ARRAY);
				// glDisableClientState(GL_VERTEX_ARRAY);
			// glPopMatrix();

		glPopMatrix();
	glPopMatrix();



	glPopMatrix();
	// bring back buffer to the front on vertical refresh, auto-calls glFlush
	glutSwapBuffers();
	// glFlush();

	/////////////////////////
	// THIS WAS IN A UPDATE FUNCION
	for(int i = 0; i < NUM_SOLIDS; i++){
		objcts[i*3+1] -= .45;//33;
		if(objcts[i*3+1] < -50.0)
			objcts[i*3+1] += 100.0;
	}

}

// process input devices if in polar perspective mode
void updateOrthographic(){
	if(UP_PRESSED)
		panY -= STEP;
	if(DOWN_PRESSED)
		panY += STEP;
	if(LEFT_PRESSED)
		panX -= STEP;
	if(RIGHT_PRESSED)
		panX += STEP;
	// reshape(windowWidth, windowHeight);
	glutPostRedisplay();
}

// process input devices if in polar perspective mode
void updatePolar(){
	if(UP_PRESSED)
		cameraRadius -= STEP;
	if(DOWN_PRESSED)
		cameraRadius += STEP;
	if(cameraRadius < 0) 
		cameraRadius = 0;
	glutPostRedisplay();
}

// process input devices if in first person perspective mode
void updateFirstPerson(){
	// map movement direction to the direction the person is facing
	float lookAzimuth = 0;
	float mouseAzimuth = mouseTotalOffsetX/180.*M_PI;    
	lookAzimuth += mouseAzimuth;
	if(UP_PRESSED){
		float x = STEP * sinf(lookAzimuth);
		float y = STEP * -cosf(lookAzimuth);
		walkX += x;
		walkY += y;
	}
	if(DOWN_PRESSED){
		float x = STEP * sinf(lookAzimuth);
		float y = STEP * -cosf(lookAzimuth);
		walkX -= x;
		walkY -= y;
	}
	if(LEFT_PRESSED){
		float x = STEP * sinf(lookAzimuth+M_PI_2);
		float y = STEP * -cosf(lookAzimuth+M_PI_2);
		walkX -= x;
		walkY -= y;
	}
	if(RIGHT_PRESSED){
		float x = STEP * sinf(lookAzimuth+M_PI_2);
		float y = STEP * -cosf(lookAzimuth+M_PI_2);
		walkX += x;
		walkY += y;
	}
	glutPostRedisplay();
}

// when mouse button state changes
void mouseButtons(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(!state){  // button down
			mouseDragStartX = x;
			mouseDragStartY = y;
			mouseTotalOffsetStartX = mouseTotalOffsetX;
			mouseTotalOffsetStartY = mouseTotalOffsetY;
		}
		else { }    // button up
	}
	// else if(button == GLUT_MIDDLE_BUTTON){}
	// else if(button == GLUT_RIGHT_BUTTON){}
}

// when mouse is dragging screen
void mouseMotion(int x, int y){
	mouseDragOffsetX = mouseDragStartX - x;
	mouseDragOffsetY = mouseDragStartY - y;
	mouseTotalOffsetX = mouseTotalOffsetStartX + mouseDragOffsetX;
	mouseTotalOffsetY = mouseTotalOffsetStartY + mouseDragOffsetY;
	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y){
	switch (key){
		case 27:  // ESCAPE key
			exit (0);
			break;

		// W A S D
		case 119:  // W
			UP_PRESSED = 1;
			break;
		case 115:  // S
			DOWN_PRESSED = 1;
			break;
		case 97:   // A
			RIGHT_PRESSED = 1;
			break;
		case 100:  // D
			LEFT_PRESSED = 1;
			break;
		case '1':
			PERSPECTIVE = 0;
			// mouseTotalOffsetX = mouseTotalOffsetY = 0;
			reshape(windowWidth, windowHeight);
			glutPostRedisplay();
			break;
		case '2':
			PERSPECTIVE = 1;
			// mouseTotalOffsetX = mouseTotalOffsetY = 0;
			reshape(windowWidth, windowHeight);
			glutPostRedisplay();
			break;
		case '3':
			PERSPECTIVE = 2;
			mouseTotalOffsetX = mouseTotalOffsetY = 0;
			reshape(windowWidth, windowHeight);
			glutPostRedisplay();
			break;
	}
	// anything that affects the screen and requires a redisplay
	// put it in this if statement
	if(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED){
		if(PERSPECTIVE == 0)
			glutIdleFunc(updateFirstPerson);
		if(PERSPECTIVE == 1)
			glutIdleFunc(updatePolar);
		if(PERSPECTIVE == 2)
			glutIdleFunc(updateOrthographic);
	}
}

void keyboardUp(unsigned char key,int x,int y){
	switch (key){
		case 119:  // W
			UP_PRESSED = 0;
			break;
		case 115:  // S
			DOWN_PRESSED = 0;
			break;
		case 97:   // A
			RIGHT_PRESSED = 0;
			break;
		case 100:  // D
			LEFT_PRESSED = 0;
			break;
	}
	if(!(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED))
		glutIdleFunc(NULL);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow(argv[0]);
	initRender();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButtons);
	glutMotionFunc(mouseMotion);
	glutKeyboardUpFunc(keyboardUp); 
	glutKeyboardFunc(keyboardDown);
	glutPostRedisplay();
	glutMainLoop();
	return 0;
}