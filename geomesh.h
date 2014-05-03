//
//  OpenGL front-end for geodesic.h
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

#ifndef __Geodesic__Mesh__
#define __Geodesic__Mesh__

typedef struct geomesh geomesh;

struct geomesh {
    float *vertexNormalsLines;
    float *lineNormalsLines;
    float *faceNormalsLines;
    unsigned int numVertexNormals;
    unsigned int numLineNormals;
    unsigned int numFaceNormals;
    
    unsigned int numTriangles;
    float *glTriangles;
};

geomesh makeMesh(geodesic *g);

void geodesicDrawTriangles(geodesic *g);
void geodesicDrawLines(geodesic *g);
void geodesicDrawPoints(geodesic *g);

//void loadMesh(geomesh *mesh, geodesic *geo);

/*
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
    unsigned int    numFaces;
    unsigned int    numLines;
    unsigned int    numPoints;
    unsigned int    numGLTriangles;
    unsigned int    numGLLinePoints;
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
*/

#endif
