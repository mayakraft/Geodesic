////////////////////////////////////////////////////////////////////
//                        PLATONIC SOLIDS                         //
//           centered at origin          radius = 1               //
//                                                                //
//         TETRA               OCTA              ICOSA            //
//             one point aligned along the +X axis                //
//                                                                //
//                   HEXA                DODECA                   //
//          aligned as duals to the octa / icosahedron            //
//                   faces in place of points                     //
//         (one face normal aligned along the +X axis)            //
//                                                                //
//                     + + + + + + + + + + +                      //
//                                                                //
//     even possible to cross-reference indices across duals      //
//                                                                //
//  eg:                                                           //
//   octa's 6 point indices correlate to hexa's 6 face indices    //
//      and octa's point[0] is along hexa's face[0] normal        //
//                                                                //
//  this implies:                                                 //
//  you can find a solid's face normals in its dual's points      //
//                                                                //
////////////////////////////////////////////////////////////////////

// for higher precision, replace all "float" with "double" or "long double"

#define TETRAHEDRON_POINTS 4
#define TETRAHEDRON_LINES 6
#define TETRAHEDRON_FACES 4

#define OCTAHEDRON_POINTS 6
#define OCTAHEDRON_LINES 12
#define OCTAHEDRON_FACES 8

#define HEXAHEDRON_POINTS 8
#define HEXAHEDRON_LINES 12
#define HEXAHEDRON_FACES 6
#define HEXAHEDRON_TRIANGLE_FACES 12  // OpenGL ES can only render triangles

#define ICOSAHEDRON_POINTS 12
#define ICOSAHEDRON_LINES 30
#define ICOSAHEDRON_FACES 20

#define DODECAHEDRON_POINTS 20
#define DODECAHEDRON_LINES 30
#define DODECAHEDRON_FACES 12
#define DODECAHEDRON_TRIANGLE_FACES 36

// dihedral angle is the angle between two adjacent faces,
//  circling under and running perpendicular to the edge dividing the faces
#define TETRAHEDRON_DIHEDRAL_ANGLE   70.52877936550930863075400066
#define OCTAHEDRON_DIHEDRAL_ANGLE   109.47122063449069136924599934
#define HEXAHEDRON_DIHEDRAL_ANGLE    90
#define ICOSAHEDRON_DIHEDRAL_ANGLE  138.189685104221401934142083269
#define DODECAHEDRON_DIHEDRAL_ANGLE 116.56505117707798935157219372

// inradius is the radius of the inscribed sphere
// or the distance from center to midpoint of a face
#define TETRAHEDRON_INRADIUS    0.333333333333333333333333333333
#define OCTAHEDRON_INRADIUS     0.577350269189625764509148780502
#define HEXAHEDRON_INRADIUS     0.5773502691896257645091487805
#define ICOSAHEDRON_INRADIUS    0.794654472291766122955530928331
#define DODECAHEDRON_INRADIUS   0.794654472291766122955530928327

#define TETRAHEDRON_SIDE_LENGTH   1.6329931618554520654648560498
#define OCTAHEDRON_SIDE_LENGTH    1.41421356237309504880168872421
#define HEXAHEDRON_SIDE_LENGTH    1.154700538379251529018297561
#define ICOSAHEDRON_SIDE_LENGTH   1.0514622242382672120513381697
#define DODECAHEDRON_SIDE_LENGTH  0.713644179546179863883939686092

#define TETRAHEDRON_VOLUME    0.513200239279667346230354471554
#define OCTAHEDRON_VOLUME     1.33333333333333333333333333333
#define HEXAHEDRON_VOLUME     1.53960071783900203869106341466
#define ICOSAHEDRON_VOLUME    2.53615071012040952564383822238
#define DODECAHEDRON_VOLUME   2.78516386312262296729255491273

const float _tetrahedron_dual_points[TETRAHEDRON_POINTS*3] = { 
	-1.0,               0.0,               0.0,               
	0.333333333333333,  0.942809041582063, 0.0,               
	0.333333333333333,  -0.471404520791032, 0.816496580927726, 
	0.333333333333333,  -0.471404520791032, -0.816496580927726};
