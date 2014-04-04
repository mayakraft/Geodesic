//
//  Mesh.cpp
//
//  Created by Robby on 3/27/14.
//  Copyright (c) 2014 Robby Kraft. All rights reserved.
//

#include "GeodesicMesh.h"
#include <OpenGLES/ES1/gl.h>
#include <fstream>
#include "Geodesic.h"

#define X 0
#define Y 1
#define Z 2

void GeodesicMesh::load(Geodesic* geodesic){
    
    printf("(V%d) NUM POINTS:%d, LINES:%d, FACES:%d\n", geodesic->v, geodesic->numPoints, geodesic->numLines, geodesic->numFaces);
    
    makeGLTriangles(geodesic);
    makeGLLines(geodesic);
    makeNormals(geodesic);
//    makeNormalLines(geodesic);
//    makeFaceNormalLines(geodesic);
    extrudeTriangles(geodesic);
    
    numPoints = geodesic->numPoints;
    numFaces = geodesic->numFaces;
    numLines = geodesic->numLines;
    glPoints = (float*)malloc(sizeof(float)*numPoints*3);
    for(int i = 0; i < geodesic->numPoints; i++){
        glPoints[i*3+X] = geodesic->points[i*3+X];
        glPoints[i*3+Y] = geodesic->points[i*3+Y];
        glPoints[i*3+Z] = geodesic->points[i*3+Z];
    }
//    log();
}


