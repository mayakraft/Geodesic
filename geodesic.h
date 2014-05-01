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

#pragma mark- generate lines[] from face data
#pragma mark- crop function

// typedef to GLfloat, float if using OpenGL
// or double, long double if you want precision
typedef float floater;

typedef struct geodesic geodesic;

struct geodesic {
    
    floater         *points;  // each a double[3]- [0]:x [1]:y [2]:z
    unsigned short  *lines;   // each an int[2]- [0]:index in *points [1]:index in *points
    unsigned short  *faces;   // each an int[3]- [0]:index in *points [1]:index in *points [2]:index in *points
    
    unsigned int    numPoints;
    unsigned int    numLines;
    unsigned int    numFaces;

    floater         *pointNormals;
    floater         *lineNormals;
    floater         *faceNormals;
};

geodesic icosahedron(int v);
geodesic octahedron(int v);
geodesic tetrahedron(int v);

geodesic tetrahedronDome(int v, float crop);
geodesic octahedronDome(int v, float crop);
geodesic icosahedronDome(int v, float crop);

#endif