const float _tetrahedron_points[TETRAHEDRON_POINTS*3] = { 
	1.0,                 0.0,               0.0,               
	-0.333333333333333, -0.942809041582063, 0.0,               
	-0.333333333333333,  0.471404520791032, 0.816496580927726, 
	-0.333333333333333,  0.471404520791032, -0.816496580927726};
const unsigned short _tetrahedron_lines[TETRAHEDRON_LINES*2] = {
	2, 3, 2, 0, 2, 1, 3, 0, 3, 1, 0, 1};
const unsigned short _tetrahedron_faces[TETRAHEDRON_FACES*3] = {
	2, 0, 1,  
	2, 1, 3,  
	2, 3, 0,  
	3, 1, 0};
const float _octahedron_points[OCTAHEDRON_POINTS*3] = {
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	-1.0, 0.0, 0.0,
	0.0, -1.0, 0.0,
	0.0, 0.0, -1.0};
const unsigned short _octahedron_lines[OCTAHEDRON_LINES*2] = {
	1, 0, 1, 2, 1, 5, 1, 3, 3, 2, 2, 0, 0, 5, 5, 3, 4, 2, 4, 3, 4, 5, 4, 0};
const unsigned short _octahedron_faces[OCTAHEDRON_FACES*3] = { 
	1, 0, 2, 
	1, 5, 0, 
	4, 0, 5,
	4, 2, 0, 
	1, 2, 3, 
	1, 3, 5, 
	4, 5, 3, 
	4, 3, 2};
const float _hexahedron_points[HEXAHEDRON_POINTS*3] = { 
	0.57735026918963, 0.57735026918963, 0.57735026918963,
	0.57735026918963, 0.57735026918963, -0.57735026918963,
	0.57735026918963, -0.57735026918963, -0.57735026918963,
	0.57735026918963, -0.57735026918963, 0.57735026918963,
	-0.57735026918963, 0.57735026918963, 0.57735026918963,
	-0.57735026918963, 0.57735026918963, -0.57735026918963,
	-0.57735026918963, -0.57735026918963, -0.57735026918963,
	-0.57735026918963, -0.57735026918963, 0.57735026918963};
const unsigned short _hexahedron_lines[HEXAHEDRON_LINES*2] = {
	0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 1, 5, 2, 6, 3, 7, 4, 5, 5, 6, 6, 7, 7, 4};
const unsigned short _hexahedron_faces[HEXAHEDRON_FACES*4] = {
// these are being stored as squares, not triangles
	0, 3, 2, 1,
	4, 0, 1, 5,
	0, 3, 7, 4,
	7, 4, 5, 6,
	3, 7, 6, 2,
	1, 5, 6, 2};
const unsigned short _hexahedron_triangle_faces[HEXAHEDRON_TRIANGLE_FACES*3] = {
	0, 2, 3,
	 2, 0, 1,
	4, 1, 0,
	 1, 4, 5,
	0, 3, 7,
	 7, 4, 0,	
	7, 5, 4,
	 5, 7, 6,
	3, 6, 7,
	 6, 3, 2,
	1, 5, 6,
	 6, 2, 1};
const float _icosahedron_points[ICOSAHEDRON_POINTS*3] = {
	0.447213595499958, -0.276393202250021, 0.850650808352040,
	-0.447213595499958, 0.276393202250021, 0.850650808352040,
	-0.447213595499958, 0.276393202250021, -0.850650808352040,
	0.447213595499958, -0.276393202250021, -0.850650808352040,
	-0.447213595499958, -0.723606797749979, 0.525731112119134,
	0.447213595499958, 0.723606797749979, 0.525731112119134,
	0.447213595499958, 0.723606797749979, -0.525731112119134,
	-0.447213595499958, -0.723606797749979, -0.525731112119134,
	0.447213595499958, -0.894427190999916, 0.0,
	1.0,                0.0,               0.0,
	-0.447213595499958, 0.894427190999916, 0.0,
	-1.0,               0.0,               0.0};
