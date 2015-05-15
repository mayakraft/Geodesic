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

// SCREEN
static int height = 400;
static int width = 400;
// KEYBOARD
static unsigned int UP_PRESSED = 0;
static unsigned int DOWN_PRESSED = 0;
static unsigned int RIGHT_PRESSED = 0;
static unsigned int LEFT_PRESSED = 0;
// MOUSE
static int mouseDownX = 0;
static int mouseDownY = 0;
static float mouseRotationX = 0.0f;
static float mouseRotationY = 0.0f;
static float startRotationX = 0.0f;
static float startRotationY = 0.0f;

// WALKING
#define STEP .10f;
static float xPos = 0.0f;
static float yPos = 0.0f;

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

void display(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
			mouseRotationX = noise1(step1*.75+10)*360;
			mouseRotationY = noise1(step6*.75)*360;

			glTranslatef(0.0, 0.0, -3.0);
   			glRotatef(mouseRotationY, -1, 0, 0);
	    	glRotatef(mouseRotationX, 0, -1, 0);
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
	glutSwapBuffers();
	// glFlush();
}

void update(){

	for(int i = 0; i < NUM_SOLIDS; i++){
		objcts[i*3+1] -= .45;//33;
		if(objcts[i*3+1] < -50.0)
			objcts[i*3+1] += 100.0;
	}

	// if(UP_PRESSED) xPos += STEP;
	// if(DOWN_PRESSED) xPos -= STEP;
	// if(RIGHT_PRESSED) yPos += STEP;
	// if(LEFT_PRESSED) yPos -= STEP;
    static const float M_PI_HALF = 1.5708f;

    float lookAzimuth = 0;
    float mouseAzimuth = mouseRotationX/180.*3.14159f-M_PI_HALF;
    
    lookAzimuth += mouseAzimuth;
    
    if(UP_PRESSED){
        float x =  sinf(lookAzimuth) * STEP;
        float y =  cosf(lookAzimuth) * STEP;
        xPos += x;
        yPos += y;
    }
    if(DOWN_PRESSED){
        float x = sinf(lookAzimuth) * STEP;
        float y =  cosf(lookAzimuth) * STEP;
        xPos -= x;
        yPos -= y;
    }
    if(LEFT_PRESSED){
        float x =  sinf(lookAzimuth+M_PI_HALF) * STEP;
        float y =  cosf(lookAzimuth+M_PI_HALF) * STEP;
        xPos -= x;
        yPos -= y;
    }
    if(RIGHT_PRESSED){
        float x =  sinf(lookAzimuth+M_PI_HALF) * STEP;
        float y = cosf(lookAzimuth+M_PI_HALF) * STEP;
        xPos += x;
        yPos += y;
    }
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)
				// glutIdleFunc(spinDisplay);
				mouseDownX = x;
				mouseDownY = y;
				startRotationX = mouseRotationX;
				startRotationY = mouseRotationY;
			break;
		default:
			break;
	}
}
void mouseMotion(int x, int y){
	mouseRotationX = startRotationX + mouseDownX - x;
	mouseRotationY = startRotationY + mouseDownY - y;
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
	switch (key){
		// ESCAPE key
		case 27:             exit (0);			break;
		case 119:
		case GLUT_KEY_UP:	 UP_PRESSED = 1;	break;
		case 115:
		case GLUT_KEY_DOWN:	 DOWN_PRESSED = 1;	break;
		case 97:
		case GLUT_KEY_RIGHT: RIGHT_PRESSED = 1;	break;
		// case 100:
		case GLUT_KEY_LEFT:	 LEFT_PRESSED = 1;	break;
		// case 't': 		 break;
	}
	// if(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED)
	// 	glutIdleFunc(update);
}

void keyboardUp(unsigned char key,int x,int y){
	switch (key){
		// ESCAPE key
		case 27:			 exit (0);			break;
		case 119:
		case GLUT_KEY_UP:	 UP_PRESSED = 0;	break;
		case 115:
		case GLUT_KEY_DOWN:	 DOWN_PRESSED = 0;	break;
		case 97:
		case GLUT_KEY_RIGHT: RIGHT_PRESSED = 0;	break;
		// case 100:
		case GLUT_KEY_LEFT:	 LEFT_PRESSED = 0;	break;
		// case 't':		 break;
	}
	// if(!(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED))
	// 	glutIdleFunc(NULL);
}

void reshape(int w, int h){
	float a = (float)width/height;
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-40.0, 40.0, -40/a, 40/a, -100.0, 100.0);
	glFrustum (-1.0, 1.0, -1.0/a, 1.0/a, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(width,height);
	glutCreateWindow(argv[0]);
	initRender();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(update);
	glutKeyboardUpFunc(keyboardUp); 
	glutKeyboardFunc(keyboard);
	glutPostRedisplay();
	glutMainLoop();
	return 0;
}