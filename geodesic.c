#include "geodesic.h"
#include <stdlib.h>
#include <math.h>

#include "geomesh.c"
#include "geodiagram.c"

#define phi (1 + sqrt(5)) / 2.0
#define M_2PI 6.28318530717958647693528676655900576
#define SQRT_P_5 0.707106781186547524400844362104849     /* sqrt(.5)  */
#define SQRT_1_P_5 1.224744871391589049098642037352946     /* sqrt(1.5)  */

#define X 0
#define Y 1
#define Z 2

//
// for cropping
// introduce this idea of rows
// each triangle is a member of a row
// starting from the top, 5 triangles in row 1
// 10 in row 2
// 15 in row 3
// ...
// rows will be encoded into the platonic solids
//

void _make_tetrahedron(float_ **po, unsigned int *numPoints,
                       unsigned short **li, unsigned int *numLines,
                       unsigned short **fa, unsigned int *numFaces){
    float_ side = SQRT_P_5;
    float_ f = SQRT_1_P_5;
    *numPoints = 4;
    *numLines = 6;
    *numFaces = 4;

    float_ *points = malloc(sizeof(float_)*(*numPoints)*3);
    points[X+3*0] = 0.0;     points[Y+3*0] = 1.0/f;   points[Z+3*0] = side/f;
    points[X+3*1] = 0.0;     points[Y+3*1] = -1.0/f;  points[Z+3*1] = side/f;
    points[X+3*2] = 1.0/f;   points[Y+3*2] = 0.0;     points[Z+3*2] = -side/f;
    points[X+3*3] = -1.0/f;  points[Y+3*3] = 0.0;     points[Z+3*3] = -side/f;
    
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    lines[0+2*0] = 0;  lines[1+2*0] = 1;
    lines[0+2*1] = 0;  lines[1+2*1] = 2;
    lines[0+2*2] = 0;  lines[1+2*2] = 3;
    lines[0+2*3] = 1;  lines[1+2*3] = 2;
    lines[0+2*4] = 1;  lines[1+2*4] = 3;
    lines[0+2*5] = 2;  lines[1+2*5] = 3;
    
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    faces[0+3*0] = 0;  faces[1+3*0] = 3;  faces[2+3*0] = 2;
    faces[0+3*1] = 0;  faces[1+3*1] = 1;  faces[2+3*1] = 3;
    faces[0+3*2] = 0;  faces[1+3*2] = 2;  faces[2+3*2] = 1;
    faces[0+3*3] = 1;  faces[1+3*3] = 2;  faces[2+3*3] = 3;
    // rotate and align one point to Y axis
    float_ offset = -0.615479708670387;
    float_ distance, angle;
    //rotate around the z until one point is at the zenith, along the (Y or X?) axis
    for(int i = 0; i < *numPoints; i++){
        angle = atan2(points[i*3+Z], points[i*3+Y]);
        distance = sqrt( pow(points[i*3+Z], 2) + pow(points[i*3+Y], 2) );
        points[i*3+Z] = distance*sin(angle+offset);
        points[i*3+Y] = distance*cos(angle+offset);
        //points[i*3+Z] stays the same
    }
    *po = points;
    *li = lines;
    *fa = faces;
}

