//
//  geodesic
//  geometry builder
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

//  Tetrahedra, Octahedra, Icosahedra
//
//  face subdivide
//  spherize (geodecise)
//  crop sphere

#ifndef __geodesic__geometry__
#define __geodesic__geometry__
typedef struct geodesic geodesic;


#define _float_precision 32  // 32:float, 64:double, 128:long double
// using floats to match GLfloat in OpenGLES

geodesic icosahedron(int v);
geodesic octahedron(int v);
geodesic tetrahedron(int v);
//TODO: not implemented
geodesic tetrahedronDome(int v, float crop);
geodesic octahedronDome(int v, float crop);
geodesic icosahedronDome(int v, float crop);

void deleteGeodesic(geodesic *g);


#if _float_precision==128
typedef long double float_;
#elif _float_precision==64
typedef double float_;
#elif _float_precision==32
typedef float float_;
#else
typedef float float_;
#endif
struct geodesic {
    
    unsigned int    numPoints;
    unsigned int    numLines;
    unsigned int    numFaces;
    
    float_          *points;  // count: numPoints * 3
    unsigned short  *lines;   // count: numLines * 2
    unsigned short  *faces;   // count: numFaces * 3
    
    float_          *pointNormals;  // count: numPoints * 3
    float_          *lineNormals;   // count: numLines * 3
    float_          *faceNormals;   // count: numFaces * 3
};

#endif