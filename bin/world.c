#include "../OpenGL/mesh.c"
#include "../noise.c"
#include "../tween.c"
#include "world.h"

//approx
#define DELTA_TWEEN .05

static unsigned char PAUSE = 0;

static GLfloat light_position1[] = { 5.0, 5.0, 5.0, 0.0 };
static GLfloat light_position2[] = { -5.0, 5.0, -5.0, 0.0 };
static GLfloat light_position3[] = { -5.0, -5.0, 5.0, 0.0 };
static GLfloat std_light_pos[] = {0.0, 0.0, 5.0, 0.0};

geodesicSphere geo;
geodesicMeshTriangles m;
tween t;
geodesicSphere geodesicV2, geodesicV3, geodesicV4;
geodesicMeshNormals normalsV2;

geodesicDome dome;
geodesicMeshCropPlanes planes;


float noiseRotateX, noiseRotateY;

#define frand() ((double) rand() / (RAND_MAX+1.0))

// float elapsedTime = 0;

void setup(){
	GRID = 0;
	GROUND = 0;
	POV = POLAR;
	ZOOM = 6;
	glPointSize(64);
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
	glLineWidth(3);
	glPointSize(6);
	glEnable(GL_LIGHTING);

	geo = icosahedronSphere(2);

	geodesicV2 = icosahedronSphere(2);
	geodesicV3 = icosahedronSphere(3);
	geodesicV4 = icosahedronSphere(4);

	normalsV2 = makeMeshNormals(&geodesicV2);

	m = makeMeshTriangles(&geo, .8);

	t = makeTween(geo.pointsNotSpherized, geo.pointsDeltaSpherized, geo.numPoints*3);

	dome = icosahedronDome(3, .8);

	planes = makeMeshCropPlanes(&dome);

//	printf("Geodesic (%dv): %d points, %d lines, %d faces\n", g.frequency, g.numPoints, g.numLines, g.numFaces);

}

void update(){

	static float tween = 0.0f;
	static float deltaTween = 0.0;

	static int count = 0;
	count++;

	// mouseDragSumX = cos(count / 80.0 * M_PI) * 8;
	// mouseDragSumY = sin(count / 80.0 * M_PI) * 8;

	if(count % 80 == 0){
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
			deleteTween(&t);
			t = makeTween(geo.pointsNotSpherized, geo.pointsDeltaSpherized, geo.numPoints*3);
		}
		updateTween(&t, tween);
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
	glTranslatef(0,0,-16);

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

// TOP ROW
		glPushMatrix();
			glTranslatef(-3, 3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			drawGeodesicPoints(&geodesicV3);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			drawGeodesicLines(&geodesicV3);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(3, 3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			drawGeodesicTriangles(&geodesicV3);
		glPopMatrix();

// MIDDLE ROW
		glPushMatrix();
			glTranslatef(-3, 0, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			drawGeodesicExtrudedTriangles(&m);
		glPopMatrix();

		glPushMatrix();
		glScalef(1.618, 1.618, 1.618);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			drawGeodesicLines(&geodesicV2);

			glDisable(GL_LIGHTING);
			glColor3f(1.0, 1.0, 1.0);
			drawGeodesicVertexNormalLines(&normalsV2);
			glColor3f(0.0, 1.0, 1.0);
			drawGeodesicLineNormalLines(&normalsV2);
			glColor3f(1.0, 0.0, 1.0);
			drawGeodesicFaceNormalLines(&normalsV2);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(3, 0, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);    
			glVertexPointer(3, GL_FLOAT, 0, t.data);
			glNormalPointer(GL_FLOAT, 0, geo.pointNormals);
			glDrawElements(GL_TRIANGLES, geo.numFaces*3, GL_UNSIGNED_SHORT, geo.faces);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix();

// BOTTOM ROW
		// glPushMatrix();
		// 	glTranslatef(-3, -3, 0);
		// 	glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
		// 	glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
		// 	drawDomeTriangles(&dome);			
		// glPopMatrix();

		glPushMatrix();
			glTranslatef(3, -3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			drawGeodesicExtrudedTriangles(&m);
			
			glDisable(GL_LIGHTING);
			glDisable(GL_CULL_FACE);
			glColor3f(0.5, 0.5, 0.5);
			drawGeodesicCropPlanes(&planes);
			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);
		glPopMatrix();

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