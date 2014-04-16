#ifndef __Geodesic__Mesh__
#define __Geodesic__Mesh__

#include <iostream>

class Geodesic;

class GeodesicMesh{
public:
    void load(Geodesic* geodesic);
    void draw();  // (draw triangles)
    void drawExtrudedTriangles();
    void drawPoints();
    void drawLines();
    void drawNormalLines();
    void drawFaceNormalLines();
    void log();

private:
    int             numFaces;
    int             numLines;
    int             numPoints;
    int             numGLTriangles;
    int             numGLLinePoints;
    unsigned short  *faces;     //
    unsigned short  *lines;     // interface to the object model
    double          *points;    //
    float           *glTriangles = NULL;  // GL_TRIANGLES
    float           *glNormals = NULL;    // GL_NORMALS
    float           *glLines = NULL;      // GL_LINES
    float           *glPoints = NULL;     // GL_POINTS
    
    // ornaments
    float           *normalLines = NULL;
    float           *normalFaces = NULL;
    float           *faceNormalLines = NULL;

    void makeGLTriangles(Geodesic* geodesic);
    void extrudeTriangles(Geodesic* geodesic);
    void makeGLLines(Geodesic* geodesic);
    void makeNormals(Geodesic* geodesic);
    void makeNormalLines(Geodesic* geodesic);
    void makeFaceNormalLines(Geodesic* geodesic);
};

#endif
