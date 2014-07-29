//
//  geodesic
//  geometry builder
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

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
typedef long double float_t;
#elif _float_precision==64
typedef double float_t;
#elif _float_precision==32
typedef float float_t;
#else
typedef float float_t;
#endif

struct geodesic {
    
    unsigned int    numPoints;
    unsigned int    numLines;
    unsigned int    numFaces;
    
    float_t         *points;  // count: numPoints * 3
    unsigned short  *lines;   // count: numLines * 2
    unsigned short  *faces;   // count: numFaces * 3
    
    float_t         *pointNormals;  // count: numPoints * 3
    float_t         *lineNormals;   // count: numLines * 3
    float_t         *faceNormals;   // count: numFaces * 3
    
    // eventually encapsulate this, inside another struct, inside a function, make into the .c file
    // the following is useful for cropping into a dome
    unsigned int    numMeridians;
    float_t         *pointMeridians;   // count: numMeridians + 1, the different Y-latitudes of points
    float_t         *faceMeridians;    // count: numMeridians, the different Y-latitudes of the center of faces
    unsigned short  *faceAltitudes;    // count: numFaces, each face is paired with its altitude (Y-axis) (index to faceMeridians)
    // NOTE meridians differ by 1, pointMeridians also contain top and bottom, hence +1 count, faceMeridians are everything in between
};

#endif