void _make_octahedron(float_ **po, unsigned int *numPoints,
                      unsigned short **li, unsigned int *numLines,
                      unsigned short **fa, unsigned int *numFaces){
    *numPoints = 6;
    *numLines = 12;
    *numFaces = 8;
    
    float_ *points = malloc(sizeof(float_)*(*numPoints)*3);
    points[X+3*0] = 0.0;   points[Y+3*0] = 1.0;   points[Z+3*0] = 0.0;
    points[X+3*1] = 1.0;   points[Y+3*1] = 0.0;   points[Z+3*1] = 0.0;
    points[X+3*2] = 0.0;   points[Y+3*2] = 0.0;   points[Z+3*2] = -1.0;
    points[X+3*3] = -1.0;  points[Y+3*3] = 0.0;   points[Z+3*3] = 0.0;
    points[X+3*4] = 0.0;   points[Y+3*4] = 0.0;   points[Z+3*4] = 1.0;
    points[X+3*5] = 0.0;   points[Y+3*5] = -1.0;  points[Z+3*5] = 0.0;
    
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    lines[0+2*0] = 0;  lines[1+2*0] = 1;
    lines[0+2*1] = 0;  lines[1+2*1] = 4;
    lines[0+2*2] = 0;  lines[1+2*2] = 2;
    lines[0+2*3] = 0;  lines[1+2*3] = 3;
    lines[0+2*4] = 3;  lines[1+2*4] = 4;
    lines[0+2*5] = 4;  lines[1+2*5] = 1;
    lines[0+2*6] = 1;  lines[1+2*6] = 2;
    lines[0+2*7] = 2;  lines[1+2*7] = 3;
    lines[0+2*8] = 5;  lines[1+2*8] = 4;
    lines[0+2*9] = 5;  lines[1+2*9] = 3;
    lines[0+2*10] = 5; lines[1+2*10] = 2;
    lines[0+2*11] = 5; lines[1+2*11] = 1;
    
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    faces[0+3*0] = 0;  faces[1+3*0] = 1;  faces[2+3*0] = 4;
    faces[0+3*1] = 0;  faces[1+3*1] = 2;  faces[2+3*1] = 1;
    faces[0+3*2] = 0;  faces[1+3*2] = 3;  faces[2+3*2] = 2;
    faces[0+3*3] = 0;  faces[1+3*3] = 4;  faces[2+3*3] = 3;
    faces[0+3*4] = 5;  faces[1+3*4] = 4;  faces[2+3*4] = 1;
    faces[0+3*5] = 5;  faces[1+3*5] = 3;  faces[2+3*5] = 4;
    faces[0+3*6] = 5;  faces[1+3*6] = 2;  faces[2+3*6] = 3;
    faces[0+3*7] = 5;  faces[1+3*7] = 1;  faces[2+3*7] = 2;

    *po = points;
    *li = lines;
    *fa = faces;
}

