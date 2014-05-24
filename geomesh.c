#include "geomesh.h"
#include <OpenGLES/ES1/gl.h>

// geodesic

void geodesicDrawTriangles(geodesic *g){
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, g->points);
    glNormalPointer(GL_FLOAT, 0, g->pointNormals);
    glDrawElements(GL_TRIANGLES, g->numFaces*3, GL_UNSIGNED_SHORT, g->faces);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicDrawLines(geodesic *g){
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, g->points);
    glNormalPointer(GL_FLOAT, 0, g->pointNormals);
    glDrawElements(GL_LINES, g->numLines*2, GL_UNSIGNED_SHORT, g->lines);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicDrawPoints(geodesic *g){
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, g->points);
    glNormalPointer(GL_FLOAT, 0, g->pointNormals);
    glDrawArrays(GL_POINTS, 0, g->numPoints);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}


// mesh

// normal line indicators: vertices, lines, faces
// extruded triangle faces and normals

void geodesicMeshDrawVertexNormalLines(geomeshNormals *m){
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m->vertexNormalsLines);
    glDrawArrays(GL_LINES, 0, m->numVertexNormals*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicMeshDrawLineNormalLines(geomeshNormals *m){
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m->lineNormalsLines);
    glDrawArrays(GL_LINES, 0, m->numLineNormals*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicMeshDrawFaceNormalLines(geomeshNormals *m){
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m->faceNormalsLines);
    glDrawArrays(GL_LINES, 0, m->numFaceNormals*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicMeshDrawExtrudedTriangles(geomeshTriangles *mesh){
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

void geodesicMeshDrawCropPlanes(geomeshCropPlanes *m){
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m->glTriangles);
//    glNormalPointer(GL_FLOAT, 0, m->glTriangleNormals);
    glDrawArrays(GL_TRIANGLES, 0, m->numPlanes*3*3);
//    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

geomeshNormals makeMeshNormals(geodesic *g){
    geomeshNormals mesh;
    mesh.vertexNormalsLines = malloc(sizeof(GLfloat)*(g->numPoints)*3*2);
    for(int i = 0; i < g->numPoints; i++){
        mesh.vertexNormalsLines[i*6+0+X] = g->pointNormals[i*3+X];
        mesh.vertexNormalsLines[i*6+0+Y] = g->pointNormals[i*3+Y];
        mesh.vertexNormalsLines[i*6+0+Z] = g->pointNormals[i*3+Z];
        mesh.vertexNormalsLines[i*6+3+X] = g->pointNormals[i*3+X]*1.1;
        mesh.vertexNormalsLines[i*6+3+Y] = g->pointNormals[i*3+Y]*1.1;
        mesh.vertexNormalsLines[i*6+3+Z] = g->pointNormals[i*3+Z]*1.1;
    }
    mesh.lineNormalsLines = malloc(sizeof(GLfloat)*g->numLines*3*2);
    for(int i = 0; i < g->numLines; i++){
        mesh.lineNormalsLines[i*6+0+X] = g->lineNormals[i*3+X];
        mesh.lineNormalsLines[i*6+0+Y] = g->lineNormals[i*3+Y];
        mesh.lineNormalsLines[i*6+0+Z] = g->lineNormals[i*3+Z];
        mesh.lineNormalsLines[i*6+3+X] = g->lineNormals[i*3+X]*1.05;
        mesh.lineNormalsLines[i*6+3+Y] = g->lineNormals[i*3+Y]*1.05;
        mesh.lineNormalsLines[i*6+3+Z] = g->lineNormals[i*3+Z]*1.05;
    }
    mesh.faceNormalsLines = malloc(sizeof(GLfloat)*g->numFaces*3*2);
    for(int i = 0; i < g->numFaces; i++){
        mesh.faceNormalsLines[i*6+0+X] = g->faceNormals[i*3+X];
        mesh.faceNormalsLines[i*6+0+Y] = g->faceNormals[i*3+Y];
        mesh.faceNormalsLines[i*6+0+Z] = g->faceNormals[i*3+Z];
        mesh.faceNormalsLines[i*6+3+X] = g->faceNormals[i*3+X]*1.025;
        mesh.faceNormalsLines[i*6+3+Y] = g->faceNormals[i*3+Y]*1.025;
        mesh.faceNormalsLines[i*6+3+Z] = g->faceNormals[i*3+Z]*1.025;
    }

    mesh.numVertexNormals = g->numPoints;
    mesh.numLineNormals = g->numLines;
    mesh.numFaceNormals = g->numFaces;

    return mesh;
}

void extrudeTriangles(geomeshTriangles *mesh, geodesic *g, float distance){
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

void shrinkMeshFaces(geomeshTriangles *m, geodesic *g, float scale){
    m->shrink = scale;
    for(int i = 0; i < g->numFaces; i++){
        // triangle vertex 1: X Y and Z
        m->glTriangles[i*9 + 0*3 + 0] = g->points[ g->faces[0+i*3]*3 + X ];
        m->glTriangles[i*9 + 0*3 + 1] = g->points[ g->faces[0+i*3]*3 + Y ];
        m->glTriangles[i*9 + 0*3 + 2] = g->points[ g->faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        m->glTriangles[i*9 + 1*3 + 0] = g->points[ g->faces[1+i*3]*3 + X ];
        m->glTriangles[i*9 + 1*3 + 1] = g->points[ g->faces[1+i*3]*3 + Y ];
        m->glTriangles[i*9 + 1*3 + 2] = g->points[ g->faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        m->glTriangles[i*9 + 2*3 + 0] = g->points[ g->faces[2+i*3]*3 + X ];
        m->glTriangles[i*9 + 2*3 + 1] = g->points[ g->faces[2+i*3]*3 + Y ];
        m->glTriangles[i*9 + 2*3 + 2] = g->points[ g->faces[2+i*3]*3 + Z ];
    }
    extrudeTriangles(m, g, (1/scale - 1));
}

geomeshCropPlanes makeMeshCropPlanes(geodesic *g){
    geomeshCropPlanes planes;
    planes.numPlanes = g->numMeridians;
    planes.glTriangles = malloc(sizeof(float_)*3*3*g->numMeridians);
    for(int i = 0; i < g->numMeridians; i++){
        planes.glTriangles[i+0] = 0.0;  planes.glTriangles[i+1] = g->cropMeridians[i];   planes.glTriangles[i+2] = sqrtf(3)/2 - sqrtf(3)/4;
        planes.glTriangles[i+3] = 1.0;  planes.glTriangles[i+4] = g->cropMeridians[i];   planes.glTriangles[i+5] = 0.0 - sqrtf(3)/4;
        planes.glTriangles[i+6] =-1.0;  planes.glTriangles[i+7] = g->cropMeridians[i];   planes.glTriangles[i+8] = 0.0 - sqrtf(3)/4;
    }
    return planes;
}

geomeshTriangles makeMeshTriangles(geodesic *g, float shrink){
    geomeshTriangles mesh;
    mesh.shrink = shrink;
    mesh.glTriangles = malloc(sizeof(GLfloat)*g->numFaces*3*3);
    for(int i = 0; i < g->numFaces; i++){
        // triangle vertex 1: X Y and Z
        mesh.glTriangles[i*9 + 0*3 + 0] = g->points[ g->faces[0+i*3]*3 + X ];
        mesh.glTriangles[i*9 + 0*3 + 1] = g->points[ g->faces[0+i*3]*3 + Y ];
        mesh.glTriangles[i*9 + 0*3 + 2] = g->points[ g->faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        mesh.glTriangles[i*9 + 1*3 + 0] = g->points[ g->faces[1+i*3]*3 + X ];
        mesh.glTriangles[i*9 + 1*3 + 1] = g->points[ g->faces[1+i*3]*3 + Y ];
        mesh.glTriangles[i*9 + 1*3 + 2] = g->points[ g->faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        mesh.glTriangles[i*9 + 2*3 + 0] = g->points[ g->faces[2+i*3]*3 + X ];
        mesh.glTriangles[i*9 + 2*3 + 1] = g->points[ g->faces[2+i*3]*3 + Y ];
        mesh.glTriangles[i*9 + 2*3 + 2] = g->points[ g->faces[2+i*3]*3 + Z ];
    }
    extrudeTriangles(&mesh, g, (1/shrink - 1));
    
    
// TRADITIONAL CURVED FACE NORMALS
//    mesh.glTriangleNormals = malloc(sizeof(GLfloat)*g->numFaces*3*3);
//    for(int i = 0; i < g->numFaces; i++){
//        // triangle vertex 1: X Y and Z
//        mesh.glTriangleNormals[i*9 + 0*3 + 0] = g->pointNormals[ g->faces[0+i*3]*3 + X ];
//        mesh.glTriangleNormals[i*9 + 0*3 + 1] = g->pointNormals[ g->faces[0+i*3]*3 + Y ];
//        mesh.glTriangleNormals[i*9 + 0*3 + 2] = g->pointNormals[ g->faces[0+i*3]*3 + Z ];
//        // triangle vertex 2: X Y and Z
//        mesh.glTriangleNormals[i*9 + 1*3 + 0] = g->pointNormals[ g->faces[1+i*3]*3 + X ];
//        mesh.glTriangleNormals[i*9 + 1*3 + 1] = g->pointNormals[ g->faces[1+i*3]*3 + Y ];
//        mesh.glTriangleNormals[i*9 + 1*3 + 2] = g->pointNormals[ g->faces[1+i*3]*3 + Z ];
//        // triangle vertex 3: X Y and Z
//        mesh.glTriangleNormals[i*9 + 2*3 + 0] = g->pointNormals[ g->faces[2+i*3]*3 + X ];
//        mesh.glTriangleNormals[i*9 + 2*3 + 1] = g->pointNormals[ g->faces[2+i*3]*3 + Y ];
//        mesh.glTriangleNormals[i*9 + 2*3 + 2] = g->pointNormals[ g->faces[2+i*3]*3 + Z ];
//    }
    
    // DISCO BALL MIRROR NORMALS
    mesh.glTriangleNormals = malloc(sizeof(GLfloat)*g->numFaces*3*3);
    for(int i = 0; i < g->numFaces; i++){
        // triangle vertex 1: X Y and Z
        mesh.glTriangleNormals[i*9 + 0*3 + 0] = g->faceNormals[ i*3 + X ];
        mesh.glTriangleNormals[i*9 + 0*3 + 1] = g->faceNormals[ i*3 + Y ];
        mesh.glTriangleNormals[i*9 + 0*3 + 2] = g->faceNormals[ i*3 + Z ];
        // triangle vertex 2: X Y and Z
        mesh.glTriangleNormals[i*9 + 1*3 + 0] = g->faceNormals[ i*3 + X ];
        mesh.glTriangleNormals[i*9 + 1*3 + 1] = g->faceNormals[ i*3 + Y ];
        mesh.glTriangleNormals[i*9 + 1*3 + 2] = g->faceNormals[ i*3 + Z ];
        // triangle vertex 3: X Y and Z
        mesh.glTriangleNormals[i*9 + 2*3 + 0] = g->faceNormals[ i*3 + X ];
        mesh.glTriangleNormals[i*9 + 2*3 + 1] = g->faceNormals[ i*3 + Y ];
        mesh.glTriangleNormals[i*9 + 2*3 + 2] = g->faceNormals[ i*3 + Z ];
    }
    
    mesh.numTriangles = g->numFaces;

    return mesh;
}

void deleteMeshNormals(geomeshNormals *m){
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

void deleteMeshTriangles(geomeshTriangles *m){
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
