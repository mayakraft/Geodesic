////////////////////////////////////////////////////////////////////
//                        PLATONIC SOLIDS                         //
//                    the 3 made of triangles                     //
//              centered at origin       radius = 1               //
//                                                                //
//         TETRA               OCTA              ICOSA            //
//             one point aligned along the +X axis                //
//                                                                //
//                   HEXA                DODECA                   //
//          one face normal aligned along the +X axis             //
//                                                                //
////////////////////////////////////////////////////////////////////
//                                                                //
//      flo_t : type cast to float, double, or long double        //
//                                                                //
//   below, functions to re-generate the geometry functionally    //
//                                                                //
////////////////////////////////////////////////////////////////////

// match type float to match GLfloat in your version of OpenGL
#define _float_precision 32  // 32:float, 64:double, 128:long double

#if _float_precision==128
typedef long double flo_t;
#elif _float_precision==64
typedef double flo_t;
#elif _float_precision==32
typedef float flo_t;
#else
typedef float flo_t;
#endif


#define TETRAHEDRON_POINTS 4
#define TETRAHEDRON_LINES 6
#define TETRAHEDRON_FACES 4

#define OCTAHEDRON_POINTS 6
#define OCTAHEDRON_LINES 12
#define OCTAHEDRON_FACES 8

#define HEXAHEDRON_POINTS 8
#define HEXAHEDRON_LINES 12
#define HEXAHEDRON_FACES 6
#define HEXAHEDRON_TRIANGLE_FACES 12

#define ICOSAHEDRON_POINTS 12
#define ICOSAHEDRON_LINES 30
#define ICOSAHEDRON_FACES 20

#define DODECAHEDRON_POINTS 20
#define DODECAHEDRON_LINES 30
#define DODECAHEDRON_FACES 12
#define DODECAHEDRON_TRIANGLE_FACES 36


const flo_t _tetrahedron_points[TETRAHEDRON_POINTS*3] = { 
	-0.333333333333333, 0.816496580927726,  0.471404520791032,
	-0.333333333333333, -0.816496580927726, 0.471404520791032,
	1.0,                0.0,                0.0,
	-0.333333333333333, 0.0,               -0.942809041582063};
const unsigned short _tetrahedron_lines[TETRAHEDRON_LINES*2] = {
	0, 1, 0, 2, 0, 3, 1, 2, 1, 3, 2, 3};
const unsigned short _tetrahedron_faces[TETRAHEDRON_FACES*3] = {
	0, 3, 2, 0, 1, 3, 0, 2, 1, 1, 2, 3};
const flo_t _octahedron_points[OCTAHEDRON_POINTS*3] = {
	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 0.0, -1.0,
	-1.0, 0.0, 0.0,
	0.0, 0.0, 1.0,
	0.0, -1.0, 0.0};
const unsigned short _octahedron_lines[OCTAHEDRON_LINES*2] = {
	0, 1, 0, 4, 0, 2, 0, 3, 3, 4, 4, 1, 1, 2, 2, 3, 5, 4, 5, 3, 5, 2, 5, 1};
const unsigned short _octahedron_faces[OCTAHEDRON_FACES*3] = { 
	0, 1, 4, 0, 2, 1, 0, 3, 2, 0, 4, 3, 5, 4, 1, 5, 3, 4, 5, 2, 3, 5, 1, 2};
const flo_t _hexahedron_points[HEXAHEDRON_POINTS*3] = { 
	0.57735026918963, 0.57735026918963, 0.57735026918963,
	0.57735026918963, -0.57735026918963, 0.57735026918963,
	-0.57735026918963, -0.57735026918963, 0.57735026918963,
	-0.57735026918963, 0.57735026918963, 0.57735026918963,
	0.57735026918963, 0.57735026918963, -0.57735026918963,
	0.57735026918963, -0.57735026918963, -0.57735026918963,
	-0.57735026918963, -0.57735026918963, -0.57735026918963,
	-0.57735026918963, 0.57735026918963, -0.57735026918963};
const unsigned short _hexahedron_lines[HEXAHEDRON_LINES*2] = {
	0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 1, 5, 2, 6, 3, 7, 4, 5, 5, 6, 6, 7, 7, 4};
const unsigned short _hexahedron_faces[HEXAHEDRON_FACES*4] = {
// these are being stored as squares, not triangles
	0, 1, 2, 3,
	0, 4, 5, 1,
	1, 5, 6, 2,
	2, 6, 7, 3,
	3, 7, 1, 0,
	7, 6, 5, 4};
const unsigned short _hexahedron_triangle_faces[HEXAHEDRON_TRIANGLE_FACES*3] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 5,
	0, 5, 1,
	1, 5, 6,
	1, 6, 2,
	2, 6, 7,
	2, 7, 3,
	3, 7, 0,   // something up
	3, 0, 1,
	7, 6, 5,
	7, 5, 4
};
const flo_t _icosahedron_points[ICOSAHEDRON_POINTS*3] = {
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
const flo_t _dodecahedron_points[DODECAHEDRON_POINTS * 3] = {
	0.491120, 0.794657, 0.371929,
	0.794649, 0.187594, -0.601791,
	0.491120, 0.794657, -0.371929,
	-0.187593,  0.794657,  -0.601791,
	0.303529, -0.187593,  -0.973720,
	0.982242, -0.187594,  -0.000000,
	-0.794649,  -0.187593, -0.601791,
	-0.303529,  0.187593,  -0.973720,
	-0.982242,  0.187594,  -0.000000,
	-0.607058,  0.794657,  -0.000000,
	-0.491120,  -0.794657, -0.371929,
	-0.794649,  -0.187593, 0.601791,
	-0.303529,  0.187593,  0.973720,
	-0.187593,  0.794657,  0.601791,
	-0.491120,  -0.794657, 0.371929,
	0.794649, 0.187594, 0.601791,
	0.303529, -0.187593,  0.973720,
	0.187593, -0.794657,  0.601791,
	0.607058, -0.794657,  0.000000,
	0.187594, -0.794657,  -0.601792 };
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
	6, 10,7
};