void _make_icosahedron(float_ **po, unsigned int *numPoints,
                       unsigned short **li, unsigned int *numLines,
                       unsigned short **fa, unsigned int *numFaces){
    float_ f = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
    *numPoints = 12;
    *numLines = 30;
    *numFaces = 20;
    
    float_ *points = malloc(sizeof(float_)*(*numPoints)*3);
    points[X+3*0] = 0.0;     points[Y+3*0] = 1.0/f;    points[Z+3*0] = phi/f;
    points[X+3*1] = 0.0;     points[Y+3*1] = -1.0/f;   points[Z+3*1] = phi/f;
    points[X+3*2] = 0.0;     points[Y+3*2] = -1.0/f;   points[Z+3*2] = -phi/f;
    points[X+3*3] = 0.0;     points[Y+3*3] = 1.0/f;    points[Z+3*3] = -phi/f;
    points[X+3*4] = phi/f;   points[Y+3*4] = 0.0;      points[Z+3*4] = 1.0/f;
    points[X+3*5] = -phi/f;  points[Y+3*5] = 0.0;      points[Z+3*5] = 1.0/f;
    points[X+3*6] = -phi/f;  points[Y+3*6] = 0.0;      points[Z+3*6] = -1.0/f;
    points[X+3*7] = phi/f;   points[Y+3*7] = 0.0;      points[Z+3*7] = -1.0/f;
    points[X+3*8] = 1.0/f;   points[Y+3*8] = phi/f;    points[Z+3*8] = 0.0;
    points[X+3*9] = -1.0/f;  points[Y+3*9] = phi/f;    points[Z+3*9] = 0.0;
    points[X+3*10] = -1.0/f; points[Y+3*10] = -phi/f;  points[Z+3*10] = 0.0;
    points[X+3*11] = 1.0/f;  points[Y+3*11] = -phi/f;  points[Z+3*11] = 0.0;
    
    unsigned short *lines = malloc(sizeof(unsigned short)*(*numLines)*2);
    lines[0+2*0] = 0;   lines[1+2*0] = 8;
    lines[0+2*1] = 0;   lines[1+2*1] = 9;
    lines[0+2*2] = 0;   lines[1+2*2] = 1;
    lines[0+2*3] = 0;   lines[1+2*3] = 4;
    lines[0+2*4] = 0;   lines[1+2*4] = 5;
    lines[0+2*5] = 8;   lines[1+2*5] = 3;
    lines[0+2*6] = 8;   lines[1+2*6] = 9;
    lines[0+2*7] = 8;   lines[1+2*7] = 7;
    lines[0+2*8] = 8;   lines[1+2*8] = 4;
    lines[0+2*9] = 9;   lines[1+2*9] = 3;
    lines[0+2*10] = 9;  lines[1+2*10] = 6;
    lines[0+2*11] = 9;  lines[1+2*11] = 5;
    lines[0+2*12] = 7;  lines[1+2*12] = 4;
    lines[0+2*13] = 7;  lines[1+2*13] = 3;
    lines[0+2*14] = 7;  lines[1+2*14] = 2;
    lines[0+2*15] = 7;  lines[1+2*15] = 11;
    lines[0+2*16] = 2;  lines[1+2*16] = 10;
    lines[0+2*17] = 2;  lines[1+2*17] = 11;
    lines[0+2*18] = 2;  lines[1+2*18] = 3;
    lines[0+2*19] = 2;  lines[1+2*19] = 6;
    lines[0+2*20] = 10; lines[1+2*20] = 11;
    lines[0+2*21] = 10; lines[1+2*21] = 5;
    lines[0+2*22] = 10; lines[1+2*22] = 6;
    lines[0+2*23] = 10; lines[1+2*23] = 1;
    lines[0+2*24] = 11; lines[1+2*24] = 1;
    lines[0+2*25] = 11; lines[1+2*25] = 4;
    lines[0+2*26] = 4;  lines[1+2*26] = 1;
    lines[0+2*27] = 5;  lines[1+2*27] = 1;
    lines[0+2*28] = 5;  lines[1+2*28] = 6;
    lines[0+2*29] = 6;  lines[1+2*29] = 3;
    
    unsigned short *faces = malloc(sizeof(unsigned short)*(*numFaces)*3);
    faces[0+3*0] = 8;    faces[1+3*0] = 7;    faces[2+3*0] = 4;
    faces[0+3*1] = 8;    faces[1+3*1] = 3;    faces[2+3*1] = 7;
    faces[0+3*2] = 8;    faces[1+3*2] = 4;    faces[2+3*2] = 0;
    faces[0+3*3] = 8;    faces[1+3*3] = 0;    faces[2+3*3] = 9;
    faces[0+3*4] = 9;    faces[1+3*4] = 3;    faces[2+3*4] = 8;
    faces[0+3*5] = 9;    faces[1+3*5] = 0;    faces[2+3*5] = 5;
    faces[0+3*6] = 9;    faces[1+3*6] = 5;    faces[2+3*6] = 6;
    faces[0+3*7] = 9;    faces[1+3*7] = 6;    faces[2+3*7] = 3;
    
    faces[0+3*8] = 3;    faces[1+3*8] = 2;    faces[2+3*8] = 7;
    faces[0+3*9] = 3;    faces[1+3*9] = 6;    faces[2+3*9] = 2;
    faces[0+3*10] = 0;   faces[1+3*10] = 4;   faces[2+3*10] = 1;
    faces[0+3*11] = 0;   faces[1+3*11] = 1;   faces[2+3*11] = 5;
    
    faces[0+3*12] = 11;  faces[1+3*12] = 4;   faces[2+3*12] = 7;
    faces[0+3*13] = 11;  faces[1+3*13] = 7;   faces[2+3*13] = 2;
    faces[0+3*14] = 11;  faces[1+3*14] = 2;   faces[2+3*14] = 10;
    faces[0+3*15] = 11;  faces[1+3*15] = 10;  faces[2+3*15] = 1;
    faces[0+3*16] = 11;  faces[1+3*16] = 1;   faces[2+3*16] = 4;
    faces[0+3*17] = 10;  faces[1+3*17] = 6;   faces[2+3*17] = 5;
    faces[0+3*18] = 10;  faces[1+3*18] = 5;   faces[2+3*18] = 1;
    faces[0+3*19] = 10;  faces[1+3*19] = 2;   faces[2+3*19] = 6;
    
    // align 2 points to polar Y
    float_ offset =  (M_2PI/4.) - atan( (1 + sqrt(5)) / 2 );
    float_ distance, angle;
    //rotate around the z until one point is at the zenith
    for(int i = 0; i < *numPoints; i++){
        angle = atan2(points[i*3+X], points[i*3+Y]);
        distance = sqrt( pow(points[i*3+X], 2) + pow(points[i*3+Y], 2) );
        points[i*3+X] = distance*sin(angle+offset);
        points[i*3+Y] = distance*cos(angle+offset);
        //points[i*3+Z] stays the same
    }
    *po = points;
    *li = lines;
    *fa = faces;
}

