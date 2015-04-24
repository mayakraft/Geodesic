//
//  geodesic
//  geometry builder
//  Copyright (c) 2013 Robby Kraft
//  MIT open source license
//

#ifndef __geodesic__geometry__
#define __geodesic__geometry__

typedef struct geodesicSphere geodesicSphere;
typedef struct geodesicDome geodesicDome;


geodesicSphere icosahedronSphere(int v);
geodesicSphere octahedronSphere(int v);
geodesicSphere tetrahedronSphere(int v);

// these are not yet implemented. the cropping algorithm is still needed
geodesicDome tetrahedronDome(int v, float crop);
geodesicDome octahedronDome(int v, float crop);
geodesicDome icosahedronDome(int v, float crop);


void deleteGeodesicSphere(geodesicSphere *g);
void deleteGeodesicDome(geodesicDome *d);

// flo_t type is cast to float, double, or long double
// and defined in platonic.h
struct geodesicSphere {

    unsigned int    numPoints;
    unsigned int    numLines;
    unsigned int    numFaces;

    flo_t           *points;  // count: numPoints * 3
    unsigned short  *lines;   // count: numLines * 2    - indices in *points array
    unsigned short  *faces;   // count: numFaces * 3    - indices in *points array

    flo_t           *pointNormals;  // count: numPoints * 3
    flo_t           *lineNormals;   // count: numLines * 3
    flo_t           *faceNormals;   // count: numFaces * 3  

    unsigned int frequency;  

    // legacy data. get creative!
    flo_t           *pointsNotSpherized;
    flo_t           *pointsDeltaSpherized;  // difference between spherized point and original
};

struct geodesicDome {

    geodesicSphere g;
    // stuff for cropping a sphere into a dome
    unsigned int    numMeridians;
    flo_t           *pointMeridians;   // count: numMeridians + 1, the different Y-latitudes of points
    flo_t           *faceMeridians;    // count: numMeridians, the different Y-latitudes of the center of faces
    unsigned short  *faceAltitudes;    // count: numFaces, each face is paired with its altitude (Y-axis) (index to faceMeridians)
    // NOTE meridians differ by 1, pointMeridians also contain top and bottom, hence +1 count, faceMeridians are everything in between
};


#endif