#include <stdlib.h>

void _tetrahedron(float_t **po, unsigned int *numPoints,
                  unsigned short **li, unsigned int *numLines,
                  unsigned short **fa, unsigned int *numFaces){
    float_t side = SQRT_p_5;
    float_t f = SQRT_1_p_5;
    *numPoints = 4;
    *numLines = 6;
    *numFaces = 4;
    float_t *points = malloc(sizeof(float_t)*(*numPoints)*3);
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
    float_t offset = -0.615479708670387;
    float_t distance, angle;
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

void _octahedron(float_t **po, unsigned int *numPoints,
                 unsigned short **li, unsigned int *numLines,
                 unsigned short **fa, unsigned int *numFaces){
    *numPoints = 6;
    *numLines = 12;
    *numFaces = 8;
    float_t *points = malloc(sizeof(float_t)*(*numPoints)*3);
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

void _icosahedron(float_t **po, unsigned int *numPoints,
                  unsigned short **li, unsigned int *numLines,
                  unsigned short **fa, unsigned int *numFaces){
    float_t f = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
    *numPoints = 12;
    *numLines = 30;
    *numFaces = 20;
    float_t *points = malloc(sizeof(float_t)*(*numPoints)*3);
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
    float_t offset =  (M_2PI/4.) - atan( (1 + sqrt(5)) / 2 );
    float_t distance, angle;
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
