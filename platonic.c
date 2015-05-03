#include "platonic.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

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