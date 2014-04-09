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
    double *points;
    int *lines;     // interface to the object model
    int *faces;
    int numPoints;
    int numLines;
    int numFaces;
    float *glTriangles = NULL;  // GL_TRIANGLES
    float *glNormals = NULL;  // GL_NORMALS
    int numGLTriangles;
    float *glLines = NULL;  // GL_LINES
    int numGLLinePoints;
    float *glPoints = NULL;  // GL_POINTS
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