void deleteGeodesic(geodesic *g){
    // be VERY careful with this one:
    // an initially unallocated geodesic will still register
    // TRUE on the if()s and call free() and crash
    g->numPoints = 0;
    g->numLines = 0;
    g->numFaces = 0;
    if(g->points){
        free(g->points);
        g->points = NULL;
    }
    if(g->lines){
        free(g->lines);
        g->lines = NULL;
    }
    if(g->faces){
        free(g->faces);
        g->faces = NULL;
    }
    if(g->pointNormals){
        free(g->pointNormals);
        g->pointNormals = NULL;
    }
    if(g->lineNormals){
        free(g->lineNormals);
        g->lineNormals = NULL;
    }
    if(g->faceNormals){
        free(g->faceNormals);
        g->faceNormals = NULL;
    }
//    free(g);
}

void _generate_geodesic_normals(geodesic *g){
    // shortcuts are made possible
    //   due to all points lying on the surface
    //   of a sphere centered at the origin
    if(g->numPoints){
        float_ length;
//        free(normals);
        g->pointNormals = malloc(sizeof(float_)*g->numPoints*3);
        for(int i = 0; i < g->numPoints; i++){
//            length = 1.0;  // we should already know the radius of the sphere
            length = sqrtf( pow(g->points[X+3*i],2) + pow(g->points[Y+3*i],2) + pow(g->points[Z+3*i],2) );
            g->pointNormals[X+3*i] = g->points[X+3*i] / length;// * (i/12.0);
            g->pointNormals[Y+3*i] = g->points[Y+3*i] / length;// * (i/12.0);
            g->pointNormals[Z+3*i] = g->points[Z+3*i] / length;// * (i/12.0);
        }
    }
    if(g->numLines){
//        free(lineNormals);
        g->lineNormals = malloc(sizeof(float_)*g->numLines*3);
        for(int i = 0; i < g->numLines; i++){
            g->lineNormals[i*3+X] = ( g->pointNormals[g->lines[i*2+0]*3+X] +
                                      g->pointNormals[g->lines[i*2+1]*3+X] ) / 2.0;
            g->lineNormals[i*3+Y] = ( g->pointNormals[g->lines[i*2+0]*3+Y] +
                                      g->pointNormals[g->lines[i*2+1]*3+Y] ) / 2.0;
            g->lineNormals[i*3+Z] = ( g->pointNormals[g->lines[i*2+0]*3+Z] +
                                      g->pointNormals[g->lines[i*2+1]*3+Z] ) / 2.0;
        }
    }
    if(g->numFaces){
//        free(faceNormals);
        g->faceNormals = malloc(sizeof(float_)*g->numFaces*3);
        for(int i = 0; i < g->numFaces; i++){
            g->faceNormals[i*3+X] = ( g->pointNormals[g->faces[i*3+0]*3+X] +
                                      g->pointNormals[g->faces[i*3+1]*3+X] +
                                      g->pointNormals[g->faces[i*3+2]*3+X] ) / 3.0;
            g->faceNormals[i*3+Y] = ( g->pointNormals[g->faces[i*3+0]*3+Y] +
                                      g->pointNormals[g->faces[i*3+1]*3+Y] +
                                      g->pointNormals[g->faces[i*3+2]*3+Y] ) / 3.0;
            g->faceNormals[i*3+Z] = ( g->pointNormals[g->faces[i*3+0]*3+Z] +
                                      g->pointNormals[g->faces[i*3+1]*3+Z] +
                                      g->pointNormals[g->faces[i*3+2]*3+Z] ) / 3.0;
        }
    }
}

// NEW POINTS / FACE
// V0: 1           +2 =
// V1: 3 per face  +3 =
// V2: 6           +4 =
// V3: 10          +5 =
// V4: 15          +6 =
// V5: 21

// NEW LINES / FACE
// V0: 0    +3=   (3*1)
// V1: 3    +6=   (3*2)
// V2: 9    +9=   (3*3)
// V3: 18   +12=  (3*4)
// V4: 30   +15=  (3*5)

// NEW FACES / FACE
// V0:
// V1: 1  +3 =  (1*1)
// V2: 4  +5 =  (2*2)
// V3: 9  +7 =  (3*3)
// V4: 16 +9 =  (4*4)
// V5: 25       (5*5)

