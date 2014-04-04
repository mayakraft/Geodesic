//
//
//  geodesic geometry
//
//  Created by Robby on 3/26/14.
//  Copyright (c) 2013 Robby Kraft. All rights reserved.
//
//  Tetrahedra, Octahedra, Icosahedra
//
//  face subdivide
//  spherize (geodecise)
//
//  ?: crop sphere
//
//  geometry data:
//    OBJ file format
//   points and faces (and lines, not in OBJ file)
//

// move to instruction builder:
//   lineClass_ mirror array of lines_, values are 1, 2, 3 (which group each belongs to)
//   - hidden lines and points which lie below ground level
//


#pragma mark- generate lines[] from face data
#pragma mark- crop function


#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class Geodesic{
    
public:
    
    void icosahedron(int VFrequency);
    void octahedron(int VFrequency);
    void tetrahedron(int VFrequency);

    int numPoints;
    int numLines;
    int numFaces;

    double *points = NULL;  // each a double[3]- [0]:x [1]:y [2]:z
    int *lines = NULL;      // each an int[2]- [0]:index in *points [1]:index in *points
    int *faces = NULL;      // each an int[3]- [0]:index in *points [1]:index in *points [2]:index in *points
    
    double *normals = NULL;  // vertex normals
    double *faceNormals = NULL;
    
    int v;

private:
    
    void loadIcosahedron();
    void loadOctahedron();
    void loadTetrahedron();
    void alignIcosahedron();
    void alignTetrahedron();
    
    void divideFaces(int vFreq);
    void removeDuplicatePoints();
    void spherize();
    void generateNormals();

    // crop
    bool *visiblePoints = NULL;  // size of numPoints, not size of *points array
    bool *visibleLines = NULL;   // size of numLines, not size of *lines array
    bool *visibleFaces = NULL;   // size of numFaces, not size of *faces array
    int *lineClass = NULL;       // size of numLines
    double *lineClassLengths = NULL;
    void crop(float c);  //to do
    void initCropData();
    void connectTheDots();
    void classifyLines();

    void makeOBJ(string filename);
};
