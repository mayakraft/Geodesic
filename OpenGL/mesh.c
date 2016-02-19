#include "../geodesic.c"

#ifdef __APPLE__
# if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
#  import <OpenGLES/ES1/gl.h>
# elif TARGET_OS_IPHONE
#  import <OpenGLES/ES1/gl.h>
# else
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# endif
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "mesh.h"

#define GEODESIC_MESH_VERTEX_NORMAL_LENGTH 1.045
#define GEODESIC_MESH_LINE_NORMAL_LENGTH 1.035
#define GEODESIC_MESH_FACE_NORMAL_LENGTH 1.025

// geodesic

void drawGeodesicTriangles(geodesicSphere *g){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, g->points);
	glNormalPointer(GL_FLOAT, 0, g->pointNormals);
	glDrawElements(GL_TRIANGLES, g->numFaces*3, GL_UNSIGNED_SHORT, g->faces);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGeodesicLines(geodesicSphere *g){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, g->points);
	glNormalPointer(GL_FLOAT, 0, g->pointNormals);
	glDrawElements(GL_LINES, g->numLines*2, GL_UNSIGNED_SHORT, g->lines);
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGeodesicPoints(geodesicSphere *g){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, g->points);
	glNormalPointer(GL_FLOAT, 0, g->pointNormals);
	glDrawArrays(GL_POINTS, 0, g->numPoints);
	
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// dome
void drawDomeTriangles(geodesicDome *d){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, d->sphere.points);
	glNormalPointer(GL_FLOAT, 0, d->sphere.pointNormals);
	// glDrawElements(GL_TRIANGLES, d->numFaces*3, GL_UNSIGNED_SHORT, d->faces);
	glDrawArrays(GL_TRIANGLES, 0, d->numVisibleTriangles*3);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// mesh

struct geodesicMeshNormals {
	float            *vertexNormalsLines,    *lineNormalsLines,    *faceNormalsLines;
	unsigned int     numVertexNormals,       numLineNormals,       numFaceNormals;
};

struct geodesicMeshTriangles{
	unsigned int    numTriangles;
	float           *glTriangles,   *glTriangleNormals;
	float           shrink;  // shrink face
	// legacy data, get creative!
	unsigned short *pointReferences;  // length of glTriangles / 3 (not storing X,Y,Z), each pointing to original indices
};

struct geodesicMeshSlicePoints{
	unsigned int    numPoints;
	float           *points;
};


struct geodesicMeshCropPlanes{
	unsigned int    numPlanes;
	float           *glTriangles,   *glTriangleNormals;
};


void drawDomeMeshTriangles(geodesicDome *d, geodesicMeshTriangles *m){
	glPushMatrix();
	glScalef(m->shrink, m->shrink, m->shrink);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m->glTriangles);
	glNormalPointer(GL_FLOAT, 0, m->glTriangleNormals);
//    glDrawArrays(GL_TRIANGLES, 0, _geodesicModel.mesh.numTriangles*3);
	glDrawArrays(GL_TRIANGLES, 0, d->numVisibleTriangles*3);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

 


