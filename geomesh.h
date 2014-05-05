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

typedef struct geomeshNormals geomeshNormals;
struct geomeshNormals {
    float *vertexNormalsLines;
    float *lineNormalsLines;
    float *faceNormalsLines;
    unsigned int numVertexNormals;
    unsigned int numLineNormals;
    unsigned int numFaceNormals;
};

typedef struct geomeshTriangles geomeshTriangles;
struct geomeshTriangles{
    unsigned int numTriangles;
    float *glTriangles;
    float *glTriangleNormals;

    float shrink;  // shrink face
};

void geodesicMeshDrawVertexNormalLines(geomeshNormals *m);
void geodesicMeshDrawLineNormalLines(geomeshNormals *m);
void geodesicMeshDrawFaceNormalLines(geomeshNormals *m);
void geodesicMeshDrawExtrudedTriangles(geomeshTriangles *mesh);

geomeshNormals makeMeshNormals(geodesic *g);
geomeshTriangles makeMeshTriangles(geodesic *g, float scale);

void deleteMeshNormals(geomeshNormals *m);
void deleteMeshTriangles(geomeshTriangles *m);

#endif