void GeodesicMesh::draw(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glPushMatrix();
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, glTriangles);
    glNormalPointer(GL_FLOAT, 0, glNormals);
    glDrawArrays(GL_TRIANGLES, 0, numTriangles);
    glPopMatrix();
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GeodesicMesh::drawLines(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, glLines);
    glDrawArrays(GL_LINES, 0, numLinePoints);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GeodesicMesh::drawNormalLines(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, normalLines);
    glDrawArrays(GL_LINES, 0, numPoints*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GeodesicMesh::drawFaceNormalLines(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, faceNormalLines);
    glDrawArrays(GL_LINES, 0, numFaces*2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GeodesicMesh::drawPoints(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, glPoints);
    glDrawArrays(GL_POINTS, 0, numPoints);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GeodesicMesh::makeGLTriangles(Geodesic* geodesic){
    if(!geodesic->numFaces)
        return;
    numTriangles = geodesic->numFaces*3;
    delete glTriangles;
    glTriangles = (float*)malloc(sizeof(float)*numTriangles*3);
    for(int i = 0; i < geodesic->numFaces; i++){
        // triangle vertex 1: X Y and Z
        glTriangles[i*9 + 0*3 + 0] = geodesic->points[ geodesic->faces[0+i*3]*3 + X ];
        glTriangles[i*9 + 0*3 + 1] = geodesic->points[ geodesic->faces[0+i*3]*3 + Y ];
        glTriangles[i*9 + 0*3 + 2] = geodesic->points[ geodesic->faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        glTriangles[i*9 + 1*3 + 0] = geodesic->points[ geodesic->faces[1+i*3]*3 + X ];
        glTriangles[i*9 + 1*3 + 1] = geodesic->points[ geodesic->faces[1+i*3]*3 + Y ];
        glTriangles[i*9 + 1*3 + 2] = geodesic->points[ geodesic->faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        glTriangles[i*9 + 2*3 + 0] = geodesic->points[ geodesic->faces[2+i*3]*3 + X ];
        glTriangles[i*9 + 2*3 + 1] = geodesic->points[ geodesic->faces[2+i*3]*3 + Y ];
        glTriangles[i*9 + 2*3 + 2] = geodesic->points[ geodesic->faces[2+i*3]*3 + Z ];
    }
}

void GeodesicMesh::extrudeTriangles(Geodesic* geodesic){
    float scale = .5;
    for(int i = 0; i < geodesic->numFaces; i++){
        // triangle vertex 1: X Y and Z
        glTriangles[i*9 + 0*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        glTriangles[i*9 + 0*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        glTriangles[i*9 + 0*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
        // triangle vertex 2: X Y and Z
        glTriangles[i*9 + 1*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        glTriangles[i*9 + 1*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        glTriangles[i*9 + 1*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
        // triangle vertex 3: X Y and Z
        glTriangles[i*9 + 2*3 + 0] += geodesic->faceNormals[0+i*3] * scale;
        glTriangles[i*9 + 2*3 + 1] += geodesic->faceNormals[1+i*3] * scale;
        glTriangles[i*9 + 2*3 + 2] += geodesic->faceNormals[2+i*3] * scale;
    }
}

void GeodesicMesh::makeGLLines(Geodesic* geodesic){
    if(!geodesic->numLines)
        return;
    numLinePoints = geodesic->numLines * 2;
    delete glLines;
    glLines = (float*)malloc(sizeof(float)*numLinePoints*3);
    for(int i = 0; i < geodesic->numLines; i++){
        glLines[i*6 + 0] = geodesic->points[ geodesic->lines[0+i*2]*3 + X];
        glLines[i*6 + 1] = geodesic->points[ geodesic->lines[0+i*2]*3 + Y];
        glLines[i*6 + 2] = geodesic->points[ geodesic->lines[0+i*2]*3 + Z];
        glLines[i*6 + 3] = geodesic->points[ geodesic->lines[1+i*2]*3 + X];
        glLines[i*6 + 4] = geodesic->points[ geodesic->lines[1+i*2]*3 + Y];
        glLines[i*6 + 5] = geodesic->points[ geodesic->lines[1+i*2]*3 + Z];
    }
}

void GeodesicMesh::makeNormals(Geodesic* geodesic){
    delete glNormals;
    glNormals = (float*)malloc(sizeof(float) * numTriangles*3);
    for(int i = 0; i < geodesic->numFaces; i++){
        // triangle vertex 1: X Y and Z
        glNormals[i*9 + 0*3 + 0] = geodesic->normals[ geodesic->faces[0+i*3]*3 + X ];
        glNormals[i*9 + 0*3 + 1] = geodesic->normals[ geodesic->faces[0+i*3]*3 + Y ];
        glNormals[i*9 + 0*3 + 2] = geodesic->normals[ geodesic->faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        glNormals[i*9 + 1*3 + 0] = geodesic->normals[ geodesic->faces[1+i*3]*3 + X ];
        glNormals[i*9 + 1*3 + 1] = geodesic->normals[ geodesic->faces[1+i*3]*3 + Y ];
        glNormals[i*9 + 1*3 + 2] = geodesic->normals[ geodesic->faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        glNormals[i*9 + 2*3 + 0] = geodesic->normals[ geodesic->faces[2+i*3]*3 + X ];
        glNormals[i*9 + 2*3 + 1] = geodesic->normals[ geodesic->faces[2+i*3]*3 + Y ];
        glNormals[i*9 + 2*3 + 2] = geodesic->normals[ geodesic->faces[2+i*3]*3 + Z ];
    }
}

void GeodesicMesh::makeNormalLines(Geodesic* geodesic){
    delete normalLines;
    normalLines = (float*)malloc(sizeof(float)*geodesic->numPoints*6);
    for(int i = 0; i < geodesic->numPoints; i++){
        normalLines[i*6+0] = geodesic->points[i*3+X];
        normalLines[i*6+1] = geodesic->points[i*3+Y];
        normalLines[i*6+2] = geodesic->points[i*3+Z];
        normalLines[i*6+3] = geodesic->points[i*3+X] + geodesic->normals[i*3+X];
        normalLines[i*6+4] = geodesic->points[i*3+Y] + geodesic->normals[i*3+Y];
        normalLines[i*6+5] = geodesic->points[i*3+Z] + geodesic->normals[i*3+Z];
    }
}

void GeodesicMesh::makeFaceNormalLines(Geodesic* geodesic){
    delete normalLines;
    faceNormalLines = (float*)malloc(sizeof(float)*geodesic->numFaces*6);
    for(int i = 0; i < geodesic->numFaces; i++){
        faceNormalLines[i*6+0] = (geodesic->points[ geodesic->faces[i*3+0] *3+X] +
                                  geodesic->points[ geodesic->faces[i*3+1] *3+X] +
                                  geodesic->points[ geodesic->faces[i*3+2] *3+X] ) / 3.0;
        faceNormalLines[i*6+1] = (geodesic->points[ geodesic->faces[i*3+0] *3+Y] +
                                  geodesic->points[ geodesic->faces[i*3+1] *3+Y] +
                                  geodesic->points[ geodesic->faces[i*3+2] *3+Y] ) / 3.0;
        faceNormalLines[i*6+2] = (geodesic->points[ geodesic->faces[i*3+0] *3+Z] +
                                  geodesic->points[ geodesic->faces[i*3+1] *3+Z] +
                                  geodesic->points[ geodesic->faces[i*3+2] *3+Z] ) / 3.0;
        faceNormalLines[i*6+3] = faceNormalLines[i*6+0] + geodesic->faceNormals[i*3+X];
        faceNormalLines[i*6+4] = faceNormalLines[i*6+1] + geodesic->faceNormals[i*3+Y];
        faceNormalLines[i*6+5] = faceNormalLines[i*6+2] + geodesic->faceNormals[i*3+Z];
    }
}

void GeodesicMesh::log(){
    if(glTriangles){
        printf("_____________________\nFACES\n_____________________\n");
        for(int i = 0; i < numFaces; i++){
            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
                   glTriangles[0+i*9], glTriangles[1+i*9], glTriangles[2+i*9],
                   glTriangles[3+i*9], glTriangles[4+i*9], glTriangles[5+i*9],
                   glTriangles[6+i*9], glTriangles[7+i*9], glTriangles[8+i*9]);
        }
    }
    if(glLines){
        printf("_____________________\nLINES\n_____________________\n");
        for(int i = 0; i < numLines; i++){
            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
                   glLines[0+i*6], glLines[1+i*6],
                   glLines[2+i*6], glLines[3+i*6],
                   glLines[4+i*6], glLines[5+i*6]);
        }
    }
    if(glPoints){
        printf("_____________________\nPOINTS\n_____________________\n");
        for(int i = 0; i < numFaces; i++){
            printf("(%.3f, %.3f, %.3f)\n",
                   glPoints[0+i*3], glPoints[1+i*3], glPoints[2+i*3]);
        }
    }
    if(glNormals){
        printf("_____________________\nNORMALS\n_____________________\n");
        for(int i = 0; i < numFaces; i++){
            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
                   glNormals[0+i*9], glNormals[1+i*9], glNormals[2+i*9],
                   glNormals[3+i*9], glNormals[4+i*9], glNormals[5+i*9],
                   glNormals[6+i*9], glNormals[7+i*9], glNormals[8+i*9]);
        }
    }
    if(normalLines){
        printf("_____________________\nNORMAL LINES\n_____________________\n");
        for(int i = 0; i < numPoints; i++){
            printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",
                   normalLines[0+i*6], normalLines[1+i*6],
                   normalLines[2+i*6], normalLines[3+i*6],
                   normalLines[4+i*6], normalLines[5+i*6]);
        }
    }
}
