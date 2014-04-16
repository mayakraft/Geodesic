#ifndef __Geodesic__Mesh__
#define __Geodesic__Mesh__

#include <iostream>

class Geodesic;

class GeodesicMesh{
public:
    void load(Geodesic* _geodesic);
    void draw();   // draw faces
    void drawExtrudedTriangles();
    void drawPoints();
    void drawLines();
    void drawNormalLines();
    void drawFaceNormalLines();
    void log();

private:
    Geodesic *geodesic;
    int             numFaces;
    int             numLines;
    int             numPoints;
    int             numGLTriangles;
    int             numGLLinePoints;
    unsigned short  *faces;     //
    unsigned short  *lines;     // interface to the object model
    double          *points;    //
    float           *glEachTriangles = NULL;  // GL_TRIANGLES, with unique vertices for face manipulation
    float           *glNormals = NULL;    // GL_NORMALS
    float           *glLines = NULL;      // GL_LINES
    float           *glPoints = NULL;     // GL_POINTS
    
    // ornaments
    float           *normalLines = NULL;
    float           *normalFaces = NULL;
    float           *faceNormalLines = NULL;

    void makeGLPoints();
    void makeGLTriangles();
    void extrudeTriangles(float scale);
    void makeGLLines();
    void makeNormals();
    void makeNormalLines();
    void makeFaceNormalLines();
};

#endif
