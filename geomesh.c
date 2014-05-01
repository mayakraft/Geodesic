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
//    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, g->points);
//    glNormalPointer(GL_FLOAT, 0, g->faceNormals);
    glDrawElements(GL_TRIANGLES, g->numFaces*3, GL_UNSIGNED_SHORT, g->faces);
    
//    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicDrawLines(geodesic *g){
	glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, g->points);
//    glNormalPointer(GL_FLOAT, 0, g->lineNormals);
    glDrawElements(GL_LINES, g->numLines*2, GL_UNSIGNED_SHORT, g->lines);
    
//    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void geodesicDrawVertices(geodesic *g){
	glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, g->points);
//    glNormalPointer(GL_FLOAT, 0, g->pointNormals);
    glDrawArrays(GL_POINTS, 0, g->numPoints);
    
//    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// mesh-inhabiting ornaments
//void GeodesicMesh::drawNormalLines(){
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, normalLines);
//    glDrawArrays(GL_LINES, 0, numPoints*2);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void GeodesicMesh::drawFaceNormalLines(){
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, faceNormalLines);
//    glDrawArrays(GL_LINES, 0, numFaces*2);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

//void GeodesicMesh::drawExtrudedTriangles(){
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);
//    
//    glVertexPointer(3, GL_FLOAT, 0, glEachTriangles);
//    glNormalPointer(GL_FLOAT, 0, glNormals);
//    glDrawArrays(GL_TRIANGLES, 0, numGLTriangles);
//    
//    glDisableClientState(GL_NORMAL_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

//void GeodesicMesh::makeGLPoints(){
//    glPoints = (float*)malloc(sizeof(float)*numPoints*3);
//    for(int i = 0; i < numPoints; i++){
//        glPoints[i*3+X] = points[i*3+X];
//        glPoints[i*3+Y] = points[i*3+Y];
//        glPoints[i*3+Z] = points[i*3+Z];
//    }
//}

/*
void GeodesicMesh::makeGLTriangles(){
    if(!numFaces)
        return;
    numGLTriangles = numFaces*3;
    delete glEachTriangles;
    glEachTriangles = (float*)malloc(sizeof(float)*numGLTriangles*3);
    for(int i = 0; i < numFaces; i++){
        if(!geodesic->visibleFaces || geodesic->visibleFaces[i]){
            // triangle vertex 1: X Y and Z
            glEachTriangles[i*9 + 0*3 + 0] = points[ faces[0+i*3]*3 + X ];
            glEachTriangles[i*9 + 0*3 + 1] = points[ faces[0+i*3]*3 + Y ];
            glEachTriangles[i*9 + 0*3 + 2] = points[ faces[0+i*3]*3 + Z ];
            // triangle vertex 2: X Y and Z
            glEachTriangles[i*9 + 1*3 + 0] = points[ faces[1+i*3]*3 + X ];
            glEachTriangles[i*9 + 1*3 + 1] = points[ faces[1+i*3]*3 + Y ];
            glEachTriangles[i*9 + 1*3 + 2] = points[ faces[1+i*3]*3 + Z ];
            // triangle vertex 3: X Y and Z
            glEachTriangles[i*9 + 2*3 + 0] = points[ faces[2+i*3]*3 + X ];
            glEachTriangles[i*9 + 2*3 + 1] = points[ faces[2+i*3]*3 + Y ];
            glEachTriangles[i*9 + 2*3 + 2] = points[ faces[2+i*3]*3 + Z ];
        }
    }
}

void GeodesicMesh::extrudeTriangles(float scale){
    for(int i = 0; i < numFaces; i++){
        // triangle vertex 1: X Y and Z
        glEachTriangles[i*9 + 0*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        glEachTriangles[i*9 + 0*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        glEachTriangles[i*9 + 0*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
        // triangle vertex 2: X Y and Z
        glEachTriangles[i*9 + 1*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        glEachTriangles[i*9 + 1*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        glEachTriangles[i*9 + 1*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
        // triangle vertex 3: X Y and Z
        glEachTriangles[i*9 + 2*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        glEachTriangles[i*9 + 2*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        glEachTriangles[i*9 + 2*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
    }
}

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
