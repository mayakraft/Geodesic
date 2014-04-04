//
//  Mesh.h
//
//  Created by Robby on 3/27/14.
//  Copyright (c) 2014 Robby Kraft. All rights reserved.
//

#ifndef __Geodesic__Mesh__
#define __Geodesic__Mesh__

#include <iostream>

class Geodesic;

class GeodesicMesh{
public:
    void load(Geodesic* geodesic);
    void draw();  // (draw triangles)
    void drawPoints();
    void drawLines();
    void drawNormalLines();
    void drawFaceNormalLines();
    void log();

private:
    float *glTriangles = NULL;  // GL_TRIANGLES
    float *glNormals = NULL;  // GL_NORMALS
    int numTriangles;
    int numFaces;
    int numLines;
    float *glLines = NULL;  // GL_LINES
    int numLinePoints;
    float *glPoints = NULL;  // GL_POINTS
    int numPoints;
    // ornaments
    float *normalLines = NULL;
    float *normalFaces = NULL;
    float *faceNormalLines = NULL;

    void makeGLTriangles(Geodesic* geodesic);
    void extrudeTriangles(Geodesic* geodesic);
    void makeGLLines(Geodesic* geodesic);
    void makeNormals(Geodesic* geodesic);
    void makeNormalLines(Geodesic* geodesic);
    void makeFaceNormalLines(Geodesic* geodesic);
};

#endif
