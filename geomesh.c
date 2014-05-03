#include "geomesh.h"
#include <OpenGLES/ES1/gl.h>

//void loadMesh(geomesh *mesh, geodesic *geo){
//    
//    mesh->_geodesic = geo;
//    
//    mesh->_geodesic->getPoints(&points, &numPoints);
//    mesh->_geodesic->getLines(&lines, &numLines);
//    mesh->_geodesic->getFaces(&faces, &numFaces);
//    printf("(V%d) NUM POINTS:%d, LINES:%d, FACES:%d\n", geodesic->v, numPoints, numLines, numFaces);
//    
//    makeGLPoints();
//    makeGLTriangles();
//    extrudeTriangles(.5);
//    makeGLLines();
//    makeNormals();
////    makeNormalLines();
////    makeFaceNormalLines();
//    
////    log();
//}

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




// mesh ornaments
void geodesicMeshDrawVertexNormalLines(geomesh *g){
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, g->vertexNormalsLines);
    glDrawArrays(GL_LINES, 0, g->numVertexNormals*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicMeshDrawLineNormalLines(geomesh *g){
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, g->lineNormalsLines);
    glDrawArrays(GL_LINES, 0, g->numLineNormals*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicMeshDrawFaceNormalLines(geomesh *g){
	glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, g->faceNormalsLines);
    glDrawArrays(GL_LINES, 0, g->numFaceNormals*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicMeshDrawExtrudedTriangles(geodesic *g, geomesh *mesh){
    glEnableClientState(GL_VERTEX_ARRAY);
 //   glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, mesh->glTriangles);
//    glNormalPointer(GL_FLOAT, 0, g->faceNormals);
    glDrawArrays(GL_TRIANGLES, 0, mesh->numTriangles*3);
    
 //   glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}



void _geodesicMeshMakeTriangles(geodesic *g, geomesh *mesh){
    if(!g->numFaces)
        return;
    mesh->numTriangles = g->numFaces;
    //    delete glEachTriangles;
    mesh->glTriangles = (float*)malloc(sizeof(float)*mesh->numTriangles*3*3);
    for(int i = 0; i < mesh->numTriangles; i++){
        //        if(!g->visibleFaces || geodesic->visibleFaces[i]){
        // triangle vertex 1: X Y and Z
        mesh->glTriangles[i*9 + 0*3 + 0] = g->points[ g->faces[0+i*3]*3 + X ];
        mesh->glTriangles[i*9 + 0*3 + 1] = g->points[ g->faces[0+i*3]*3 + Y ];
        mesh->glTriangles[i*9 + 0*3 + 2] = g->points[ g->faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        mesh->glTriangles[i*9 + 1*3 + 0] = g->points[ g->faces[1+i*3]*3 + X ];
        mesh->glTriangles[i*9 + 1*3 + 1] = g->points[ g->faces[1+i*3]*3 + Y ];
        mesh->glTriangles[i*9 + 1*3 + 2] = g->points[ g->faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        mesh->glTriangles[i*9 + 2*3 + 0] = g->points[ g->faces[2+i*3]*3 + X ];
        mesh->glTriangles[i*9 + 2*3 + 1] = g->points[ g->faces[2+i*3]*3 + Y ];
        mesh->glTriangles[i*9 + 2*3 + 2] = g->points[ g->faces[2+i*3]*3 + Z ];
        //        }
    }
}

void _geodesicMeshExtrudeTriangles(geodesic *geodesic, geomesh *mesh, float scale){
    for(int i = 0; i < mesh->numTriangles; i++){
        // triangle vertex 1: X Y and Z
        mesh->glTriangles[i*9 + 0*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        mesh->glTriangles[i*9 + 0*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        mesh->glTriangles[i*9 + 0*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
        // triangle vertex 2: X Y and Z
        mesh->glTriangles[i*9 + 1*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        mesh->glTriangles[i*9 + 1*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        mesh->glTriangles[i*9 + 1*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
        // triangle vertex 3: X Y and Z
        mesh->glTriangles[i*9 + 2*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        mesh->glTriangles[i*9 + 2*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        mesh->glTriangles[i*9 + 2*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
    }
}

geomesh makeMesh(geodesic *g){
    geomesh mesh;
    mesh.vertexNormalsLines = malloc(sizeof(float)*g->numPoints*3*2);
    for(int i = 0; i < g->numFaces; i++){
        mesh.vertexNormalsLines[i*6+0+X] = g->pointNormals[i*3+X];
        mesh.vertexNormalsLines[i*6+0+Y] = g->pointNormals[i*3+Y];
        mesh.vertexNormalsLines[i*6+0+Z] = g->pointNormals[i*3+Z];
        mesh.vertexNormalsLines[i*6+3+X] = g->pointNormals[i*3+X]*1.1;
        mesh.vertexNormalsLines[i*6+3+Y] = g->pointNormals[i*3+Y]*1.1;
        mesh.vertexNormalsLines[i*6+3+Z] = g->pointNormals[i*3+Z]*1.1;
    }
    mesh.lineNormalsLines = malloc(sizeof(float)*g->numLines*3*2);
    for(int i = 0; i < g->numFaces; i++){
        mesh.lineNormalsLines[i*6+0+X] = g->lineNormals[i*3+X];
        mesh.lineNormalsLines[i*6+0+Y] = g->lineNormals[i*3+Y];
        mesh.lineNormalsLines[i*6+0+Z] = g->lineNormals[i*3+Z];
        mesh.lineNormalsLines[i*6+3+X] = g->lineNormals[i*3+X]*1.05;
        mesh.lineNormalsLines[i*6+3+Y] = g->lineNormals[i*3+Y]*1.05;
        mesh.lineNormalsLines[i*6+3+Z] = g->lineNormals[i*3+Z]*1.05;
    }
    mesh.faceNormalsLines = malloc(sizeof(float)*g->numFaces*3*2);
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
    
    _geodesicMeshMakeTriangles(g, &mesh);
    _geodesicMeshExtrudeTriangles(g, &mesh, .15);
    return mesh;
}


/*
void GeodesicMesh::makeGLLines(){
    if(!numLines)
        return;
    numGLLinePoints = numLines * 2;
    delete glLines;
    glLines = (float*)malloc(sizeof(float)*numGLLinePoints*3);
    for(int i = 0; i < numLines; i++){
        glLines[i*6 + 0] = points[ lines[0+i*2]*3 + X];
        glLines[i*6 + 1] = points[ lines[0+i*2]*3 + Y];
        glLines[i*6 + 2] = points[ lines[0+i*2]*3 + Z];
        glLines[i*6 + 3] = points[ lines[1+i*2]*3 + X];
        glLines[i*6 + 4] = points[ lines[1+i*2]*3 + Y];
        glLines[i*6 + 5] = points[ lines[1+i*2]*3 + Z];
    }
}

void GeodesicMesh::makeNormals(){
    delete glNormals;
    glNormals = (float*)malloc(sizeof(float) * numGLTriangles*3);
    for(int i = 0; i < numFaces; i++){
        // triangle vertex 1: X Y and Z
        glNormals[i*9 + 0*3 + 0] = geodesic->normals[ faces[0+i*3]*3 + X ];
        glNormals[i*9 + 0*3 + 1] = geodesic->normals[ faces[0+i*3]*3 + Y ];
        glNormals[i*9 + 0*3 + 2] = geodesic->normals[ faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        glNormals[i*9 + 1*3 + 0] = geodesic->normals[ faces[1+i*3]*3 + X ];
        glNormals[i*9 + 1*3 + 1] = geodesic->normals[ faces[1+i*3]*3 + Y ];
        glNormals[i*9 + 1*3 + 2] = geodesic->normals[ faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        glNormals[i*9 + 2*3 + 0] = geodesic->normals[ faces[2+i*3]*3 + X ];
        glNormals[i*9 + 2*3 + 1] = geodesic->normals[ faces[2+i*3]*3 + Y ];
        glNormals[i*9 + 2*3 + 2] = geodesic->normals[ faces[2+i*3]*3 + Z ];
    }
}

void GeodesicMesh::makeNormalLines(){
    delete normalLines;
    normalLines = (float*)malloc(sizeof(float)*numPoints*6);
    for(int i = 0; i < numPoints; i++){
        normalLines[i*6+0] = points[i*3+X];
        normalLines[i*6+1] = points[i*3+Y];
        normalLines[i*6+2] = points[i*3+Z];
        normalLines[i*6+3] = points[i*3+X] + geodesic->normals[i*3+X];
        normalLines[i*6+4] = points[i*3+Y] + geodesic->normals[i*3+Y];
        normalLines[i*6+5] = points[i*3+Z] + geodesic->normals[i*3+Z];
    }
}

void GeodesicMesh::makeFaceNormalLines(){
    delete normalLines;
    faceNormalLines = (float*)malloc(sizeof(float)*numFaces*6);
    for(int i = 0; i < numFaces; i++){
        faceNormalLines[i*6+0] = (points[ faces[i*3+0] *3+X] +
                                  points[ faces[i*3+1] *3+X] +
                                  points[ faces[i*3+2] *3+X] ) / 3.0;
        faceNormalLines[i*6+1] = (points[ faces[i*3+0] *3+Y] +
                                  points[ faces[i*3+1] *3+Y] +
                                  points[ faces[i*3+2] *3+Y] ) / 3.0;
        faceNormalLines[i*6+2] = (points[ faces[i*3+0] *3+Z] +
                                  points[ faces[i*3+1] *3+Z] +
                                  points[ faces[i*3+2] *3+Z] ) / 3.0;
        faceNormalLines[i*6+3] = faceNormalLines[i*6+0] + geodesic->faceNormals[i*3+X];
        faceNormalLines[i*6+4] = faceNormalLines[i*6+1] + geodesic->faceNormals[i*3+Y];
        faceNormalLines[i*6+5] = faceNormalLines[i*6+2] + geodesic->faceNormals[i*3+Z];
    }
}
*/

//void logMesh(){
//    if(glEachTriangles){
//        printf("_____________________\nFACES\n_____________________\n");
//        for(int i = 0; i < numFaces; i++){
//            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
//                   glEachTriangles[0+i*9], glEachTriangles[1+i*9], glEachTriangles[2+i*9],
//                   glEachTriangles[3+i*9], glEachTriangles[4+i*9], glEachTriangles[5+i*9],
//                   glEachTriangles[6+i*9], glEachTriangles[7+i*9], glEachTriangles[8+i*9]);
//        }
//    }
//    if(glLines){
//        printf("_____________________\nLINES\n_____________________\n");
//        for(int i = 0; i < numLines; i++){
//            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
//                   glLines[0+i*6], glLines[1+i*6],
//                   glLines[2+i*6], glLines[3+i*6],
//                   glLines[4+i*6], glLines[5+i*6]);
//        }
//    }
//    if(glPoints){
//        printf("_____________________\nPOINTS\n_____________________\n");
//        for(int i = 0; i < numFaces; i++){
//            printf("(%.3f, %.3f, %.3f)\n",
//                   glPoints[0+i*3], glPoints[1+i*3], glPoints[2+i*3]);
//        }
//    }
//    if(glNormals){
//        printf("_____________________\nNORMALS\n_____________________\n");
//        for(int i = 0; i < numFaces; i++){
//            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
//                   glNormals[0+i*9], glNormals[1+i*9], glNormals[2+i*9],
//                   glNormals[3+i*9], glNormals[4+i*9], glNormals[5+i*9],
//                   glNormals[6+i*9], glNormals[7+i*9], glNormals[8+i*9]);
//        }
//    }
//    if(normalLines){
//        printf("_____________________\nNORMAL LINES\n_____________________\n");
//        for(int i = 0; i < numPoints; i++){
//            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
//                   normalLines[0+i*6], normalLines[1+i*6],
//                   normalLines[2+i*6], normalLines[3+i*6],
//                   normalLines[4+i*6], normalLines[5+i*6]);
//        }
//    }
//}
