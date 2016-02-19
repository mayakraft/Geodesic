#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif


#include "platonic.h"

////////////////////////////////////////////////////////
//    OpenGL ES functions for platonic.h
//              rendering points, lines, faces

// index convention for now:
//   0: tetrahedron
//   1: octahedron
//   2: hexahedron
//   3: icosahedron
//   4: dodecahedron
//   5: tetrahedron dual  <- special case (same geometry as 0:tetrahedron, aligned differently)

unsigned int _poly_num_vertices[6] = {
	TETRAHEDRON_POINT_COUNT, OCTAHEDRON_POINT_COUNT, HEXAHEDRON_POINT_COUNT, ICOSAHEDRON_POINT_COUNT, DODECAHEDRON_POINT_COUNT, TETRAHEDRON_POINT_COUNT
};
unsigned int _poly_num_lines[6] = {
	TETRAHEDRON_LINE_COUNT, OCTAHEDRON_LINE_COUNT, HEXAHEDRON_LINE_COUNT, ICOSAHEDRON_LINE_COUNT, DODECAHEDRON_LINE_COUNT, TETRAHEDRON_LINE_COUNT
};
unsigned int _poly_num_faces[6] = {
	TETRAHEDRON_FACE_COUNT, OCTAHEDRON_FACE_COUNT, HEXAHEDRON_TRIANGLE_FACE_COUNT, ICOSAHEDRON_FACE_COUNT, DODECAHEDRON_TRIANGLE_FACE_COUNT, TETRAHEDRON_FACE_COUNT
};
const float* _poly_point_arrays[6] = {
	_tetrahedron_points, _octahedron_points, _hexahedron_points, _icosahedron_points, _dodecahedron_points, _tetrahedron_dual_points
};
const unsigned short* _poly_line_array[6] = {
	_tetrahedron_lines, _octahedron_lines, _hexahedron_lines, _icosahedron_lines, _dodecahedron_lines, _tetrahedron_dual_lines
};
const unsigned short* _poly_face_array[6] = {
	_tetrahedron_faces, _octahedron_faces, _hexahedron_triangle_faces, _icosahedron_faces, _dodecahedron_triangle_faces, _tetrahedron_dual_faces
};
int _poly_dual_index[6] = { 5, 2, 1, 4, 3, 0 };

float platonic_dihedral_angle[6] = {
	TETRAHEDRON_DIHEDRAL_ANGLE,
	OCTAHEDRON_DIHEDRAL_ANGLE,
	HEXAHEDRON_DIHEDRAL_ANGLE,
	ICOSAHEDRON_DIHEDRAL_ANGLE,
	DODECAHEDRON_DIHEDRAL_ANGLE,
	TETRAHEDRON_DIHEDRAL_ANGLE
};
float platonic_inradius[6] = {
	TETRAHEDRON_INRADIUS,
	OCTAHEDRON_INRADIUS,
	HEXAHEDRON_INRADIUS,
	ICOSAHEDRON_INRADIUS,
	DODECAHEDRON_INRADIUS,
	TETRAHEDRON_INRADIUS
};
float platonic_midradius[6] = {
	TETRAHEDRON_MIDRADIUS,
	OCTAHEDRON_MIDRADIUS,
	HEXAHEDRON_MIDRADIUS,
	ICOSAHEDRON_MIDRADIUS,
	DODECAHEDRON_MIDRADIUS,
	TETRAHEDRON_MIDRADIUS
};
float platonic_side_length[6] = {
	TETRAHEDRON_SIDE_LENGTH,
	OCTAHEDRON_SIDE_LENGTH,
	HEXAHEDRON_SIDE_LENGTH,
	ICOSAHEDRON_SIDE_LENGTH,
	DODECAHEDRON_SIDE_LENGTH,
	TETRAHEDRON_SIDE_LENGTH
};
float platonic_volume[6] = {
	TETRAHEDRON_VOLUME,
	OCTAHEDRON_VOLUME,
	HEXAHEDRON_VOLUME,
	ICOSAHEDRON_VOLUME,
	DODECAHEDRON_VOLUME,
	TETRAHEDRON_VOLUME
};

void drawPlatonicSolidFaces(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _poly_point_arrays[ solidType ]);
	glDrawElements(GL_TRIANGLES, 3*_poly_num_faces[solidType], GL_UNSIGNED_SHORT, _poly_face_array[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidLines(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _poly_point_arrays[ solidType ]);
	glDrawElements(GL_LINES, 2*_poly_num_lines[solidType], GL_UNSIGNED_SHORT, _poly_line_array[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidPoints(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _poly_point_arrays[ solidType ]);
	glDrawArrays(GL_POINTS, 0, _poly_num_vertices[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}