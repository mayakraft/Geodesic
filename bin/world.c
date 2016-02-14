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

geodesicSphere g;
geodesicMeshTriangles m;
tween t;
tween ext;

float noiseRotateX, noiseRotateY;

#define frand() ((double) rand() / (RAND_MAX+1.0))
#define NUM_SOLIDS 100
float objcts[3*NUM_SOLIDS];
unsigned short objctsType[NUM_SOLIDS];

// float elapsedTime = 0;

void setup(){
	GRID = 0;
	GROUND = 0;
	
	// POV = POLAR;
	glPointSize(64);
	// glLineWidth(5);
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 5.0f };
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat green[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// glEnable(GL_LIGHTING);
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


	g = icosahedronSphere(4);
	m = makeMeshTriangles(&g, .8);
	t = makeTween(g.pointsNotSpherized, g.pointsDeltaSpherized, g.numPoints*3);
	// ext = makeTween(m.glTriangles, )
 //    unsigned int    numTriangles;
 //    float           *;

//	printf("Geodesic (%dv): %d points, %d lines, %d faces\n", g.frequency, g.numPoints, g.numLines, g.numFaces);

	for(int i = 0; i < NUM_SOLIDS; i++){
		objcts[0+i*3] = frand()*30-15;
		objcts[1+i*3] = frand()*100-50;
		objcts[2+i*3] = frand()*30-15;
		objctsType[i] = rand()%5;
	}
}

void update(){

		for(int i = 0; i < NUM_SOLIDS; i++){
		objcts[i*3+1] -= .45;//33;
		if(objcts[i*3+1] < -50.0)
			objcts[i*3+1] += 100.0;
	}


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
			deleteGeodesicSphere(&g);
			g = icosahedronSphere(  ((int)pow(rand()%4+1,1.25))+ 1  );
			for(int i = 0; i < g.numPoints; i++){
				if(g.parentFace[i] >= 0){
					// printf("%d (%d) %f\n", i, g.parentFace[i], g.faceNormals[g.parentFace[i]]);
					g.pointNormals[i*3+0] = _dodecahedron_points[g.parentFace[i]*3+0];
					g.pointNormals[i*3+1] = _dodecahedron_points[g.parentFace[i]*3+1];
					g.pointNormals[i*3+2] = _dodecahedron_points[g.parentFace[i]*3+2];
				}
			}
			deleteTween(&t);
			t = makeTween(g.pointsNotSpherized, g.pointsDeltaSpherized, g.numPoints*3);
		}
		updateTween(&t, tween);
	}
}

void draw(){

	glPushMatrix();
		// apply perspective inside this matrix
		if(POV == 0){
			glRotatef(mouseDragSumY, -1, 0, 0);
			glRotatef(mouseDragSumX, 0, 0, -1);
			glTranslatef(originX, originY, 0);
		}
		if(POV == 1){
			glTranslatef(0, 0, -ZOOM);
			glRotatef(mouseDragSumY, -1, 0, 0);
			glRotatef(mouseDragSumX, 0, 0, -1);
		}
		if(POV == 2){
			glTranslatef(-mouseDragSumX * .05, mouseDragSumY * .05, 0.0f);
		}

		// perspective has been established
		// draw stuff below

		// glPushMatrix();
		// 	glTranslatef(0.0f, 0.0f, -1.0f);
		// 	int XOffset = 0;
		// 	int ZOffset = 0;
		// 	if(POV == 0){
		// 		XOffset = walkX;  // math.floor
		// 		ZOffset = walkY;
		// 	}
		// 	for(int i = -8; i <= 8; i++){
		// 		for(int j = -8; j <= 8; j++){
		// 			int b = abs(((i+j+XOffset+ZOffset)%2));
		// 			if(b) glColor3f(0.0, 0.0, 0.0);
		// 			else glColor3f(1.0, 1.0, 1.0);
		// 			unitSquare(i-XOffset, j-ZOffset, 1, 1);
		// 		}
		// 	}
		// glPopMatrix();


	// glClearColor(0.0, 0.0, 0.0, 0.0);
	// glClearDepth(1.0);
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
			noiseRotateX = noise1(step1*.75+10)*360;
			noiseRotateY = noise1(step6*.75)*360;

			glTranslatef(0.0, 0.0, -3.0);
   			glRotatef(noiseRotateX, -1, 0, 0);
	    	glRotatef(noiseRotateY, 0, -1, 0);
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
			else if(objctsType[i] == 2){
				glVertexPointer(3, GL_FLOAT, 0, _icosahedron_points);
				glNormalPointer(GL_FLOAT, 0, _icosahedron_points);
				glDrawElements(GL_TRIANGLES, 3*ICOSAHEDRON_FACES, GL_UNSIGNED_SHORT, _icosahedron_faces);
			}
			else if(objctsType[i] == 3){
				glVertexPointer(3, GL_FLOAT, 0, _hexahedron_points);
				glNormalPointer(GL_FLOAT, 0, _hexahedron_points);
				glDrawElements(GL_TRIANGLES, 3*HEXAHEDRON_TRIANGLE_FACES, GL_UNSIGNED_SHORT, _hexahedron_triangle_faces);
			}
			else if(objctsType[i] == 4){
				glVertexPointer(3, GL_FLOAT, 0, _dodecahedron_points);
				glNormalPointer(GL_FLOAT, 0, _dodecahedron_points);
				glDrawElements(GL_TRIANGLES, 3*DODECAHEDRON_TRIANGLE_FACES, GL_UNSIGNED_SHORT, _dodecahedron_triangle_faces);
			}
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	// geodesicDrawTriangles(&g);
	glEnable(GL_LIGHTING);

	    	glRotatef(noise1(step1)*360, 0, 1, 0);
	    	glRotatef(noise1(step3)*360, 1, 0, 0);
	    	glRotatef(noise1(step5)*360, 0, 0, 1);


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




	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, t.data);
    glNormalPointer(GL_FLOAT, 0, g.pointNormals);
    glDrawElements(GL_TRIANGLES, g.numFaces*3, GL_UNSIGNED_SHORT, g.faces);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

	// geodesicDrawTriangles(&g);

	glShadeModel(GL_FLAT);
	// geodesicDrawTriangles(&g);
			// geodesicMeshDrawExtrudedTriangles(&m);
	glShadeModel (GL_SMOOTH);

		glPopMatrix();
	glPopMatrix();



	glPopMatrix();

}

void keyDown(unsigned int key) { }
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }