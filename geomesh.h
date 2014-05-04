//
//  OpenGL front-end for geodesic.h
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

#ifndef __geodesic__mesh__
#define __geodesic__mesh__


// geodesic

void geodesicDrawTriangles(geodesic *g);
void geodesicDrawLines(geodesic *g);
void geodesicDrawPoints(geodesic *g);


// geodesic mesh

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
    float *glTriangleNormals;
};

geomesh makeMesh(geodesic *g);

void freeMesh(geomesh *m);

#endif
