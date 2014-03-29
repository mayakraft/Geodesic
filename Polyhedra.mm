//
//  Polyhedra.m
//  StagingArea
//
//  Created by Robby Kraft on 3/27/14.
//  Copyright (c) 2014 Robby Kraft. All rights reserved.
//

#import "Polyhedra.h"
#include "Geodesic.h"

#define X 0
#define Y 1
#define Z 2

@interface Polyhedra (){
    Geodesic geodesic;
    float *triPoints;
    int numTriPoints;
    float *linePoints;
    int numLinePoints;
    
    float *normalPoints;
}
@end

@implementation Polyhedra

-(void) makeGLTriangles{
    if(!geodesic.numFaces)
        return;
    numTriPoints = geodesic.numFaces*3;
    delete triPoints;
    triPoints = (float*)malloc(sizeof(float)*numTriPoints*3);
    for(int i = 0; i < geodesic.numFaces; i++){
        // triangle vertex 1: X Y and Z
        triPoints[i*9 + 0*3 + 0] = geodesic.points[ geodesic.faces[0+i*3]*3 + X ];
        triPoints[i*9 + 0*3 + 1] = geodesic.points[ geodesic.faces[0+i*3]*3 + Y ];
        triPoints[i*9 + 0*3 + 2] = geodesic.points[ geodesic.faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        triPoints[i*9 + 1*3 + 0] = geodesic.points[ geodesic.faces[1+i*3]*3 + X ];
        triPoints[i*9 + 1*3 + 1] = geodesic.points[ geodesic.faces[1+i*3]*3 + Y ];
        triPoints[i*9 + 1*3 + 2] = geodesic.points[ geodesic.faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        triPoints[i*9 + 2*3 + 0] = geodesic.points[ geodesic.faces[2+i*3]*3 + X ];
        triPoints[i*9 + 2*3 + 1] = geodesic.points[ geodesic.faces[2+i*3]*3 + Y ];
        triPoints[i*9 + 2*3 + 2] = geodesic.points[ geodesic.faces[2+i*3]*3 + Z ];
    }
    for(int i = 0; i < geodesic.numFaces; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",triPoints[0+i*9],
               triPoints[1+i*9],
               triPoints[2+i*9],
               triPoints[3+i*9],
               triPoints[4+i*9],
               triPoints[5+i*9],
               triPoints[6+i*9],
               triPoints[7+i*9],
               triPoints[8+i*9]);
    }
}

-(void) makeGLLines{
    if(!geodesic.numLines)
        return;
    numLinePoints = geodesic.numLines * 2;
    delete linePoints;
    linePoints = (float*)malloc(sizeof(float)*numLinePoints*3);
    for(int i = 0; i < geodesic.numLines; i++){
        linePoints[i*6 + 0] = geodesic.points[ geodesic.lines[0+i*2]*3 + X];
        linePoints[i*6 + 1] = geodesic.points[ geodesic.lines[0+i*2]*3 + Y];
        linePoints[i*6 + 2] = geodesic.points[ geodesic.lines[0+i*2]*3 + Z];
        linePoints[i*6 + 3] = geodesic.points[ geodesic.lines[1+i*2]*3 + X];
        linePoints[i*6 + 4] = geodesic.points[ geodesic.lines[1+i*2]*3 + Y];
        linePoints[i*6 + 5] = geodesic.points[ geodesic.lines[1+i*2]*3 + Z];
    }
    for(int i = 0; i < geodesic.numLines; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",linePoints[0+i*6],
               linePoints[1+i*6],
               linePoints[2+i*6],
               linePoints[3+i*6],
               linePoints[4+i*6],
               linePoints[5+i*6]);
    }
}

-(void) makeNormalLines{
    delete normalPoints;
    normalPoints = (float*)malloc(sizeof(float)*geodesic.numPoints*6);
    for(int i = 0; i < geodesic.numPoints; i++){
        normalPoints[i*6+0] = geodesic.points[i*3+X];
        normalPoints[i*6+1] = geodesic.points[i*3+Y];
        normalPoints[i*6+2] = geodesic.points[i*3+Z];
        normalPoints[i*6+3] = geodesic.points[i*3+X] + geodesic.normals[i*3+X];
        normalPoints[i*6+4] = geodesic.points[i*3+Y] + geodesic.normals[i*3+Y];
        normalPoints[i*6+5] = geodesic.points[i*3+Z] + geodesic.normals[i*3+Z];
    }
    for(int i = 0; i < geodesic.numPoints; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",normalPoints[0+i*6],
               normalPoints[1+i*6],
               normalPoints[2+i*6],
               normalPoints[3+i*6],
               normalPoints[4+i*6],
               normalPoints[5+i*6]);
    }
}

-(void) setup{
    geodesic.setIcosahedron();
    NSLog(@"NUM POINTS:%d, LINES:%d, FACES:%d",geodesic.numPoints, geodesic.numLines, geodesic.numFaces);
    [self makeGLTriangles];
    [self makeGLLines];
    NSLog(@"________________");
    [self makeNormalLines];
    //    NSLog(@"%d",numTriPoints);
}

-(void)draw{
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glPushMatrix();
    glColor4f(0.0, 0.0, 1.0, 0.5);
    glVertexPointer(3, GL_FLOAT, 0, triPoints);
    glDrawArrays(GL_TRIANGLES, 0, numTriPoints);
    glPopMatrix();
    
    //glDisableClientState(GL_VERTEX_ARRAY);
    
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, linePoints);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_LINES, 0, numLinePoints);
    glPopMatrix();
    
    glPushMatrix();
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, normalPoints);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_LINES, 0, geodesic.numPoints*2);
    glPopMatrix();
    
    
//    for(int i = 0; i < recordIndex; i++){
//        glColor4f(1.0, 0.0+i/(float)recordIndex, 0.0, 1.0);
//        GLfloat userAccelerationVector[] = {0.0f, 0.0f, 0.0f, userAccelerations[3*i], userAccelerations[3*i+1], userAccelerations[3*i+2]};
//        glVertexPointer(3, GL_FLOAT, 0, userAccelerationVector);
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glDrawArrays(GL_LINE_LOOP, 0, 2);
//        if(i == playBack % recordIndex && i < recordIndex){
//            GLfloat triangle[9];
//            triangle[0] = userAccelerations[0];
//            triangle[1] = userAccelerations[1];
//            triangle[2] = userAccelerations[2];
//            triangle[3] = userAccelerations[i*3];
//            triangle[4] = userAccelerations[i*3+1];
//            triangle[5] = userAccelerations[i*3+2];
//            triangle[6] = userAccelerations[(i+1)*3];
//            triangle[7] = userAccelerations[(i+1)*3+1];
//            triangle[8] = userAccelerations[(i+1)*3+2];
//            glEnableClientState(GL_VERTEX_ARRAY);
//            glPushMatrix();
//            glColor4f(1.0, 0.5, 0.5, 1.0);
//            glVertexPointer(3, GL_FLOAT, 0, triangle);
//            glDrawArrays(GL_TRIANGLES, 0, 3);
//            glPopMatrix();
//            glDisableClientState(GL_VERTEX_ARRAY);
//        }
//
//    }
    
}


@end
