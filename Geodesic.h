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
//  export obj file
//  points, faces, lines
//
//  how to call the shape:
//  solidName is the name of the platonic solid
//  v is the frequency number
//

#ifndef __Geodesic__Geometry__
#define __Geodesic__Geometry__

#pragma mark- generate lines[] from face data
#pragma mark- crop function

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class Geodesic{
    
public:
    // load a shape
    void icosahedron(int VFrequency);
    void octahedron(int VFrequency);
    void tetrahedron(int VFrequency);
    // crop sphere to dome
    void crop(float latitude); // top to bottom, 0 to 1, retain top portion
    
    // data
    void getPoints(double *points[], int *numPoints);
    void getLines(unsigned short *lines[], int *numLines);
    void getFaces(unsigned short *faces[], int *numFaces);
    // export
    void OBJ(char *&data, int &length);  // fills &data with OBJ file
    
    string  title; // Tetrahedron, Octahedron, Icosahedron
    unsigned int     v;
    double  *normals = NULL;  // vertex normals
    double  *faceNormals = NULL;
    // crop
    bool    *visiblePoints = NULL;  // size of numPoints, not size of *points array
    bool    *visibleLines = NULL;   // size of numLines, not size of *lines array
    bool    *visibleFaces = NULL;   // size of numFaces, not size of *faces array

private:

    void divideFaces(int vFreq);
    void removeDuplicatePoints();
    void spherize();
    void generateNormals();
    
    void loadIcosahedron();
    void loadOctahedron();
    void loadTetrahedron();
    
    double          *points = NULL;  // each a double[3]- [0]:x [1]:y [2]:z
    unsigned short  *lines = NULL;      // each an int[2]- [0]:index in *points [1]:index in *points
    unsigned short  *faces = NULL;      // each an int[3]- [0]:index in *points [1]:index in *points [2]:index in *points
    unsigned int    numPoints;
    unsigned int    numLines;
    unsigned int    numFaces;
    float           latitude;  // of crop
    
    // diagram
    int     *lineClass = NULL;       // size of numLines
    double  *lineClassLengths = NULL;
    void    initDiagramData();
    void    classifyLines();
};

#endif