//         o   A                               0
//        / \         clockwise winding       2 1
//       /   \                               5 4 3
//      /     \                             9 8 7 6
//  C  o_______o  B
//
//           side length  /  frequency (v)
//       \  = AB     short for AB/v
//        / = AC
//
//        /\         /\        /\           /\
//       /\/\                   /\         /\/\
//      /\/\/\
//     /\/\/\/\
//                 first    only 1 up      add 2
//       goal       row     triangle     up and down
//
//        /\                /\              /\
//       /\/\              /\/\            /\/\
//      /\/\/\            /\/\/\          /\/\/\
//           /\              /\/\          /\/\/\
//
//     after the       add 2 faces
//     first face        each step
//    of each row     an up and a down
//          ______
//       a /\    / b    INDEX SHORTCUTS (row = row # from A)
//        /  \  /        p->c  i-1
//      p/____\/c        p->a  i-row
//                       p->b  i-row-1

void _remove_duplicate_points_lines(geodesic *g);

void _divide_geodesic_faces(geodesic *g, int v){
    if(v > 1){
        // calculate new points per face
        // V0: 1           +2 =
        // V1: 3 per face  +3 =
        // V2: 6           +4 =
        // V3: 10          +5 =
        // V4: 15          +6 =
        // V5: 21
        int pointsPerFace = 3;
        for(int i = 1; i < v; i++)
            pointsPerFace += (i+2);
        // calculate new lines per face
        // V0: 0    +3=   (3*1)
        // V1: 3    +6=   (3*2)
        // V2: 9    +9=   (3*3)
        // V3: 18   +12=  (3*4)
        // V4: 30   +15=  (3*5)
        int linesPerFace = 3;
        for(int i = 1; i < v; i++){
            linesPerFace += 3*(i+1);
        }
        // new Points, Faces arrays, and their sizes
        float_ newPointsArray[g->numFaces * pointsPerFace * 3 + g->numPoints];
        unsigned short newFacesArray[v*(v+1)*g->numFaces*3*3];   // data overflow problem. TODO: correctly approximate array size
        unsigned short newLinesArray[linesPerFace*g->numFaces*2];
        // incrementers for the new arrays as we increment and add to them
        unsigned int newPI = 0;
        unsigned int newLI = 0;
        unsigned int newFI = 0;
        // original points in their original indeces
        for(int i = 0; i < g->numPoints; i++){
            newPointsArray[i*3+X] = g->points[i*3+X];
            newPointsArray[i*3+Y] = g->points[i*3+Y];
            newPointsArray[i*3+Z] = g->points[i*3+Z];
            newPI++;
        }
        // bring along the parent polyhedra's faces too
        // makes for interesting non-convex geometry
        // othewise, leave this commented out
//        for(int i = 0; i < numFaces; i++){
//            newFacesArray[i*3+0] = faces[i*3+0];
//            newFacesArray[i*3+1] = faces[i*3+1];
//            newFacesArray[i*3+2] = faces[i*3+2];
//            newFI++;
//        }
        int i, j, k;
        // TODO this can probably remain an int, and just use the variable v
        float segments = v;
        // the 3 vertices of the parent triangle we will subdivide
        int faceEdgeA, faceEdgeB, faceEdgeC;
        float_ *edgePointA, *edgePointB, *edgePointC;
        // vectors: line segments AB and BC divided by the frequency number
        float_ dAB[3], dBC[3];
        // increment through the original set of faces
        for(i=0; i < g->numFaces; i++){
            // save the original major 3 vertices
            faceEdgeA = g->faces[i*3 + 0];
            faceEdgeB = g->faces[i*3 + 1];
            faceEdgeC = g->faces[i*3 + 2];
            edgePointA = &g->points[faceEdgeA*3];
            edgePointB = &g->points[faceEdgeB*3];
            edgePointC = &g->points[faceEdgeC*3];
            // calculate the vector quantity from line segment A to B divided by frequency
            // same with B to C
            dAB[X] = ( edgePointB[X] - edgePointA[X] ) / segments;
            dAB[Y] = ( edgePointB[Y] - edgePointA[Y] ) / segments;
            dAB[Z] = ( edgePointB[Z] - edgePointA[Z] ) / segments;
            dBC[X] = ( edgePointC[X] - edgePointB[X] ) / segments;
            dBC[Y] = ( edgePointC[Y] - edgePointB[Y] ) / segments;
            dBC[Z] = ( edgePointC[Z] - edgePointB[Z] ) / segments;
            // starting at point A, begin generating points one row at a time
            // incrementing towards line segment BC
            // iterate 1, 12, 123, 1234, 12345, 123456...
            for(j = 0; j <= v; j++){
                for(k = 0; k <= j; k++){
                    // skip the 3 original vertices
                    if(!((j == 0 && k == 0) || (j == v & k == 0) || (j == v && k == v))){  //ignore 3 points of the triangle
                        // POINTS
                        newPointsArray[newPI*3+X] = edgePointA[X] + j * dAB[X] + k * dBC[X];
                        newPointsArray[newPI*3+Y] = edgePointA[Y] + j * dAB[Y] + k * dBC[Y];
                        newPointsArray[newPI*3+Z] = edgePointA[Z] + j * dAB[Z] + k * dBC[Z];
                        newPI++;
                    }
                    // FACES and LINES
                    if(k != 0){
                        // build a vertical pointing triangle face
                        int faceP1 = (newPI-1);
                        int faceP2 = (newPI-1)-j-1;
                        int faceP3 = (newPI-1)-1;
                        if(j == v) faceP2++;  // last row->parent row is offset by one because of skipping one of the original triangle points
                        if((j == v && k == v)){  // i have no idea why the last triangle on the last row differs from the other triangles on the last row
                            faceP2++;
                            faceP3++;
                        }
                        // why we save original face edges:
                        // instead of generating new edge vertices,
                        // preserve 3 original edge vertices
                        if(j == 1) faceP2 = faceEdgeA;  // (original pointA)
                        if(j == v && k == 1) faceP3 = faceEdgeB;
                        if(j == v && k == v) faceP1 = faceEdgeC;
                        
                        newFacesArray[newFI*3+0] = faceP1;
                        newFacesArray[newFI*3+1] = faceP2;
                        newFacesArray[newFI*3+2] = faceP3;
                        newFI++;
                        
                        // LINES
                        // from vertically pointed triangles
                        newLinesArray[newLI*2+0] = faceP1;
                        newLinesArray[newLI*2+1] = faceP2;
                        newLI++;
                        newLinesArray[newLI*2+0] = faceP2;
                        newLinesArray[newLI*2+1] = faceP3;
                        newLI++;
                        newLinesArray[newLI*2+0] = faceP3;
                        newLinesArray[newLI*2+1] = faceP1;
                        newLI++;
                        // LINES END
                        
                        //also build a downward pointing triangle face
                        if( k != j){
                            faceP1 = (newPI-1);
                            faceP2 = (newPI-1)-j+1-1;
                            faceP3 = (newPI-1)-j-1;
                            if(j == v){
                                faceP2++;
                                faceP3++;
                            }
                            newFacesArray[newFI*3+0] = faceP1;
                            newFacesArray[newFI*3+1] = faceP2;
                            newFacesArray[newFI*3+2] = faceP3;
                            newFI++;
                        }
                    }
                }
            }
        }
        
        g->numPoints = newPI;
        free(g->points);
        g->points = malloc(sizeof(float_)*g->numPoints*3);
        for(int i = 0; i < g->numPoints*3; i++)
            g->points[i] = newPointsArray[i];

        g->numLines = newLI;
        free(g->lines);
        g->lines = malloc(sizeof(unsigned short)*g->numLines*2);
        for(int i = 0; i < g->numLines*2; i++)
            g->lines[i] = newLinesArray[i];

        g->numFaces = newFI;
        free(g->faces);
        g->faces = malloc(sizeof(unsigned short)*g->numFaces*3);
        for(int i = 0; i < g->numFaces*3; i++)
            g->faces[i] = newFacesArray[i];
        
        // what is left missing, is there are duplicate points along the original
        // face edge lines, due to subdividing each original triangle face
        // without being aware of which faces are its neighbors.
        
        // an un-elegant fix is to heuristically merge points
        // that haev the same coordinates into one point
        // and update pointers in lines[] and faces[] arrays
        _remove_duplicate_points_lines(g);
    }
}

