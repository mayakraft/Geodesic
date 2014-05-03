//
//  geodesic geometry
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//
//  Tetrahedra, Octahedra, Icosahedra
//
//  face subdivide
//  spherize (geodecise)
//  crop sphere
//

#ifndef __geodesic_geometry__
#define __geodesic_geometry__


#define _float_precision 32  // 32, 64, 128
// if mesh rendering: coordinate this with GLfloat

#if _float_precision==128
typedef long double float_;
#elif _float_precision==64
typedef double float_;
#elif _float_precision==32
typedef float float_;
#else
typedef float float_;
#endif

#pragma mark- generate lines[] from face data
#pragma mark- crop function

typedef struct geodesic geodesic;

struct geodesic {
    
    float_          *points;  // each a double[3]- [0]:x [1]:y [2]:z
    unsigned short  *lines;   // each an int[2]- [0]:index in *points [1]:index in *points
    unsigned short  *faces;   // each an int[3]- [0]:index in *points [1]:index in *points [2]:index in *points
    
    unsigned int    numPoints;
    unsigned int    numLines;
    unsigned int    numFaces;

    float_          *pointNormals;
    float_          *lineNormals;
    float_          *faceNormals;
};

geodesic icosahedron(int v);
geodesic octahedron(int v);
geodesic tetrahedron(int v);

geodesic tetrahedronDome(int v, float crop);
geodesic octahedronDome(int v, float crop);
geodesic icosahedronDome(int v, float crop);

void freeGeodesic(geodesic *g);

#endif