const unsigned short _icosahedron_lines[ICOSAHEDRON_LINES*2] = {
	0, 8, 0, 9, 0, 1, 0, 4, 0, 5, 8, 3, 8, 9, 8, 7, 8, 4, 9, 3, 
	9, 6, 9, 5, 7, 4, 7, 3, 7, 2, 7, 11, 2, 10, 2, 11, 2, 3, 2, 6,
	10, 11, 10, 5, 10, 6, 10, 1, 11, 1, 11, 4, 4, 1, 5, 1, 5, 6, 6, 3};
const unsigned short _icosahedron_faces[ICOSAHEDRON_FACES*3] = { 
	8, 7, 4, 
	7, 8, 3,    // pair 2 
	8, 4, 0, 
	8, 0, 9, 
	9, 3, 8, 
	9, 0, 5, 
	9, 5, 6, 
	9, 6, 3, 
	3, 2, 7,   // pair 2
	3, 6, 2, 
	0, 4, 1, 
	0, 1, 5, 
	11, 4, 7, 
	11, 7, 2, 
	11, 2, 10, 
	1, 11, 10,    // pair 1
	11, 1, 4, 
	10, 6, 5, 
	10, 5, 1,     // pair 1
	10, 2, 6};
const float _dodecahedron_points[DODECAHEDRON_POINTS * 3] = {
	-0.794657,   0.491120, 0.371929,
	-0.187594,   0.794649, -0.601791,
	-0.794657,   0.491120, -0.371929,
	-0.794657, -0.187593, -0.601791,
	0.187593,  0.303529, -0.973720,
	0.187594,  0.982242, -0.000000,
	0.187593,-0.794649, -0.601791,
	-0.187593, -0.303529, -0.973720,
	-0.187594, -0.982242, -0.000000,
	-0.794657, -0.607058, -0.000000,
	0.794657,-0.491120, -0.371929,
	0.187593,-0.794649, 0.601791,
	-0.187593, -0.303529, 0.973720,
	-0.794657, -0.187593, 0.601791,
	0.794657,-0.491120, 0.371929,
	-0.187594,   0.794649, 0.601791,
	0.187593,  0.303529, 0.973720,
	0.794657,  0.187593, 0.601791,
	0.794657,  0.607058, 0.000000,
	0.794657,  0.187594, -0.601792 };
const unsigned short _dodecahedron_lines[DODECAHEDRON_LINES * 2] = {
	19, 18,
	18, 17,
	17, 14,
	14, 10,
	10, 19,
	14, 11,
	11, 8,
	8, 6,
	6, 10,
	19, 4,
	4, 1,
	1, 5,
	5, 18,
	9, 3,
	3, 7,
	7, 6,
	8, 9,
	13, 9,
	3, 2,
	2, 0,
	0, 13,
	12, 11,
	12, 13,
	1, 2,
	5, 15,
	15, 0,
	15, 16,
	16, 17,
	16, 12,
	4, 7 };
const unsigned short _dodecahedron_triangle_faces[DODECAHEDRON_TRIANGLE_FACES * 3] = {
	5, 2, 1,
	15, 0, 5,
	2, 5, 0,

	9, 2, 13,
	2, 0, 13,
	3, 2, 9,

	10, 17, 19,
	18, 19, 17,
	14, 17, 10,

	19, 1,  4,
	6, 9, 8,   
	1, 18, 5, 

	11, 14, 8, 
	18, 1, 19,
	8, 9, 11,

	10, 8, 14,
	8, 10, 6, 
	6, 7, 9,

	9, 7, 3,
	13, 12, 9,
	12, 11, 9,

	18, 15, 5,
	17, 15, 18,
	15, 17, 16,

	11, 12, 14,
	14, 12, 17,
	17, 12, 16,

	12, 13, 16,
	13, 0, 16,
    0,  15, 16,

	7, 2, 3,
	2, 7, 1,
	1, 7, 4,

 	4, 7,  19,
	19, 7, 10,
	6, 10, 7 };