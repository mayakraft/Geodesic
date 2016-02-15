#include "../OpenGL/mesh.c"
#include "../noise.c"
#include "../tween.c"
#include "world.h"

//approx
#define CLOCKS_PER_SECOND 60000

#define DELTA_TWEEN .05

static unsigned char PAUSE = 0;


static GLfloat light_position1[] = { 5.0, 5.0, 5.0, 0.0 };
static GLfloat light_position2[] = { -5.0, 5.0, -5.0, 0.0 };
static GLfloat light_position3[] = { -5.0, -5.0, 5.0, 0.0 };
static GLfloat std_light_pos[] = {0.0, 0.0, 5.0, 0.0};

geodesicSphere geo[3];
geodesicMeshTriangles m[3];
tween t[3];
tween ext;

float noiseRotateX, noiseRotateY;

#define frand() ((double) rand() / (RAND_MAX+1.0))

// float elapsedTime = 0;

void setup(){
	GRID = 0;
	GROUND = 0;

	POV = POLAR;
	ZOOM = 6;
	glPointSize(64);
	// glLineWidth(5);
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 5.0f };
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat green[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, green);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	// glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glEnable( GL_POINT_SMOOTH );
	glLineWidth(5);
	glPointSize(10);

	glEnable(GL_LIGHTING);

	geo[0] = icosahedronSphere(2);
	geo[1] = icosahedronSphere(4);
	geo[2] = icosahedronSphere(12);
	m[0] = makeMeshTriangles(&geo[0], .8);
	m[1] = makeMeshTriangles(&geo[1], .8);
	m[2] = makeMeshTriangles(&geo[2], .8);
	t[0] = makeTween(geo[0].pointsNotSpherized, geo[0].pointsDeltaSpherized, geo[0].numPoints*3);
	t[1] = makeTween(geo[1].pointsNotSpherized, geo[1].pointsDeltaSpherized, geo[1].numPoints*3);
	t[2] = makeTween(geo[2].pointsNotSpherized, geo[2].pointsDeltaSpherized, geo[2].numPoints*3);
	// ext = makeTween(m.glTriangles, )
 //    unsigned int    numTriangles;
 //    float           *;

//	printf("Geodesic (%dv): %d points, %d lines, %d faces\n", g.frequency, g.numPoints, g.numLines, g.numFaces);

}

void update(){

	static float tween = 0.0f;
	static float deltaTween = 0.0;

	static int count = 0;
	count++;

	if(count % 120 == 0){
		if(tween == 1.0) deltaTween = -DELTA_TWEEN;
		else if(tween == 0.0) deltaTween = DELTA_TWEEN;
	}
	if(deltaTween != 0.0){
		tween += deltaTween;
		if(tween > 1.0){
			tween = 1.0;
			deltaTween = 0;
		}
		else if(tween < 0.0){
			tween = 0.0;
			deltaTween = 0;
			// deleteGeodesicSphere(&g);
			// g = icosahedronSphere(  ((int)pow(rand()%4+1,1.25))+ 1  );
			// for(int i = 0; i < g.numPoints; i++){
			// 	if(g.parentFace[i] >= 0){
			// 		// printf("%d (%d) %f\n", i, g.parentFace[i], g.faceNormals[g.parentFace[i]]);
			// 		g.pointNormals[i*3+0] = _dodecahedron_points[g.parentFace[i]*3+0];
			// 		g.pointNormals[i*3+1] = _dodecahedron_points[g.parentFace[i]*3+1];
			// 		g.pointNormals[i*3+2] = _dodecahedron_points[g.parentFace[i]*3+2];
			// 	}
			// }
			deleteTween(&t[0]);
			deleteTween(&t[1]);
			deleteTween(&t[2]);
			t[0] = makeTween(geo[0].pointsNotSpherized, geo[0].pointsDeltaSpherized, geo[0].numPoints*3);
			t[1] = makeTween(geo[1].pointsNotSpherized, geo[1].pointsDeltaSpherized, geo[1].numPoints*3);
			t[2] = makeTween(geo[2].pointsNotSpherized, geo[2].pointsDeltaSpherized, geo[2].numPoints*3);
		}
		updateTween(&t[0], tween);
		updateTween(&t[1], tween);
		updateTween(&t[2], tween);
	}
}

void draw(){
	static float step1, step2, step3, step4, step5, step6;
	step1 += .0055;
	step2 += .0045;
	step3 += .00711;
	step4 += .00666;
	step5 += .0049;
	step6 += .00821;

	glPushMatrix();
		glTranslatef(0, 0, -ZOOM);

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
			glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
			glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
			glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
		glPopMatrix();


		// glEnable(GL_LIGHTING);
		// geodesicDrawTriangles(&g);
		// glDisable(GL_LIGHTING);
		// glColor4f(0.0, 0.0, 0.0);
		// geodesicDrawLines(&g);

		// glDisable(GL_LIGHTING);
		// glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		// geodesicDrawTriangles(&g);
		// glEnable(GL_LIGHTING);


		// glPushMatrix();
		// 	glEnableClientState(GL_VERTEX_ARRAY);
		// 	glEnableClientState(GL_NORMAL_ARRAY);
		// 	// glColor3f(0.5f, 1.0f, 0.5f);
		// 	glVertexPointer(3, GL_FLOAT, 0, t.data);
		// 	glNormalPointer(GL_FLOAT, 0, g.pointNormals);
		// 	glDrawElements(GL_TRIANGLES, 3*ICOSAHEDRON_FACES, GL_UNSIGNED_SHORT, _icosahedron_faces);
		// 	glDisableClientState(GL_NORMAL_ARRAY);
		// 	glDisableClientState(GL_VERTEX_ARRAY);
		// glPopMatrix();

		glShadeModel(GL_FLAT);
		for(int i = 0; i < 3; i++){
			glPushMatrix();
				glTranslatef((i-1) * 3, 0.0, 0.0);
				glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
				glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 0, 1);

				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);    
				glVertexPointer(3, GL_FLOAT, 0, t[i].data);
				glNormalPointer(GL_FLOAT, 0, geo[i].pointNormals);
				glDrawElements(GL_TRIANGLES, geo[i].numFaces*3, GL_UNSIGNED_SHORT, geo[i].faces);
				glDisableClientState(GL_NORMAL_ARRAY);
				glDisableClientState(GL_VERTEX_ARRAY);
			glPopMatrix();
		}

		// geodesicDrawTriangles(&g);

		// glShadeModel(GL_FLAT);
		// geodesicDrawTriangles(&g);
		// geodesicMeshDrawExtrudedTriangles(&m);
		// glShadeModel (GL_SMOOTH);

	glPopMatrix();
}

void keyDown(unsigned int key) { }
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }