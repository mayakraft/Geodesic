//
//  Polyhedron.m
//  StagingArea
//
//  Created by Robby Kraft on 3/27/14.
//  Copyright (c) 2014 Robby Kraft. All rights reserved.
//

#import "Polyhedron.h"
#include "Geodesic.h"

#define X 0
#define Y 1
#define Z 2

@interface Polyhedron (){
    // data
    float *glTriangles;
    int numTriangles;
    float *glLines;
    int numLinePoints;
    float *glNormals;
    
    // ornaments
    float *normalLines;
    float *normalFaces;
    
    Geodesic geodesic;
}
@end

@implementation Polyhedron

-(void) setup{
    geodesic.icosahedron(1);
    NSLog(@"NUM POINTS:%d, LINES:%d, FACES:%d",geodesic.numPoints, geodesic.numLines, geodesic.numFaces);
    [self makeGLTriangles];
    [self makeGLLines];
    [self makeNormals];
    [self makeNormalLines];
//    NSLog(@"%d",numTriPoints);
    
    int numLights;
    glGetIntegerv(GL_MAX_LIGHTS, &numLights);
    NSLog(@"NUM LIGHTS: %d",numLights);
}

-(void)draw{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glPushMatrix();
    glColor4f(0.0, 0.0, 1.0, 0.5);
    glVertexPointer(3, GL_FLOAT, 0, glTriangles);
    glNormalPointer(GL_FLOAT, 0, glNormals);
    glDrawArrays(GL_TRIANGLES, 0, numTriangles);
    glPopMatrix();
    
    glDisableClientState(GL_NORMAL_ARRAY);
    
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, glLines);
    glDrawArrays(GL_LINES, 0, numLinePoints);
    glPopMatrix();
    
    glPushMatrix();
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, normalLines);
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

-(void) makeGLTriangles{
    if(!geodesic.numFaces)
        return;
    numTriangles = geodesic.numFaces*3;
    delete glTriangles;
    glTriangles = (float*)malloc(sizeof(float)*numTriangles*3);
    for(int i = 0; i < geodesic.numFaces; i++){
        // triangle vertex 1: X Y and Z
        glTriangles[i*9 + 0*3 + 0] = geodesic.points[ geodesic.faces[0+i*3]*3 + X ];
        glTriangles[i*9 + 0*3 + 1] = geodesic.points[ geodesic.faces[0+i*3]*3 + Y ];
        glTriangles[i*9 + 0*3 + 2] = geodesic.points[ geodesic.faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        glTriangles[i*9 + 1*3 + 0] = geodesic.points[ geodesic.faces[1+i*3]*3 + X ];
        glTriangles[i*9 + 1*3 + 1] = geodesic.points[ geodesic.faces[1+i*3]*3 + Y ];
        glTriangles[i*9 + 1*3 + 2] = geodesic.points[ geodesic.faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        glTriangles[i*9 + 2*3 + 0] = geodesic.points[ geodesic.faces[2+i*3]*3 + X ];
        glTriangles[i*9 + 2*3 + 1] = geodesic.points[ geodesic.faces[2+i*3]*3 + Y ];
        glTriangles[i*9 + 2*3 + 2] = geodesic.points[ geodesic.faces[2+i*3]*3 + Z ];
    }
    NSLog(@"_____________________");
    NSLog(@"    FACES");
    NSLog(@"_____________________");
    for(int i = 0; i < geodesic.numFaces; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",glTriangles[0+i*9],
               glTriangles[1+i*9],
               glTriangles[2+i*9],
               glTriangles[3+i*9],
               glTriangles[4+i*9],
               glTriangles[5+i*9],
               glTriangles[6+i*9],
               glTriangles[7+i*9],
               glTriangles[8+i*9]);
    }
}

-(void) makeGLLines{
    if(!geodesic.numLines)
        return;
    numLinePoints = geodesic.numLines * 2;
    delete glLines;
    glLines = (float*)malloc(sizeof(float)*numLinePoints*3);
    for(int i = 0; i < geodesic.numLines; i++){
        glLines[i*6 + 0] = geodesic.points[ geodesic.lines[0+i*2]*3 + X];
        glLines[i*6 + 1] = geodesic.points[ geodesic.lines[0+i*2]*3 + Y];
        glLines[i*6 + 2] = geodesic.points[ geodesic.lines[0+i*2]*3 + Z];
        glLines[i*6 + 3] = geodesic.points[ geodesic.lines[1+i*2]*3 + X];
        glLines[i*6 + 4] = geodesic.points[ geodesic.lines[1+i*2]*3 + Y];
        glLines[i*6 + 5] = geodesic.points[ geodesic.lines[1+i*2]*3 + Z];
    }
    NSLog(@"_____________________");
    NSLog(@"    LINES");
    NSLog(@"_____________________");
    for(int i = 0; i < geodesic.numLines; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",glLines[0+i*6],
               glLines[1+i*6],
               glLines[2+i*6],
               glLines[3+i*6],
               glLines[4+i*6],
               glLines[5+i*6]);
    }
}

