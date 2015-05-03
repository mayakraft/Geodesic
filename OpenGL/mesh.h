//
//  geodesic
//  OpenGL front-end
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

#ifndef __geodesic__mesh__
#define __geodesic__mesh__

// generic draw functions

void drawTriangles(GLfloat *vertices, GLfloat *normals, unsigned short *faces, unsigned int numFaces);
void drawUniqueTriangles(GLfloat *vertices, GLfloat *normals, unsigned int numTriangles);

// geodesic

void geodesicDrawTriangles(geodesicSphere *g);
void geodesicDrawLines(geodesicSphere *g);
void geodesicDrawPoints(geodesicSphere *g);


// geodesic mesh

struct geodesicMeshNormals {
    float            *vertexNormalsLines,    *lineNormalsLines,    *faceNormalsLines;
    unsigned int     numVertexNormals,       numLineNormals,       numFaceNormals;
}; typedef struct geodesicMeshNormals geodesicMeshNormals;


struct geodesicMeshTriangles{
    unsigned int    numTriangles;
    float           *glTriangles,   *glTriangleNormals;
    float           shrink;  // shrink face
    // legacy data, get creative!
    unsigned short *pointReferences;  // length of glTriangles / 3 (not storing X,Y,Z), each pointing to original indices
}; typedef struct geodesicMeshTriangles geodesicMeshTriangles;


struct geodesicMeshCropPlanes{
    unsigned int    numPlanes;
    float           *glTriangles,   *glTriangleNormals;
}; typedef struct geodesicMeshCropPlanes geodesicMeshCropPlanes;


// fill structs, delete structs
geodesicMeshNormals makeMeshNormals(geodesicSphere *g);
geodesicMeshTriangles makeMeshTriangles(geodesicSphere *g, float scale);
geodesicMeshCropPlanes makeMeshCropPlanes(geodesicSphere *g);
void deleteMeshNormals(geodesicMeshNormals *m);
void deleteMeshTriangles(geodesicMeshTriangles *m);

// visually expose the geometry normals: (1) vertex, (2) line, (3) face normals
void geodesicMeshDrawVertexNormalLines(geodesicMeshNormals *m);
void geodesicMeshDrawLineNormalLines(geodesicMeshNormals *m);
void geodesicMeshDrawFaceNormalLines(geodesicMeshNormals *m);

// draw triangle faces, that don't share vertices, able to be manipulated independently
void geodesicMeshDrawExtrudedTriangles(geodesicMeshTriangles *mesh);

// extra tools
void geodesicMeshDrawCropPlanes(geodesicMeshCropPlanes *m);

// backend
void shrinkMeshFaces(geodesicMeshTriangles *m, geodesicSphere *g, float scale);

#endif
