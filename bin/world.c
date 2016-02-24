#include "../OpenGL/mesh.c"
#include "../tween.c"
#include "world.h"

#define DELTA_TWEEN .05
#define frand() ((double) rand() / (RAND_MAX+1.0))

#define maxFrequency 6

unsigned int SCENE = 0;

// scene 1 objects
geodesicSphere geodesicV[12];
geodesicMeshTriangles mesh[12];
geodesicMeshNormals normalsV[12];

// scene 2 objects
geodesicSphere geo;
geodesicMeshTriangles m;
geodesicSphere geodesicV2, geodesicV3, geodesicV4;
geodesicMeshNormals normalsV2;
tween t;
geodesicDome domeV3, domeV8;
geodesicMeshTriangles domeMeshV3, domeMeshV8;
geodesicMeshCropPlanes planes;

//lighting
static GLfloat light_position1[] = { 5.0, 5.0, 5.0, 0.0 };
static GLfloat light_position2[] = { -5.0, 5.0, -5.0, 0.0 };
static GLfloat light_position3[] = { -5.0, -5.0, 5.0, 0.0 };
static GLfloat std_light_pos[] = {0.0, 0.0, 5.0, 0.0};

void setup(){
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GRID = 0;
	GROUND = 0;
	POV = POLAR;
	ZOOM = 6;

	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat green[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
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
	glShadeModel(GL_SMOOTH);
	glEnable( GL_POINT_SMOOTH );
	glLineWidth(3);
	glPointSize(6);

	glDisable(GL_LIGHTING);

	for(int i = 0; i < 12; i++){
		int v = i;
		if (v == 0) v = 1;
		geodesicV[i] = icosahedronSphere(v);
		normalsV[i] = makeMeshNormals(&geodesicV[i]);
		mesh[i] = makeMeshTriangles(&geodesicV[i], .8);
	}
	geo = icosahedronSphere(2);
	geodesicV2 = icosahedronSphere(2);
	geodesicV3 = icosahedronSphere(3);
	geodesicV4 = icosahedronSphere(4);
	normalsV2 = makeMeshNormals(&geodesicV2);
	m = makeMeshTriangles(&geo, .8);
	t = makeTween(geo.pointsNotSpherized, geo.pointsDeltaSpherized, geo.numPoints*3);
	domeV3 = icosahedronDome(3, .66);
	domeMeshV3 = makeMeshTriangles(&(domeV3.sphere), 0.85);
	planes = makeMeshCropPlanes(&domeV3);
	// domeV8 = octahedronDome(8, .8);
	// domeMeshV8 = makeMeshTriangles(&(domeV8.sphere), 0.85);
	domeV8 = icosahedronDome(8, .8);
	domeMeshV8 = makeMeshTriangles(&(domeV8.sphere), 0.85);


//	printf("Geodesic (%dv): %d points, %d lines, %d faces\n", g.frequency, g.numPoints, g.numLines, g.numFaces);
}

void switchScenes(){
	if(SCENE == 0){
		glDisable(GL_LIGHTING);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	}
	if(SCENE == 1){
		glEnable(GL_LIGHTING);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	}
}

float autoRotateX, autoRotateY;
static int count = 0;

void update(){
	count++;
	
	autoRotateX = count;

	// Math.easeInOutQuint = function (t, b, c, d) {
	// t /= d/2;
	// if (t < 1) return c/2*t*t*t*t*t + b;
	// t -= 2;
	// return c/2*(t*t*t*t*t + 2) + b;

	// autoRotateX = cos(count * .01) * 60;
	// autoRotateY = sin(count * .01) * 10;


	// scene 2 update
	static float tween = 0.0f;
	static float deltaTween = 0.0;
	static int count = 0;
	count++;
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
			deleteTween(&t);
			t = makeTween(geo.pointsNotSpherized, geo.pointsDeltaSpherized, geo.numPoints*3);
		}
		updateTween(&t, tween);
	}
}

