//
//  geodesic
//  OpenGL front-end
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

#ifndef __geodesic__mesh__
#define __geodesic__mesh__



// geodesic

void geodesicDrawTriangles(geodesicSphere *g);
void geodesicDrawLines(geodesicSphere *g);
void geodesicDrawPoints(geodesicSphere *g);



// geodesic mesh

typedef struct geomeshNormals geomeshNormals;
struct geomeshNormals {
    float           *vertexNormalsLines;
    float           *lineNormalsLines;
    float           *faceNormalsLines;
    unsigned int    numVertexNormals;
    unsigned int    numLineNormals;
    unsigned int    numFaceNormals;
};

typedef struct geomeshTriangles geomeshTriangles;
struct geomeshTriangles{
    unsigned int    numTriangles;
    float           *glTriangles;
    float           *glTriangleNormals;

    float           shrink;  // shrink face
};

typedef struct geomeshCropPlanes geomeshCropPlanes;
struct geomeshCropPlanes{
    unsigned int    numPlanes;
    float           *glTriangles;
    float           *glTriangleNormals;
};

void geodesicMeshDrawVertexNormalLines(geomeshNormals *m);
void geodesicMeshDrawLineNormalLines(geomeshNormals *m);
void geodesicMeshDrawFaceNormalLines(geomeshNormals *m);
void geodesicMeshDrawExtrudedTriangles(geomeshTriangles *mesh);

geomeshNormals makeMeshNormals(geodesicSphere *g);
geomeshTriangles makeMeshTriangles(geodesicSphere *g, float scale);
geomeshCropPlanes makeMeshCropPlanes(geodesicSphere *g);

void geodesicMeshDrawCropPlanes(geomeshCropPlanes *m);

void shrinkMeshFaces(geomeshTriangles *m, geodesicSphere *g, float scale);

void deleteMeshNormals(geomeshNormals *m);
void deleteMeshTriangles(geomeshTriangles *m);

#endif