-(void) makeNormals{
    delete glNormals;
    glNormals = (float*)malloc(sizeof(float) * numTriangles*3);
    for(int i = 0; i < geodesic.numFaces; i++){
        // triangle vertex 1: X Y and Z
        glNormals[i*9 + 0*3 + 0] = geodesic.normals[ geodesic.faces[0+i*3]*3 + X ];
        glNormals[i*9 + 0*3 + 1] = geodesic.normals[ geodesic.faces[0+i*3]*3 + Y ];
        glNormals[i*9 + 0*3 + 2] = geodesic.normals[ geodesic.faces[0+i*3]*3 + Z ];
        // triangle vertex 2: X Y and Z
        glNormals[i*9 + 1*3 + 0] = geodesic.normals[ geodesic.faces[1+i*3]*3 + X ];
        glNormals[i*9 + 1*3 + 1] = geodesic.normals[ geodesic.faces[1+i*3]*3 + Y ];
        glNormals[i*9 + 1*3 + 2] = geodesic.normals[ geodesic.faces[1+i*3]*3 + Z ];
        // triangle vertex 3: X Y and Z
        glNormals[i*9 + 2*3 + 0] = geodesic.normals[ geodesic.faces[2+i*3]*3 + X ];
        glNormals[i*9 + 2*3 + 1] = geodesic.normals[ geodesic.faces[2+i*3]*3 + Y ];
        glNormals[i*9 + 2*3 + 2] = geodesic.normals[ geodesic.faces[2+i*3]*3 + Z ];
    }
    NSLog(@"_____________________");
    NSLog(@"    NORMALS");
    NSLog(@"_____________________");
    for(int i = 0; i < geodesic.numFaces; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",glNormals[0+i*9],
               glNormals[1+i*9],
               glNormals[2+i*9],
               glNormals[3+i*9],
               glNormals[4+i*9],
               glNormals[5+i*9],
               glNormals[6+i*9],
               glNormals[7+i*9],
               glNormals[8+i*9]);
    }
}

-(void) makeNormalLines{
    delete normalLines;
    normalLines = (float*)malloc(sizeof(float)*geodesic.numPoints*6);
    for(int i = 0; i < geodesic.numPoints; i++){
        normalLines[i*6+0] = geodesic.points[i*3+X];
        normalLines[i*6+1] = geodesic.points[i*3+Y];
        normalLines[i*6+2] = geodesic.points[i*3+Z];
        normalLines[i*6+3] = geodesic.points[i*3+X] + geodesic.normals[i*3+X];
        normalLines[i*6+4] = geodesic.points[i*3+Y] + geodesic.normals[i*3+Y];
        normalLines[i*6+5] = geodesic.points[i*3+Z] + geodesic.normals[i*3+Z];
    }
    NSLog(@"_____________________");
    NSLog(@"    NORMAL LINES");
    NSLog(@"_____________________");
    for(int i = 0; i < geodesic.numPoints; i++){
        printf("(%.3f, %.3f, %.3f) --- (%.3f, %.3f, %.3f)\n",normalLines[0+i*6],
               normalLines[1+i*6],
               normalLines[2+i*6],
               normalLines[3+i*6],
               normalLines[4+i*6],
               normalLines[5+i*6]);
    }
}

@end