void drawScene1(){
	glTranslatef(0, 0, -ZOOM - 14);

	glPushMatrix();

		glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
		glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
		glRotatef(-autoRotateY / 20.0, 1, 0, 0);
		glRotatef(-autoRotateX / 20.0, 0, 1, 0);
		glRotatef(-90, 0, 0, 1);

		glLineWidth(1);
		glPointSize(3);

		float alpha1 = sin(count/180.0 * M_PI) * .5 + .5;
		float alpha2 = -sin(count/180.0 * M_PI) * .5 + .5;

		glPushMatrix();
			glScalef(2.8, 2.8, 2.8);
			glColor4f(0.0, 0.0, 0.0, 0.05);
			drawGeodesicExtrudedTriangles(&mesh[5]);
		glPopMatrix();

		for(int i = 2; i < maxFrequency; i++){
			glPushMatrix();
				// glScalef(3 + i/50.0, 3 + i/50.0, 3 + i/50.0);
				glScalef(3, 3, 3);
				// glColor4f(0.0, 0.0, 0.0, 0.1 + powf(12 - i,2)/1000.0);
				glColor4f(0.0, 0.0, 0.0, 0.07);
				if(i == 3 || i == 6 || i == 9 || i == 12)
					glColor4f(0.0, 0.0, 0.0, 0.16);
				// drawGeodesicPoints(&geodesicV[i]);

				glLineWidth(1);
				drawGeodesicLines(&geodesicV[i]);
				// drawGeodesicFaces(&geodesicV[i]);

				glLineWidth(1);
				glColor4f(0.0, 0.0, 0.66, 0.15);
				drawGeodesicVertexNormalLines(&normalsV[i]);
				glColor4f(0.0, 0.66, 0.0, 0.15);
				drawGeodesicLineNormalLines(&normalsV[i]);
				glColor4f(0.66, 0.0, 0.0, 0.15);
				drawGeodesicFaceNormalLines(&normalsV[i]);
			glPopMatrix();
		}

		glLineWidth(1);
		glCullFace(GL_BACK);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPushMatrix();
			glScalef(2.95, 2.95, 2.95);
			drawPlatonicSolidFaces(3);
		glPopMatrix();
		glCullFace(GL_FRONT);

		glColor4f(0.0, 0.0, 0.0, 0.1);
		glPushMatrix();
			glScalef(3.9, 3.9, 3.9);
			drawPlatonicSolidLines(4);
		glPopMatrix();

		glLineWidth(8);
		glColor4f(0.0, 0.0, 0.0, 0.04);
		glPushMatrix();
			glScalef(3, 3, 3);
			drawPlatonicSolidLines(3);
		glPopMatrix();

		glLineWidth(4);
		glColor4f(0.0, 0.0, 0.0, 0.03);
		glPushMatrix();
			glScalef(3.01, 3.01, 3.01);
			drawPlatonicSolidLines(3);
		glPopMatrix();

		glLineWidth(1);
		glColor4f(0.0, 0.0, 0.0, 0.02);
		glPushMatrix();
			glScalef(3.02, 3.02, 3.02);
			drawPlatonicSolidLines(3);
		glPopMatrix();

		glLineWidth(2);
		glPushMatrix();
			glScalef(3, 3, 3);
			glColor4f(0.0, 0.0, 0.0, 0.3);
			drawGeodesicVertexNormalLines(&normalsV[2]);
			glColor4f(0.0, 0.0, 0.0, 0.3);
			drawGeodesicLineNormalLines(&normalsV[2]);
			glColor4f(0.0, 0.0, 0.0, 0.3);
			drawGeodesicFaceNormalLines(&normalsV[2]);
		glPopMatrix();

	glPopMatrix();
}

void drawScene2(){
	glTranslatef(0,0,-16);

	glPushMatrix();
		glTranslatef(0, 0, -ZOOM);
		glPushMatrix();
			static float lightRotate = 0.0f;
			lightRotate += 0.3;
			glRotatef(lightRotate / 80.0 * 180.0, 0.11111, 0.3, 1.0);
			glLightfv(GL_LIGHT0, GL_POSITION, std_light_pos);
			glLightfv(GL_LIGHT1, GL_POSITION, std_light_pos);
			glLightfv(GL_LIGHT2, GL_POSITION, std_light_pos);
			glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
			glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
			glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
		glPopMatrix();


		glShadeModel(GL_FLAT);
// TOP ROW
		glPushMatrix();
			glTranslatef(-3, 3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
			drawGeodesicPoints(&geodesicV3);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
			drawGeodesicLines(&geodesicV3);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(3, 3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
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
			glRotatef(-90, 0, 0, 1);
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
			glRotatef(-90, 0, 0, 1);

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);    
			glVertexPointer(3, GL_FLOAT, 0, t.data);
			glNormalPointer(GL_FLOAT, 0, geo.pointNormals);
			glDrawElements(GL_TRIANGLES, geo.numFaces*3, GL_UNSIGNED_SHORT, geo.faces);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix();

// BOTTOM ROW
		glPushMatrix();
			glTranslatef(-3, -3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glPushMatrix();
				glRotatef(-90, 0, 0, 1);
				drawGeodesicExtrudedTriangles(&m);
			glPopMatrix();
		
			glDisable(GL_LIGHTING);
			glDisable(GL_CULL_FACE);
			glColor3f(0.5, 0.5, 0.5);
			drawGeodesicCropPlanes(&planes);
			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, -3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
			drawDomeMeshTriangles(&domeV3, &domeMeshV3);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(3, -3, 0);
			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glRotatef(-90, 0, 0, 1);
			drawDomeMeshTriangles(&domeV8, &domeMeshV8);
		glPopMatrix();

	glPopMatrix();	
}

void draw(){
	if(SCENE == 0)
		drawScene1();
	if(SCENE == 1)
		drawScene2();
}

void keyDown(unsigned int key) {
	if(key == SPACE_BAR){
		SCENE = !SCENE;
		switchScenes();
	}
}
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }