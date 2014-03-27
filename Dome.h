//
//  Dome.h
//  Domekit
//
//  Created by Robby on 1/28/13.
//  Copyright (c) 2013 Robby Kraft. All rights reserved.
//

#include <iostream>


class Dome{
private:
    
    int numPoints;
    int numLines;
    int numFaces;

    double *points = NULL;  // collections of float[3]- [0]:x [1]:y [2]:z
    int *lines = NULL;   // collections of int[2]- [0]:pointIndex1 [1]:pointIndex2
    int *faces = NULL;   // collections of int[3]- [0]:pointIndex1 [1]:pointIndex2 [2]:pointIndex3
    
    bool *visiblePoints = NULL;  // size of numPoints, not size of *points array
    bool *visibleLines = NULL;   // size of numLines, not size of *lines array
    bool *visibleFaces = NULL;   // size of numFaces, not size of *faces array
    
    int *lineClass = NULL;          // size of numLines
    double *lineClassLengths = NULL; // size of
    
    int v;
    int primitiveType; // 0:icosahedron, 1:octahedron, 2:tetrahedron
    
    void loadIcosahedron();
        void alignIcosahedron();
    void loadOctahedron();
    void loadTetrahedron();
    
    void divideFaces(int vFreq);
    void spherize();
    void connectTheDots();
    void removeDuplicateLines();
    void removeDuplicatePoints();
    
public:
    
    void initIcosahedron();
    void initOctahedron();
    void initTetrahedron();
    void geodecise(int vFreq);
    void classifyLines();
    
};



//    BOOL icosahedron; // 1 = icosa, 0 = octa

//-(id) init;
//-(id) initWithDome:(Dome*) input;
//-(id) initWithTriangle;
//-(void) geodecise:(int)v;
//-(void) geodeciseTriangle:(int)v;
//-(void) classifyLines;
//-(void) setIcosahedron;
//-(void) setOctahedron;
