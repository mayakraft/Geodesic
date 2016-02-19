#include "../OpenGL/mesh.c"
#include "world.h"

#define DELTA_TWEEN .05
#define frand() ((double) rand() / (RAND_MAX+1.0))

// spheres
geodesicSphere ico;
geodesicSphere geodesicV[12];
geodesicMeshTriangles mesh[12];
geodesicMeshNormals normalsV[12];

// domes
geodesicDome domeV3, domeV8;
geodesicMeshTriangles domeMeshV3, domeMeshV8;
geodesicMeshCropPlanes planes;


void setup(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GRID = 0;
	GROUND = 0;
	POV = POLAR;
	ZOOM = 6;
	glPointSize(64);
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	// glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glEnable( GL_POINT_SMOOTH );

		glDisable(GL_LIGHTING);
	glLineWidth(3);
	glPointSize(6);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ico = icosahedronSphere(1);

	for(int i = 0; i < 12; i++){
		int v = i;
		if (v == 0) v = 1;
		geodesicV[i] = icosahedronSphere(v);
		normalsV[i] = makeMeshNormals(&geodesicV[i]);
		mesh[i] = makeMeshTriangles(&geodesicV[i], .8);
	}

	domeV3 = icosahedronDome(3, .66);
	domeMeshV3 = makeMeshTriangles(&(domeV3.sphere), 0.85);
	planes = makeMeshCropPlanes(&domeV3);

	// domeV8 = octahedronDome(8, .8);
	// domeMeshV8 = makeMeshTriangles(&(domeV8.sphere), 0.85);
	domeV8 = icosahedronDome(8, .8);
	domeMeshV8 = makeMeshTriangles(&(domeV8.sphere), 0.85);

//	printf("Geodesic (%dv): %d points, %d lines, %d faces\n", g.frequency, g.numPoints, g.numLines, g.numFaces);
}

float autoRotateX, autoRotateY;
static int count = 0;

void update(){
	count++;
	
	// autoRotateX = count;

	// autoRotateX = cos(count * .01) * 60;
	// autoRotateY = sin(count * .01) * 10;
}

void draw(){
	// glTranslatef(0,0,-16);
		glTranslatef(0, 0, -ZOOM - 12);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		for(int i = 2; i < 12; i++){
			glPushMatrix();
				glScalef(2.95, 2.95, 2.95);
				drawGeodesicTriangles(&geodesicV[i]);
			glPopMatrix();
		}

	glPushMatrix();

			glRotatef(-mouseDragSumY * MOUSE_SENSITIVITY, 1, 0, 0);
			glRotatef(-mouseDragSumX * MOUSE_SENSITIVITY, 0, 1, 0);
			glRotatef(-autoRotateY / 5.0, 1, 0, 0);
			glRotatef(-autoRotateX / 5.0, 0, 1, 0);

			glRotatef(-90, 0, 0, 1);

		glLineWidth(1);
		glPointSize(3);

		float alpha1 = sin(count/180.0 * M_PI) * .5 + .5;
		float alpha2 = -sin(count/180.0 * M_PI) * .5 + .5;

		// for(int i = 2; i < 12; i++){
		// 	glPushMatrix();
		// 		// glScalef(3 + i/50.0, 3 + i/50.0, 3 + i/50.0);
		// 		glScalef(3, 3, 3);
		// 		// glColor4f(0.0, 0.0, 0.0, 0.1 + powf(12 - i,2)/1000.0);
		// 		glColor4f(0.0, 0.0, 0.0, 0.1 * alpha1);
		// 		// if(i == 3 || i == 6 || i == 9 || i == 12)
		// 		// glColor4f(0.0, 0.0, 0.0, 0.2);
		// 		// drawGeodesicPoints(&geodesicV[i]);
		// 		drawGeodesicLines(&geodesicV[i]);
		// 		// drawGeodesicFaces(&geodesicV[i]);

		// 		glColor4f(0.0, 0.0, 0.66, 0.15 * alpha2);
		// 		drawGeodesicVertexNormalLines(&normalsV[i]);
		// 		glColor4f(0.0, 0.66, 0.0, 0.15 * alpha2);
		// 		drawGeodesicLineNormalLines(&normalsV[i]);
		// 		glColor4f(0.66, 0.0, 0.0, 0.15 * alpha2);
		// 		drawGeodesicFaceNormalLines(&normalsV[i]);
		// 	glPopMatrix();
		// }
		glPushMatrix();
			glScalef(3.29, 3.29, 3.29);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			drawPlatonicSolidFaces(4);
		glPopMatrix();


		glPushMatrix();
			glScalef(3.3, 3.3, 3.3);
			glColor4f(0.0, 0.0, 0.0, 1.0);
			drawPlatonicSolidFaces(3);
			drawPlatonicSolidLines(4);
		glPopMatrix();


		// glPushMatrix();
		// 	glScalef(3.61, 3.61, 3.61);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(0.0, 0.0, 0.0, 0.07);
		// 	drawGeodesicLines(&ico);
		// 	glColor4f(0.0, 0.0, 0.0, 0.04);
		// 	drawGeodesicTriangles(&ico);
		// glPopMatrix();

		// glPushMatrix();
		// 	glScalef(3.55, 3.55, 3.55);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(0.0, 0.0, 0.0, 0.04);
		// 	drawGeodesicExtrudedTriangles(&mesh[3]);
		// glPopMatrix();


		// glPushMatrix();
		// 	glScalef(3.6, 3.6, 3.6);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(0.0, 0.0, 0.0, 0.09);
		// 	drawGeodesicExtrudedTriangles(&mesh[3]);
		// 	glColor4f(0.0, 0.0, 0.0, 0.05);
		// 	drawGeodesicLines(&geodesicV[3]);
		// glPopMatrix();

		// glPushMatrix();
		// 	glScalef(3.6, 3.6, 3.6);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(1.0, 1.0, 1.0, 0.1);
		// 	drawGeodesicTriangles(&geodesicV[2]);
		// glPopMatrix();

		// glPushMatrix();
		// 	glScalef(3.6, 3.6, 3.6);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(0.0, 0.0, 0.4, 0.05);
		// 	drawGeodesicPoints(&geodesicV[3]);
		// glPopMatrix();

		// glPushMatrix();
		// 	glScalef(3.618, 3.618, 3.618);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(0.0, 0.0, 0.0, 0.1);
		// 	drawGeodesicLines(&geodesicV[2]);
		// 	glColor4f(0.0, 0.0, 0.3, 0.15);
		// 	drawGeodesicVertexNormalLines(&normalsV[3]);
		// 	glColor4f(0.0, 0.3, 0.0, 0.15);
		// 	drawGeodesicLineNormalLines(&normalsV[3]);
		// 	glColor4f(0.3, 0.0, 0.0, 0.15);
		// 	drawGeodesicFaceNormalLines(&normalsV[3]);
		// glPopMatrix();

		// glPushMatrix();
		// 	glScalef(3.6, 3.6, 3.6);
		// 	glRotatef(-90, 0, 0, 1);
		// 	glColor4f(0.0, 0.0, 0.0, 0.1);
		// 	drawGeodesicLines(&geodesicV[4]);
		// glPopMatrix();

			// drawDomeMeshTriangles(&domeV3, &domeMeshV3);



	glPopMatrix();
}

void keyDown(unsigned int key) { }
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }