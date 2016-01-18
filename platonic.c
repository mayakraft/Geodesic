#include "platonic.h"

#ifdef __APPLE__
# if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
#  import <OpenGLES/ES1/gl.h>
# elif TARGET_OS_IPHONE
#  import <OpenGLES/ES1/gl.h>
# else
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# endif
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <stdlib.h>

void tetrahedronMesh(GLfloat **po, unsigned int *numPoints,
                  unsigned short **li, unsigned int *numLines,
                  unsigned short **fa, unsigned int *numFaces){
    *numPoints = TETRAHEDRON_POINTS;
    *numLines = TETRAHEDRON_LINES;
    *numFaces = TETRAHEDRON_FACES;
    GLfloat *points = malloc(sizeof(GLfloat)*(*numPoints)*3);
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    for(int i = 0; i < (*numPoints)*3; i++)
        points[i] = _tetrahedron_points[i];
    for(int i = 0; i < (*numLines)*2; i++)
        lines[i] = _tetrahedron_lines[i];
    for(int i = 0; i < (*numFaces)*3; i++)
        faces[i] = _tetrahedron_faces[i];
    *po = points;
    *li = lines;
    *fa = faces;
}

void octahedronMesh(GLfloat **po, unsigned int *numPoints,
                 unsigned short **li, unsigned int *numLines,
                 unsigned short **fa, unsigned int *numFaces){
    *numPoints = OCTAHEDRON_POINTS;
    *numLines = OCTAHEDRON_LINES;
    *numFaces = OCTAHEDRON_FACES;
    GLfloat *points = malloc(sizeof(GLfloat)*(*numPoints)*3);
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    for(int i = 0; i < (*numPoints)*3; i++)
        points[i] = _octahedron_points[i];
    for(int i = 0; i < (*numLines)*2; i++)
        lines[i] = _octahedron_lines[i];
    for(int i = 0; i < (*numFaces)*3; i++)
        faces[i] = _octahedron_faces[i];
    *po = points;
    *li = lines;
    *fa = faces;
}

void hexahedronMesh(GLfloat **po, unsigned int *numPoints,
                 unsigned short **li, unsigned int *numLines,
                 unsigned short **fa, unsigned int *numFaces){
    *numPoints = HEXAHEDRON_POINTS;
    *numLines = HEXAHEDRON_LINES;
    *numFaces = HEXAHEDRON_TRIANGLE_FACES;
    GLfloat *points = malloc(sizeof(GLfloat)*(*numPoints)*3);
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    for(int i = 0; i < (*numPoints)*3; i++)
        points[i] = _hexahedron_points[i];
    for(int i = 0; i < (*numLines)*2; i++)
        lines[i] = _hexahedron_lines[i];
    // hexahedron faces are squares, not triangles
    for(int i = 0; i < (*numFaces)*4; i++)
        faces[i] = _hexahedron_triangle_faces[i];
    *po = points;
    *li = lines;
    *fa = faces;
}

void icosahedronMesh(GLfloat **po, unsigned int *numPoints,
                  unsigned short **li, unsigned int *numLines,
                  unsigned short **fa, unsigned int *numFaces){
    *numPoints = ICOSAHEDRON_POINTS;
    *numLines = ICOSAHEDRON_LINES;
    *numFaces = ICOSAHEDRON_FACES;
    GLfloat *points = malloc(sizeof(GLfloat)*(*numPoints)*3);
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    for(int i = 0; i < (*numPoints)*3; i++)
        points[i] = _icosahedron_points[i];
    for(int i = 0; i < (*numLines)*2; i++)
        lines[i] = _icosahedron_lines[i];
    for(int i = 0; i < (*numFaces)*3; i++)
        faces[i] = _icosahedron_faces[i];
    *po = points;
    *li = lines;
    *fa = faces;
}

void _dodecahedron(GLfloat **po, unsigned int *numPoints,
                   unsigned short **li, unsigned int *numLines,
                   unsigned short **fa, unsigned int *numFaces){
    *numPoints = DODECAHEDRON_POINTS;
    *numLines = DODECAHEDRON_LINES;
    *numFaces = DODECAHEDRON_TRIANGLE_FACES;
    GLfloat *points = malloc(sizeof(GLfloat)*(*numPoints)*3);
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    for(int i = 0; i < (*numPoints)*3; i++)
        points[i] = _dodecahedron_points[i];
    for(int i = 0; i < (*numLines)*2; i++)
        lines[i] = _dodecahedron_lines[i];
    for(int i = 0; i < (*numFaces)*3; i++)
        faces[i] = _dodecahedron_triangle_faces[i];
}

////////////////////////////////////////////////////////
//    OpenGL ES convenience functions for platonic.h
//
void drawPlatonicSolidFaces(char solidType){
	const float *vertices;
	const unsigned short *faces;
	unsigned int numFaces;
	if(solidType == 0){
		vertices = _tetrahedron_points;
		numFaces = TETRAHEDRON_FACES;
		faces = _tetrahedron_faces;
	}
	else if(solidType == 1){
		vertices = _octahedron_points;
		numFaces = OCTAHEDRON_FACES;
		faces = _octahedron_faces;
	}
	else if(solidType == 2){
		vertices = _hexahedron_points;
		numFaces = HEXAHEDRON_TRIANGLE_FACES;
		faces = _hexahedron_triangle_faces;
	}
	else if(solidType == 3){
		vertices = _icosahedron_points;
		numFaces = ICOSAHEDRON_FACES;
		faces = _icosahedron_faces;
	}
	else if(solidType == 4){
		vertices = _dodecahedron_points;
		numFaces = DODECAHEDRON_TRIANGLE_FACES;
		faces = _dodecahedron_triangle_faces;
	}
	else if(solidType == -1){
		vertices = _tetrahedron_dual_points;
		numFaces = TETRAHEDRON_FACES;
		faces = _tetrahedron_faces;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, 3*numFaces, GL_UNSIGNED_SHORT, faces);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidLines(char solidType){
	const float *vertices;
	const unsigned short *lines;
	unsigned int numLines;
	if(solidType == 0){
		vertices = _tetrahedron_points;
		numLines = TETRAHEDRON_LINES;
		lines = _tetrahedron_lines;
	}
	else if(solidType == 1){
		vertices = _octahedron_points;
		numLines = OCTAHEDRON_LINES;
		lines = _octahedron_lines;
	}
	else if(solidType == 2){
		vertices = _hexahedron_points;
		numLines = HEXAHEDRON_LINES;
		lines = _hexahedron_lines;
	}
	else if(solidType == 3){
		vertices = _icosahedron_points;
		numLines = ICOSAHEDRON_LINES;
		lines = _icosahedron_lines;
	}
	else if(solidType == 4){
		vertices = _dodecahedron_points;
		numLines = DODECAHEDRON_LINES;
		lines = _dodecahedron_lines;
	}
	else if(solidType == -1){
		vertices = _tetrahedron_dual_points;
		numLines = TETRAHEDRON_LINES;
		lines = _tetrahedron_lines;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINES, 2*numLines, GL_UNSIGNED_SHORT, lines);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidPoints(char solidType){
	const float *vertices;
	unsigned int numVertices;
	if(solidType == 0){
		vertices = _tetrahedron_points;
		numVertices = TETRAHEDRON_POINTS;
	}
	else if(solidType == 1){
		vertices = _octahedron_points;
		numVertices = OCTAHEDRON_POINTS;
	}
	else if(solidType == 2){
		vertices = _hexahedron_points;
		numVertices = HEXAHEDRON_POINTS;
	}
	else if(solidType == 3){
		vertices = _icosahedron_points;
		numVertices = ICOSAHEDRON_POINTS;
	}
	else if(solidType == 4){
		vertices = _dodecahedron_points;
		numVertices = DODECAHEDRON_POINTS;
	}
	else if(solidType == -1){
		vertices = _tetrahedron_dual_points;
		numVertices = TETRAHEDRON_POINTS;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, vertices);
	glDrawArrays(GL_POINTS, 0, numVertices);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////