void drawGeodesicVertexNormalLines(geodesicMeshNormals *m){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m->vertexNormalsLines);
	glDrawArrays(GL_LINES, 0, m->numVertexNormals*2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGeodesicLineNormalLines(geodesicMeshNormals *m){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m->lineNormalsLines);
	glDrawArrays(GL_LINES, 0, m->numLineNormals*2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGeodesicFaceNormalLines(geodesicMeshNormals *m){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m->faceNormalsLines);
	glDrawArrays(GL_LINES, 0, m->numFaceNormals*2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGeodesicExtrudedTriangles(geodesicMeshTriangles *mesh){
	glPushMatrix();
	glScalef(mesh->shrink, mesh->shrink, mesh->shrink);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mesh->glTriangles);
	glNormalPointer(GL_FLOAT, 0, mesh->glTriangleNormals);
	glDrawArrays(GL_TRIANGLES, 0, mesh->numTriangles*3);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void drawGeodesicCropPlanes(geodesicMeshCropPlanes *m){
	glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m->glTriangles);
	glNormalPointer(GL_FLOAT, 0, m->glTriangleNormals);
	glDrawArrays(GL_TRIANGLES, 0, m->numPlanes*3);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

geodesicMeshNormals makeMeshNormals(geodesicSphere *g){
	geodesicMeshNormals mesh;
	mesh.vertexNormalsLines = malloc(sizeof(GLfloat)*(g->numPoints)*3*2);
	for(int i = 0; i < g->numPoints; i++){
		mesh.vertexNormalsLines[i*6+0+0] = g->pointNormals[i*3+0];
		mesh.vertexNormalsLines[i*6+0+1] = g->pointNormals[i*3+1];
		mesh.vertexNormalsLines[i*6+0+2] = g->pointNormals[i*3+2];
		mesh.vertexNormalsLines[i*6+3+0] = g->pointNormals[i*3+0] * GEODESIC_MESH_VERTEX_NORMAL_LENGTH;
		mesh.vertexNormalsLines[i*6+3+1] = g->pointNormals[i*3+1] * GEODESIC_MESH_VERTEX_NORMAL_LENGTH;
		mesh.vertexNormalsLines[i*6+3+2] = g->pointNormals[i*3+2] * GEODESIC_MESH_VERTEX_NORMAL_LENGTH;
	}
	mesh.lineNormalsLines = malloc(sizeof(GLfloat)*g->numLines*3*2);
	for(int i = 0; i < g->numLines; i++){
		mesh.lineNormalsLines[i*6+0+0] = g->lineNormals[i*3+0];
		mesh.lineNormalsLines[i*6+0+1] = g->lineNormals[i*3+1];
		mesh.lineNormalsLines[i*6+0+2] = g->lineNormals[i*3+2];
		mesh.lineNormalsLines[i*6+3+0] = g->lineNormals[i*3+0] * GEODESIC_MESH_LINE_NORMAL_LENGTH;
		mesh.lineNormalsLines[i*6+3+1] = g->lineNormals[i*3+1] * GEODESIC_MESH_LINE_NORMAL_LENGTH;
		mesh.lineNormalsLines[i*6+3+2] = g->lineNormals[i*3+2] * GEODESIC_MESH_LINE_NORMAL_LENGTH;
	}
	mesh.faceNormalsLines = malloc(sizeof(GLfloat)*g->numFaces*3*2);
	for(int i = 0; i < g->numFaces; i++){
		mesh.faceNormalsLines[i*6+0+0] = g->faceNormals[i*3+0];
		mesh.faceNormalsLines[i*6+0+1] = g->faceNormals[i*3+1];
		mesh.faceNormalsLines[i*6+0+2] = g->faceNormals[i*3+2];
		mesh.faceNormalsLines[i*6+3+0] = g->faceNormals[i*3+0] * GEODESIC_MESH_FACE_NORMAL_LENGTH;
		mesh.faceNormalsLines[i*6+3+1] = g->faceNormals[i*3+1] * GEODESIC_MESH_FACE_NORMAL_LENGTH;
		mesh.faceNormalsLines[i*6+3+2] = g->faceNormals[i*3+2] * GEODESIC_MESH_FACE_NORMAL_LENGTH;
	}

	mesh.numVertexNormals = g->numPoints;
	mesh.numLineNormals = g->numLines;
	mesh.numFaceNormals = g->numFaces;

	return mesh;
}

void extrudeTriangles(geodesicMeshTriangles *mesh, geodesicSphere *g, float distance){
	for(int i = 0; i < g->numFaces; i++){
		// triangle vertex 1: X Y and Z
		mesh->glTriangles[i*9 + 0*3 + 0] += g->faceNormals[0+i*3] * distance;
		mesh->glTriangles[i*9 + 0*3 + 1] += g->faceNormals[1+i*3] * distance;
		mesh->glTriangles[i*9 + 0*3 + 2] += g->faceNormals[2+i*3] * distance;
		// triangle vertex 2: X Y and Z
		mesh->glTriangles[i*9 + 1*3 + 0] += g->faceNormals[0+i*3] * distance;
		mesh->glTriangles[i*9 + 1*3 + 1] += g->faceNormals[1+i*3] * distance;
		mesh->glTriangles[i*9 + 1*3 + 2] += g->faceNormals[2+i*3] * distance;
		// triangle vertex 3: X Y and Z
		mesh->glTriangles[i*9 + 2*3 + 0] += g->faceNormals[0+i*3] * distance;
		mesh->glTriangles[i*9 + 2*3 + 1] += g->faceNormals[1+i*3] * distance;
		mesh->glTriangles[i*9 + 2*3 + 2] += g->faceNormals[2+i*3] * distance;
	}
}

void shrinkMeshFaces(geodesicMeshTriangles *m, geodesicSphere *g, float scale){
	m->shrink = scale;
	for(int i = 0; i < g->numFaces; i++){
		// triangle vertex 1: X Y and Z
		m->glTriangles[i*9 + 0*3 + 0] = g->points[ g->faces[0+i*3]*3 + 0 ];
		m->glTriangles[i*9 + 0*3 + 1] = g->points[ g->faces[0+i*3]*3 + 1 ];
		m->glTriangles[i*9 + 0*3 + 2] = g->points[ g->faces[0+i*3]*3 + 2 ];
		// triangle vertex 2: X Y and Z
		m->glTriangles[i*9 + 1*3 + 0] = g->points[ g->faces[1+i*3]*3 + 0 ];
		m->glTriangles[i*9 + 1*3 + 1] = g->points[ g->faces[1+i*3]*3 + 1 ];
		m->glTriangles[i*9 + 1*3 + 2] = g->points[ g->faces[1+i*3]*3 + 2 ];
		// triangle vertex 3: X Y and Z
		m->glTriangles[i*9 + 2*3 + 0] = g->points[ g->faces[2+i*3]*3 + 0 ];
		m->glTriangles[i*9 + 2*3 + 1] = g->points[ g->faces[2+i*3]*3 + 1 ];
		m->glTriangles[i*9 + 2*3 + 2] = g->points[ g->faces[2+i*3]*3 + 2 ];
	}
	extrudeTriangles(m, g, (1/scale - 1));
}


geodesicMeshSlicePoints makeMeshSlicePoints(geodesicDome *g){
	geodesicMeshSlicePoints slices;
	slices.numPoints = g->numMeridians;
	slices.points = malloc(sizeof(float_t)*3*(g->numMeridians));
	for(int i = 0; i < g->numMeridians; i++){
		slices.points[i*3+0] = g->slicePoints[i];
		slices.points[i*3+1] = 0.0;
		slices.points[i*3+2] = 0.0;
	}
	return slices;
}

geodesicMeshCropPlanes makeMeshCropPlanes(geodesicDome *g){
	 geodesicMeshCropPlanes planes;
	 planes.numPlanes = g->numMeridians+1;
	 planes.glTriangles = malloc(sizeof(float_t)*3*3*(g->numMeridians+1));
	 for(int i = 0; i < g->numMeridians+1; i++){
		 planes.glTriangles[i*9+0] = 0.0;  planes.glTriangles[i*9+1] = g->pointMeridians[i];   planes.glTriangles[i*9+2] = sqrtf(3)/2 + sqrtf(3)/4;
		 planes.glTriangles[i*9+3] =-1.0;  planes.glTriangles[i*9+4] = g->pointMeridians[i];   planes.glTriangles[i*9+5] = 0.0 - sqrtf(3)/4;
		 planes.glTriangles[i*9+6] = 1.0;  planes.glTriangles[i*9+7] = g->pointMeridians[i];   planes.glTriangles[i*9+8] = 0.0 - sqrtf(3)/4;
//         planes.glTriangles[i*9+0] = 0.0;  planes.glTriangles[i*9+1] = g->faceMeridians[i];   planes.glTriangles[i*9+2] = sqrtf(3)/2 + sqrtf(3)/4;
//         planes.glTriangles[i*9+3] =-1.0;  planes.glTriangles[i*9+4] = g->faceMeridians[i];   planes.glTriangles[i*9+5] = 0.0 - sqrtf(3)/4;
//         planes.glTriangles[i*9+6] = 1.0;  planes.glTriangles[i*9+7] = g->faceMeridians[i];   planes.glTriangles[i*9+8] = 0.0 - sqrtf(3)/4;
	 }
	 planes.glTriangleNormals = malloc(sizeof(float_t)*3*3*(g->numMeridians+1));
	 for(int i = 0; i < g->numMeridians+1; i++){
		 planes.glTriangleNormals[i*9+0] = 0.0;  planes.glTriangleNormals[i*9+1] = 1.0;   planes.glTriangleNormals[i*9+2] = 0.0;
		 planes.glTriangleNormals[i*9+3] = 0.0;  planes.glTriangleNormals[i*9+4] = 1.0;   planes.glTriangleNormals[i*9+5] = 0.0;
		 planes.glTriangleNormals[i*9+6] = 0.0;  planes.glTriangleNormals[i*9+7] = 1.0;   planes.glTriangleNormals[i*9+8] = 0.0;
	 }
	 return planes;
 }

geodesicMeshTriangles makeMeshTriangles(geodesicSphere *g, float shrink){
	geodesicMeshTriangles mesh;
	mesh.shrink = shrink;
	mesh.glTriangles = malloc(sizeof(GLfloat)*g->numFaces*3*3);
	// legacy memory
		mesh.pointReferences = malloc(sizeof(GLfloat)*g->numFaces*3);
	for(int i = 0; i < g->numFaces; i++){
		// triangle vertex 1: X Y and Z
		mesh.glTriangles[i*9 + 0*3 + 0] = g->points[ g->faces[0+i*3]*3 + 0 ];
		mesh.glTriangles[i*9 + 0*3 + 1] = g->points[ g->faces[0+i*3]*3 + 1 ];
		mesh.glTriangles[i*9 + 0*3 + 2] = g->points[ g->faces[0+i*3]*3 + 2 ];
		// triangle vertex 2: X Y and Z
		mesh.glTriangles[i*9 + 1*3 + 0] = g->points[ g->faces[1+i*3]*3 + 0 ];
		mesh.glTriangles[i*9 + 1*3 + 1] = g->points[ g->faces[1+i*3]*3 + 1 ];
		mesh.glTriangles[i*9 + 1*3 + 2] = g->points[ g->faces[1+i*3]*3 + 2 ];
		// triangle vertex 3: X Y and Z
		mesh.glTriangles[i*9 + 2*3 + 0] = g->points[ g->faces[2+i*3]*3 + 0 ];
		mesh.glTriangles[i*9 + 2*3 + 1] = g->points[ g->faces[2+i*3]*3 + 1 ];
		mesh.glTriangles[i*9 + 2*3 + 2] = g->points[ g->faces[2+i*3]*3 + 2 ];
		// legacy
			mesh.pointReferences[i*3 + 0] = g->faces[0+i*3];
			mesh.pointReferences[i*3 + 1] = g->faces[1+i*3];
			mesh.pointReferences[i*3 + 2] = g->faces[2+i*3];
	}
	extrudeTriangles(&mesh, g, (1/shrink - 1));
	
// TRADITIONAL CURVED FACE NORMALS
//    mesh.glTriangleNormals = malloc(sizeof(GLfloat)*g->numFaces*3*3);
//    for(int i = 0; i < g->numFaces; i++){
//        // triangle vertex 1: X Y and Z
//        mesh.glTriangleNormals[i*9 + 0*3 + 0] = g->pointNormals[ g->faces[0+i*3]*3 + 0 ];
//        mesh.glTriangleNormals[i*9 + 0*3 + 1] = g->pointNormals[ g->faces[0+i*3]*3 + 1 ];
//        mesh.glTriangleNormals[i*9 + 0*3 + 2] = g->pointNormals[ g->faces[0+i*3]*3 + 2 ];
//        // triangle vertex 2: X Y and Z
//        mesh.glTriangleNormals[i*9 + 1*3 + 0] = g->pointNormals[ g->faces[1+i*3]*3 + 0 ];
//        mesh.glTriangleNormals[i*9 + 1*3 + 1] = g->pointNormals[ g->faces[1+i*3]*3 + 1 ];
//        mesh.glTriangleNormals[i*9 + 1*3 + 2] = g->pointNormals[ g->faces[1+i*3]*3 + 2 ];
//        // triangle vertex 3: X Y and Z
//        mesh.glTriangleNormals[i*9 + 2*3 + 0] = g->pointNormals[ g->faces[2+i*3]*3 + 0 ];
//        mesh.glTriangleNormals[i*9 + 2*3 + 1] = g->pointNormals[ g->faces[2+i*3]*3 + 1 ];
//        mesh.glTriangleNormals[i*9 + 2*3 + 2] = g->pointNormals[ g->faces[2+i*3]*3 + 2 ];
//    }
	
	// DISCO BALL MIRROR NORMALS
	mesh.glTriangleNormals = malloc(sizeof(GLfloat)*g->numFaces*3*3);
	for(int i = 0; i < g->numFaces; i++){
		// triangle vertex 1: X Y and Z
		mesh.glTriangleNormals[i*9 + 0*3 + 0] = g->faceNormals[ i*3 + 0 ];
		mesh.glTriangleNormals[i*9 + 0*3 + 1] = g->faceNormals[ i*3 + 1 ];
		mesh.glTriangleNormals[i*9 + 0*3 + 2] = g->faceNormals[ i*3 + 2 ];
		// triangle vertex 2: X Y and Z
		mesh.glTriangleNormals[i*9 + 1*3 + 0] = g->faceNormals[ i*3 + 0 ];
		mesh.glTriangleNormals[i*9 + 1*3 + 1] = g->faceNormals[ i*3 + 1 ];
		mesh.glTriangleNormals[i*9 + 1*3 + 2] = g->faceNormals[ i*3 + 2 ];
		// triangle vertex 3: X Y and Z
		mesh.glTriangleNormals[i*9 + 2*3 + 0] = g->faceNormals[ i*3 + 0 ];
		mesh.glTriangleNormals[i*9 + 2*3 + 1] = g->faceNormals[ i*3 + 1 ];
		mesh.glTriangleNormals[i*9 + 2*3 + 2] = g->faceNormals[ i*3 + 2 ];
	}
	
	mesh.numTriangles = g->numFaces;

	return mesh;
}

void deleteMeshNormals(geodesicMeshNormals *m){
	m->numVertexNormals = 0;
	m->numLineNormals = 0;
	m->numFaceNormals = 0;
	if(m->vertexNormalsLines){
		free(m->vertexNormalsLines);
		m->vertexNormalsLines = NULL;
	}
	if(m->lineNormalsLines){
		free(m->lineNormalsLines);
		m->lineNormalsLines = NULL;
	}
	if(m->faceNormalsLines){
		free(m->faceNormalsLines);
		m->faceNormalsLines = NULL;
	}
//    free(m);
}

void deleteSlicePoints(geodesicMeshSlicePoints *m){
		m->numPoints = 0;
		if(m->points){
			free(m->points);
			m->points = NULL;
		}
//    free(m);
	}

void deleteCropPlanes(geodesicMeshCropPlanes *m){
	m->numPlanes = 0;
	if(m->glTriangles){
		free(m->glTriangles);
		m->glTriangles = NULL;
	}
	if(m->glTriangleNormals){
		free(m->glTriangleNormals);
		m->glTriangleNormals = NULL;
	}
//    free(m);
}

void deleteMeshTriangles(geodesicMeshTriangles *m){
	m->numTriangles = 0;
	if(m->glTriangles){
		free(m->glTriangles);
		m->glTriangles = NULL;
	}
	if(m->glTriangleNormals){
		free(m->glTriangleNormals);
		m->glTriangleNormals = NULL;
	}
	//    free(m);
}