void _spherize_points(float_ *points, unsigned int numPoints){
    int i;
    float_ difference, distance;
    float_ maxdistance = 1.0;//sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
    for(i = 0; i < numPoints; i++)
    {
        distance = sqrt(pow(points[i*3+X], 2) +
                        pow(points[i*3+Y], 2) +
                        pow(points[i*3+Z], 2) );
        difference = maxdistance / distance;
        points[i*3+X]*=difference;
        points[i*3+Y]*=difference;
        points[i*3+Z]*=difference;
    }
}

void _crop_geodesic(geodesic *g, float crop){
    //TODO: crop
}

geodesic tetrahedron(int v){
    geodesic g;
    _make_tetrahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
    _divide_geodesic_faces(&g, v);
    _spherize_points(g.points, g.numPoints);
    _generate_geodesic_normals(&g);
    printf("%dV geodesic tetrahedron: %d points, %d lines, %d faces\n",v,g.numPoints,g.numLines,g.numFaces);
    return g;
}

geodesic octahedron(int v){
    geodesic g;
    _make_octahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
    _divide_geodesic_faces(&g, v);
    _spherize_points(g.points, g.numPoints);
    _generate_geodesic_normals(&g);
    printf("%dV geodesic octahedron: %d points, %d lines, %d faces\n",v,g.numPoints,g.numLines,g.numFaces);
    return g;
}

