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

// SCREEN
static int height = 400;
static int width = 800;
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

geodesic g;

void init(){

	g = icosahedron(2);

	glutInitDisplayMode (GLUT_DEPTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 5.0, 5.0, 5.0, 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
   		glRotatef(mouseRotationY, -1, 0, 0);
	    glRotatef(mouseRotationX, 0, -1, 0);

		glTranslatef(yPos, 0, -xPos);
		glPushMatrix();
			glTranslatef(0.0, 0.0, -3.0);
			geodesicDrawTriangles(&g);

			// glPushMatrix();
			// 	glEnableClientState(GL_VERTEX_ARRAY);
			// 	glColor3f(0.5f, 1.0f, 0.5f);
			// 	glVertexPointer(3, GL_FLOAT, 0, _icosahedron_points);
			// 	glDrawElements(GL_TRIANGLES, 3*ICOSAHEDRON_FACES, GL_UNSIGNED_SHORT, _icosahedron_faces);
			// 	glDisableClientState(GL_VERTEX_ARRAY);
			// glPopMatrix();

		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
	// glFlush();
}

void spinDisplay(void){
	static GLfloat spin = 0.0f;
	spin = spin - 2.0;
	if(spin > 360.0){
		spin = spin - 360.0;
	}
	glutPostRedisplay();
}

void update(){
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
	if(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED)
		glutIdleFunc(update);
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
	if(!(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED))
		glutIdleFunc(NULL);
}

void reshape(int w, int h){
	float a = (float)width/height;
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-40.0, 40.0, -40/a, 40/a, -100.0, 100.0);
	glFrustum (-1.0, 1.0, -1.0/a, 1.0/a, 1.5, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(width,height);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardUpFunc(keyboardUp); 
	glutKeyboardFunc(keyboard);
	glutPostRedisplay();
	glutMainLoop();
	return 0;
}