//
//  geodesic
//  geometry builder
//  Copyright (c) 2013 Robby Kraft
//  MIT open source license
//

#ifndef __geodesic__geometry__
#define __geodesic__geometry__

// geometry data can be as precise as you allow
// make sure Platonic solid seeds are as precise
typedef float flo_t;
// typedef double flo_t;
// typedef long double flo_t;


typedef struct geodesicSphere geodesicSphere;
typedef struct geodesicDome geodesicDome;


geodesicSphere icosahedronSphere(unsigned int v);
geodesicSphere octahedronSphere(unsigned int v);
geodesicSphere tetrahedronSphere(unsigned int v);

// these are not yet implemented. the cropping algorithm is still needed
geodesicDome tetrahedronDome(unsigned int v, float crop);
geodesicDome octahedronDome(unsigned int v, float crop);
geodesicDome icosahedronDome(unsigned int v, float crop);


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
    unsigned short  *parentFace; // of the original platonic solid faces, from which did the point originate? size of numPoints
};

struct geodesicDome {

    geodesicSphere g;
    flo_t           *slicePoints;
    flo_t           numSlicePoints;
    // stuff for cropping a sphere into a dome
    unsigned int    numMeridians;
    flo_t           *pointMeridians;   // count: numMeridians + 1, the different major-axis-latitudes of points
    flo_t           *faceMeridians;    // count: numMeridians, the different major-axis-latitudes of the center of faces
    unsigned short  *faceAltitudes;    // count: numFaces, each face is paired with its altitude (major-axis-axis) (index to faceMeridians)
    unsigned int    *faceAltitudeCounts; // count: number of unique entries in faceAltitudes (numMeridians), how many triangles in each tier
    // NOTE meridians differ by 1, pointMeridians also contain top and bottom, hence +1 count, faceMeridians are everything in between
};

typedef struct geodesicAnalysis geodesicAnalysis;

geodesicAnalysis classifyLines(geodesicSphere *g);

struct geodesicAnalysis {
    double           *lineLengthValues;
    unsigned int    numLineLengths;      // the above array size
    unsigned int    *lineLengthTypes;    // count: numLines, pointers to indices in lineLengthValues
};

#endif