geodesic icosahedron(int v){
    geodesic g;
    _make_icosahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
    _divide_geodesic_faces(&g, v);
    _spherize_points(g.points, g.numPoints);
    _generate_geodesic_normals(&g);
    printf("%dV geodesic icosahedron: %d points, %d lines, %d faces\n",v,g.numPoints,g.numLines,g.numFaces);
    return g;
}

geodesic tetrahedronDome(int v, float crop) {
    geodesic g = tetrahedron(v);
    _crop_geodesic(&g, crop);
    return g;
}
geodesic octahedronDome(int v, float crop) {
    geodesic g = octahedron(v);
    _crop_geodesic(&g, crop);
    return g;
}
geodesic icosahedronDome(int v, float crop) {
    geodesic g = icosahedron(v);
    _crop_geodesic(&g, crop);
    return g;
}

// sample 128 precision: 1.189731495357231765085759326628007
// sample 64 precision: 1.7976931348623157
// sample 32 precision: 3.4028234
#if _float_precision==128
#define ELBOW .0000000000000001
#elif _float_precision==64
#define ELBOW .00000000001
#elif _float_precision==32
#define ELBOW .00001
#else
#define ELBOW .00001
#endif

void _remove_duplicate_points_lines(geodesic *g){
    
    // make array of size numPoints which looks like this:
    // -1  -1  -1  -1   3  -1  -1  -1  -1  -1  5   5  -1  -1  -1
    // mostly -1s, except at duplicate points, store the first instance of duplication
    int duplicateIndexes[g->numPoints];
    for(int i = 0; i < g->numPoints; i++)
        duplicateIndexes[i] = -1;
    for(int i = 0; i < g->numPoints - 1; i++){
        for(int j = i+1; j < g->numPoints; j++){
            if (g->points[X+i*3] - ELBOW < g->points[X+j*3] && g->points[X+i*3] + ELBOW > g->points[X+j*3] &&
                g->points[Y+i*3] - ELBOW < g->points[Y+j*3] && g->points[Y+i*3] + ELBOW > g->points[Y+j*3] &&
                g->points[Z+i*3] - ELBOW < g->points[Z+j*3] && g->points[Z+i*3] + ELBOW > g->points[Z+j*3] )
            {
                duplicateIndexes[j] = i;
            }
        }
    }
    
    // replaces all pointers to duplicated indexes with their first instance
    // FACES
    for(int f = 0; f < g->numFaces*3; f++){
        if(duplicateIndexes[g->faces[f]] != -1)
            g->faces[f] = duplicateIndexes[g->faces[f]];
    }
    // LINES
    unsigned short *lineWasAssociatedWithADuplicate = calloc(g->numLines, sizeof(unsigned short));
    for(int l = 0; l < g->numLines*2; l++){
        if(duplicateIndexes[g->lines[l]] != -1){
            g->lines[l] = duplicateIndexes[g->lines[l]];
            lineWasAssociatedWithADuplicate[l/2] = 1;  // this is going to help us with searching our line duplicates
        }
    }
    
    //
    //   DUPLICATE LINES
    //
    // now we have all we need to handle duplicate account of lines
    // build an array of -1s, except where a duplicate lies-
    // it will contain the index of it's first occurrence
    int duplicateLineIndexes[g->numLines];
    for(int i = 0; i < g->numLines; i++)
        duplicateLineIndexes[i] = -1;
    unsigned int duplicateCount = 0;
    for(int i = 0; i < g->numLines; i++){
        for(int j = i+1; j < g->numLines; j++){
            // loop in a loop, bad news
            // use the following to cut down on calls
            if(lineWasAssociatedWithADuplicate[j]){
                if(  (g->lines[i*2+0] == g->lines[j*2+0] && g->lines[i*2+1] == g->lines[j*2+1]) ||
                     (g->lines[i*2+0] == g->lines[j*2+1] && g->lines[i*2+1] == g->lines[j*2+0]) ) {
                    if(duplicateLineIndexes[j] == -1){
                        duplicateLineIndexes[j] = i;
                        duplicateCount++;
                    }
                }
            }
        }
    }
    free(lineWasAssociatedWithADuplicate);
    unsigned int newNumLines = g->numLines - duplicateCount;

    unsigned int indexLineOffset = 0;
    // invert duplicate indexes array so duplicates have -1s
    // the rest increment naturally
    // 1  2  3  4  5  6  -1  7  8  -1  9  -1  -1  -1  10  11
    for(int i = 0; i < g->numLines; i++){
        if(duplicateLineIndexes[i] != -1){
            duplicateLineIndexes[i] = -1;
            // by how many indexes is the array currently shifting
            // back to cover up the holes of the duplicated indexes
            indexLineOffset++;
        } else{
            duplicateLineIndexes[i] = i-indexLineOffset;
        }
    }
    unsigned short *newLines = malloc(sizeof(unsigned short)*newNumLines*2);
    for(int i = 0; i < g->numLines; i++){
        if(duplicateLineIndexes[i] != -1){
            newLines[duplicateLineIndexes[i]*2+0] = g->lines[i*2+0];
            newLines[duplicateLineIndexes[i]*2+1] = g->lines[i*2+1];
        }
    }
    g->numLines = 0;
    free(g->lines);
    g->lines = newLines;
    g->numLines = newNumLines;
    //
    //   END DUPLICATE LINES
    //
    
    unsigned int indexPointOffset = 0;
    unsigned int newNumPoints = 0;
    // invert duplicate indexes array so duplicates have -1s
    // the rest are their own indexes, in the new collapsed array,
    // which removes all the duplicated indexes completely. looks like:
    // 1  2  3  4  5  6  -1  7  8  -1  9  -1  -1  -1  10  11
    for(int i = 0; i < g->numPoints; i++){
        if(duplicateIndexes[i] != -1){
            duplicateIndexes[i] = -1;
            // by how many indexes is the array currently shifting
            // back to cover up the holes of the duplicated indexes
            indexPointOffset++;
        } else{
            duplicateIndexes[i] = i-indexPointOffset;
            newNumPoints++;
        }
    }


    float_ *newPointsArray = malloc(sizeof(float_)*newNumPoints*3);
    for(int i = 0; i < g->numPoints; i++){
        if(duplicateIndexes[i] != -1){
            newPointsArray[duplicateIndexes[i]*3+X] = g->points[i*3+X];
            newPointsArray[duplicateIndexes[i]*3+Y] = g->points[i*3+Y];
            newPointsArray[duplicateIndexes[i]*3+Z] = g->points[i*3+Z];
        }
    }

    g->numPoints = 0;
    free(g->points);
    g->points = newPointsArray;
    g->numPoints = newNumPoints;

    // finally, update faces and lines with the moved indexes of the shortened point array
    // FACES
    for(int f = 0; f < g->numFaces*3; f++){
        if(duplicateIndexes[g->faces[f]] != -1)
            g->faces[f] = duplicateIndexes[g->faces[f]];
    }
    // LINES
    for(int l = 0; l < g->numLines*2; l++){
        if(duplicateIndexes[g->lines[l]] != -1)
            g->lines[l] = duplicateIndexes[g->lines[l]];
    }
}

/*
// top to bottom, 0 to 1, retain top portion
void Geodesic::crop(float latitude){
    float NUDGE = .04;  // todo make this smarter
    float c = 1.0-((latitude+NUDGE)*2.);  // map from -1 to 1
    delete visiblePoints;
    delete visibleLines;
    delete visibleFaces;
    visiblePoints = (bool*)calloc(numPoints,sizeof(bool));
    visibleLines = (bool*)calloc(numLines,sizeof(bool));
    visibleFaces = (bool*)calloc(numFaces,sizeof(bool));
    for(int i = 0; i < numPoints; i++)
        if(points[i*3+Y] > c)
            visiblePoints[i] = true;
    for(int i = 0; i < numLines; i++)
        if(points[lines[i*2+0]*3+Y] > c && points[lines[i*2+1]*3+Y] > c)
            visibleLines[i] = true;
    for(int i = 0; i < numFaces; i++)
        if(points[faces[i*3+0]*3+Y] > c && points[faces[i*3+1]*3+Y] > c && points[faces[i*3+2]*3+Y] > c)
            visibleFaces[i] = true;
}
*/
