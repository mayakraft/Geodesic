//
//  geodesic
//  OpenGL front-end
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

#ifndef __geodesic__mesh__
#define __geodesic__mesh__


/////////////////////////////////
// geodesic

void drawGeodesicTriangles(geodesicSphere *g);
void drawGeodesicLines(geodesicSphere *g);
void drawGeodesicPoints(geodesicSphere *g);

void drawDomeTriangles(geodesicDome *d);

/////////////////////////////////
// geodesic mesh
//
// the rest of this file has shapes that require generating
// new geometry outside of what is included in the geodesic class
typedef struct geodesicMeshNormals geodesicMeshNormals;
typedef struct geodesicMeshTriangles geodesicMeshTriangles;
typedef struct geodesicMeshSlicePoints geodesicMeshSlicePoints;
typedef struct geodesicMeshCropPlanes geodesicMeshCropPlanes;


void drawDomeMeshTriangles(geodesicDome *d, geodesicMeshTriangles *m);


// step 1: initialize the data (delete data after use)
geodesicMeshNormals makeMeshNormals(geodesicSphere *g);
geodesicMeshTriangles makeMeshTriangles(geodesicSphere *g, float scale);
geodesicMeshSlicePoints makeMeshSlicePoints(geodesicDome *g);
geodesicMeshCropPlanes makeMeshCropPlanes(geodesicDome *g);
void deleteMeshNormals(geodesicMeshNormals *m);
void deleteMeshTriangles(geodesicMeshTriangles *m);
void deleteSlicePoints(geodesicMeshSlicePoints *m);
void deleteCropPlanes(geodesicMeshCropPlanes *m);


// step 2: draw

// draw the geodesic sphere's normal lines: vertex, line, face normals
void drawGeodesicVertexNormalLines(geodesicMeshNormals *m);
void drawGeodesicLineNormalLines(geodesicMeshNormals *m);
void drawGeodesicFaceNormalLines(geodesicMeshNormals *m);

// draw triangle faces, that don't share vertices, able to be manipulated independently
void drawGeodesicExtrudedTriangles(geodesicMeshTriangles *mesh);

// extra tools
void drawGeodesicCropPlanes(geodesicMeshCropPlanes *m);

#endif