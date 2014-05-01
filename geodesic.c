#include "geodesic.h"
#include <stdlib.h>
#include <math.h>
#include "geomesh.c"

#define phi (1 + sqrt(5)) / 2.0
#define M_2PI 6.28318530717958647693528676655900576

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
// rows are encoded into the platonic solids
//

void _make_tetrahedron(floater **po, unsigned int *numPoints,
                       unsigned short **li, unsigned int *numLines,
                       unsigned short **fa, unsigned int *numFaces){
    floater side = 0.70710678118655;
    floater f = 1.224744871391589;
    *numPoints = 4;
    *numLines = 6;
    *numFaces = 4;

//    delete points;
    floater *points = (floater*)malloc(sizeof(floater)*(*numPoints)*3);
    points[X+3*0] = 0.0;    points[Y+3*0] = 1.0/f;   points[Z+3*0] = side/f;
    points[X+3*1] = 0.0;    points[Y+3*1] = -1.0/f;  points[Z+3*1] = side/f;
    points[X+3*2] = 1.0/f;   points[Y+3*2] = 0.0;   points[Z+3*2] = -side/f;
    points[X+3*3] = -1.0/f;  points[Y+3*3] = 0.0;   points[Z+3*3] = -side/f;
    
//    delete lines;
    unsigned short *lines = (unsigned short*)malloc(sizeof(unsigned short)*(*numLines)*2);
    lines[0+2*0] = 0;  lines[1+2*0] = 1;
    lines[0+2*1] = 0;  lines[1+2*1] = 2;
    lines[0+2*2] = 0;  lines[1+2*2] = 3;
    lines[0+2*3] = 1;  lines[1+2*3] = 2;
    lines[0+2*4] = 1;  lines[1+2*4] = 3;
    lines[0+2*5] = 2;  lines[1+2*5] = 3;
    
//    delete faces;
    unsigned short *faces = (unsigned short*)malloc(sizeof(unsigned short)*(*numFaces)*3);
    faces[0+3*0] = 0;  faces[1+3*0] = 3;  faces[2+3*0] = 2;
    faces[0+3*1] = 0;  faces[1+3*1] = 1;  faces[2+3*1] = 3;
    faces[0+3*2] = 0;  faces[1+3*2] = 2;  faces[2+3*2] = 1;
    faces[0+3*3] = 1;  faces[1+3*3] = 2;  faces[2+3*3] = 3;
    // rotate and align one point to Y axis
    floater offset = -0.615479708670387;
    floater distance, angle;
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

void _make_octahedron(floater **po, unsigned int *numPoints,
                      unsigned short **li, unsigned int *numLines,
                      unsigned short **fa, unsigned int *numFaces){
    *numPoints = 6;
    *numLines = 12;
    *numFaces = 8;
    
//    delete points;
    floater *points = (floater*)malloc(sizeof(floater)*(*numPoints)*3);
    points[X+3*0] = 0.0;   points[Y+3*0] = 1.0;   points[Z+3*0] = 0.0;
    points[X+3*1] = 1.0;   points[Y+3*1] = 0.0;   points[Z+3*1] = 0.0;
    points[X+3*2] = 0.0;   points[Y+3*2] = 0.0;   points[Z+3*2] = -1.0;
    points[X+3*3] = -1.0;  points[Y+3*3] = 0.0;   points[Z+3*3] = 0.0;
    points[X+3*4] = 0.0;   points[Y+3*4] = 0.0;   points[Z+3*4] = 1.0;
    points[X+3*5] = 0.0;   points[Y+3*5] = -1.0;  points[Z+3*5] = 0.0;
    
//    delete lines;
    unsigned short *lines = (unsigned short*)malloc(sizeof(unsigned short)*(*numLines)*2);
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
    lines[0+2*10] = 5;  lines[1+2*10] = 2;
    lines[0+2*11] = 5;  lines[1+2*11] = 1;
    
//    delete faces;
    unsigned short *faces = (unsigned short*)malloc(sizeof(unsigned short)*(*numFaces)*3);
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

void _make_icosahedron(floater **po, unsigned int *numPoints,
                       unsigned short **li, unsigned int *numLines,
                       unsigned short **fa, unsigned int *numFaces){
    floater f = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
    *numPoints = 12;
    *numLines = 30;
    *numFaces = 20;
    
//    delete points;
    floater *points = (floater*)malloc(sizeof(floater)*(*numPoints)*3);
    printf("SIZE OF: %lu\n",sizeof(floater)*(*numPoints)*3);
    points[X+3*0] = 0.0;  points[Y+3*0] = 1.0/f;  points[Z+3*0] = phi/f;
    points[X+3*1] = 0.0;  points[Y+3*1] = -1.0/f;  points[Z+3*1] = phi/f;
    points[X+3*2] = 0.0;  points[Y+3*2] = -1.0/f;  points[Z+3*2] = -phi/f;
    points[X+3*3] = 0.0;  points[Y+3*3] = 1.0/f;  points[Z+3*3] = -phi/f;
    points[X+3*4] = phi/f;  points[Y+3*4] = 0.0;  points[Z+3*4] = 1.0/f;
    points[X+3*5] = -phi/f;  points[Y+3*5] = 0.0;  points[Z+3*5] = 1.0/f;
    points[X+3*6] = -phi/f;  points[Y+3*6] = 0.0;  points[Z+3*6] = -1.0/f;
    points[X+3*7] = phi/f;  points[Y+3*7] = 0.0;  points[Z+3*7] = -1.0/f;
    points[X+3*8] = 1.0/f;  points[Y+3*8] = phi/f;  points[Z+3*8] = 0.0;
    points[X+3*9] = -1.0/f;  points[Y+3*9] = phi/f;  points[Z+3*9] = 0.0;
    points[X+3*10] = -1.0/f;  points[Y+3*10] = -phi/f;  points[Z+3*10] = 0.0;
    points[X+3*11] = 1.0/f;  points[Y+3*11] = -phi/f;  points[Z+3*11] = 0.0;
    
//    delete lines;
    unsigned short *lines = (unsigned short*)malloc(sizeof(unsigned short)*(*numLines)*2);
    lines[0+2*0] = 0;  lines[1+2*0] = 8;
    lines[0+2*1] = 0;  lines[1+2*1] = 9;
    lines[0+2*2] = 0;  lines[1+2*2] = 1;
    lines[0+2*3] = 0;  lines[1+2*3] = 4;
    lines[0+2*4] = 0;  lines[1+2*4] = 5;
    lines[0+2*5] = 8;  lines[1+2*5] = 3;
    lines[0+2*6] = 8;  lines[1+2*6] = 9;
    lines[0+2*7] = 8;  lines[1+2*7] = 7;
    lines[0+2*8] = 8;  lines[1+2*8] = 4;
    lines[0+2*9] = 9;  lines[1+2*9] = 3;
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
    lines[0+2*20] = 10;  lines[1+2*20] = 11;
    lines[0+2*21] = 10;  lines[1+2*21] = 5;
    lines[0+2*22] = 10;  lines[1+2*22] = 6;
    lines[0+2*23] = 10;  lines[1+2*23] = 1;
    lines[0+2*24] = 11;  lines[1+2*24] = 1;
    lines[0+2*25] = 11;  lines[1+2*25] = 4;
    lines[0+2*26] = 4;  lines[1+2*26] = 1;
    lines[0+2*27] = 5;  lines[1+2*27] = 1;
    lines[0+2*28] = 5;  lines[1+2*28] = 6;
    lines[0+2*29] = 6;  lines[1+2*29] = 3;
    
//    delete faces;
    unsigned short *faces = (unsigned short*)malloc(sizeof(unsigned short)*(*numFaces)*3);
    faces[0+3*0] = 8;  faces[1+3*0] = 7;  faces[2+3*0] = 4;
    faces[0+3*1] = 8;  faces[1+3*1] = 3;  faces[2+3*1] = 7;
    faces[0+3*2] = 8;  faces[1+3*2] = 4;  faces[2+3*2] = 0;
    faces[0+3*3] = 8;  faces[1+3*3] = 0;  faces[2+3*3] = 9;
    faces[0+3*4] = 9;  faces[1+3*4] = 3;  faces[2+3*4] = 8;
    faces[0+3*5] = 9;  faces[1+3*5] = 0;  faces[2+3*5] = 5;
    faces[0+3*6] = 9;  faces[1+3*6] = 5;  faces[2+3*6] = 6;
    faces[0+3*7] = 9;  faces[1+3*7] = 6;  faces[2+3*7] = 3;
    
    faces[0+3*8] = 3;  faces[1+3*8] = 2;  faces[2+3*8] = 7;
    faces[0+3*9] = 3;  faces[1+3*9] = 6;  faces[2+3*9] = 2;
    faces[0+3*10] = 0;  faces[1+3*10] = 4;  faces[2+3*10] = 1;
    faces[0+3*11] = 0;  faces[1+3*11] = 1;  faces[2+3*11] = 5;
    
    faces[0+3*12] = 11;  faces[1+3*12] = 4;  faces[2+3*12] = 7;
    faces[0+3*13] = 11;  faces[1+3*13] = 7;  faces[2+3*13] = 2;
    faces[0+3*14] = 11;  faces[1+3*14] = 2;  faces[2+3*14] = 10;
    faces[0+3*15] = 11;  faces[1+3*15] = 10;  faces[2+3*15] = 1;
    faces[0+3*16] = 11;  faces[1+3*16] = 1;  faces[2+3*16] = 4;
    faces[0+3*17] = 10;  faces[1+3*17] = 6;  faces[2+3*17] = 5;
    faces[0+3*18] = 10;  faces[1+3*18] = 5;  faces[2+3*18] = 1;
    faces[0+3*19] = 10;  faces[1+3*19] = 2;  faces[2+3*19] = 6;
    
    // align 2 points to polar Y
    floater offset =  (M_2PI/4.) - atan( (1 + sqrt(5)) / 2 );
    floater distance, angle;
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
/*
void _generate_geodesic_normals(geodesic *g){
    // shortcuts are made possible
    //   due to all points lying on the surface
    //   of a sphere centered at the origin
    if(g->numPoints){
        floater length;
//        delete normals;
        g->pointNormals = (floater*)malloc(sizeof(floater)*g->numPoints*3);
        for(int i = 0; i < g->numPoints; i++){
//            length = 1.0;  // we should already know the radius of the sphere
            length = sqrtf( pow(g->points[X+3*i],2) + pow(g->points[Y+3*i],2) + pow(g->points[Z+3*i],2) );
            g->pointNormals[X+3*i] = g->points[X+3*i] / length;// * (i/12.0);
            g->pointNormals[Y+3*i] = g->points[Y+3*i] / length;// * (i/12.0);
            g->pointNormals[Z+3*i] = g->points[Z+3*i] / length;// * (i/12.0);
        }
    }
    if(g->numLines){
//        delete lineNormals;
        g->lineNormals = (floater*)malloc(sizeof(floater)*g->numLines*2);
        for(int i = 0; i < g->numLines; i++){
            g->lineNormals[i*2+X] = ( g->pointNormals[g->lines[i*2+0]*3+X] +
                                      g->pointNormals[g->lines[i*2+1]*3+X] ) / 2.0;
            g->lineNormals[i*2+Y] = ( g->pointNormals[g->lines[i*2+0]*3+Y] +
                                      g->pointNormals[g->lines[i*2+1]*3+Y] ) / 2.0;
            g->lineNormals[i*2+Z] = ( g->pointNormals[g->lines[i*2+0]*3+Z] +
                                      g->pointNormals[g->lines[i*2+1]*3+Z] ) / 2.0;
        }
    }
    if(g->numFaces){
//        delete faceNormals;
        g->faceNormals = (floater*)malloc(sizeof(floater)*g->numFaces*3);
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
}*/

//void Geodesic::OBJ(char *&data, int &length){
//    string obj;
//    obj.append("# GEODESIC SOLID\n# DOMEKIT\no ");
//    obj.append(to_string(v));
//    obj.append("V Geodesic ");
//    obj.append(title);
//    obj.append("\n");
//    for(int i = 0; i < numPoints; i++){
//        obj.append("v ");
//        obj.append(to_string((floater)points[i*3+0]));     obj.append(" ");
//        obj.append(to_string((floater)points[i*3+1]));     obj.append(" ");
//        obj.append(to_string((floater)points[i*3+2]));     obj.append("\n");
//    }
//    for(int i = 0; i < numFaces; i++){
//        obj.append("f ");
//        obj.append(to_string(1 + faces[i*3+0]));     obj.append(" ");
//        obj.append(to_string(1 + faces[i*3+1]));     obj.append(" ");
//        obj.append(to_string(1 + faces[i*3+2]));     obj.append("\n");
//    }
//    length = (int)obj.length();
//    data = (char*)calloc(obj.length(), sizeof(char));
//    memcpy(data, obj.c_str(), length);
//}

//void Geodesic::OBJ(string filename){
//    ofstream myfile;
//    myfile.open (filename);
//    myfile << "# geodesic dome object\n";
//    myfile << "# robby kraft\n";
//    myfile << "o Dome\n";
//    for(int i = 0; i < numPoints; i++)
//        myfile << "v " << points[i*3] << " " << points[i*3+1] << " " << points[i*3+2] << "\n";
//    for(int i = 0; i < numFaces; i++)
//        myfile << "f "<< faces[i*3] << " " << faces[i*3+1] << " " << faces[i*3+2] << "\n";
//    myfile.close();
//}

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

/*
void _divide_geodesic_faces(geodesic *g, int v){
    if(v > 1){
        // equation to calculate new points per face
        int pointsPerFace = 3;
        for(int i = 1; i < v; i++)
            pointsPerFace += (i+2);
        // new Points, Faces arrays, and their sizes
        floater newPointsArray[g->numFaces * pointsPerFace * 3 + g->numPoints];
        int newFacesArray[v*(v+1)*g->numFaces*3*3];   // data overflow problem. correctly approximate array size
        int newPI = 0;
        int newFI = 0;
        // original points in their original indeces
        for(int i = 0; i < g->numPoints; i++){
            newPointsArray[i*3+X] = g->points[i*3+X];
            newPointsArray[i*3+Y] = g->points[i*3+Y];
            newPointsArray[i*3+Z] = g->points[i*3+Z];
            newPI++;
        }
        // bring along the parent polyhedra's faces too, non-convex geometry
//        for(int i = 0; i < numFaces; i++){
//            newFacesArray[i*3+0] = faces[i*3+0];
//            newFacesArray[i*3+1] = faces[i*3+1];
//            newFacesArray[i*3+2] = faces[i*3+2];
//            newFI++;
//        }
        int i, j, k;
        float segments = v;
        floater *pointA, *pointB, *pointC;
        int faceA, faceB, faceC;
        floater AB[3], BC[3];
        int faceP1, faceP2, faceP3;
        for(i=0; i < g->numFaces; i++){
            // retain pointers to major 3 vertices
            faceA = g->faces[i*3 + 0];
            faceB = g->faces[i*3 + 1];
            faceC = g->faces[i*3 + 2];
            pointA = &g->points[faceA*3];
            pointB = &g->points[faceB*3];
            pointC = &g->points[faceC*3];
            // change from A to B / frequency, and B to C
            AB[X] = ( pointB[X] - pointA[X] ) / segments;
            AB[Y] = ( pointB[Y] - pointA[Y] ) / segments;
            AB[Z] = ( pointB[Z] - pointA[Z] ) / segments;
            BC[X] = ( pointC[X] - pointB[X] ) / segments;
            BC[Y] = ( pointC[Y] - pointB[Y] ) / segments;
            BC[Z] = ( pointC[Z] - pointB[Z] ) / segments;
            // iterate 1, 12, 123, 1234, 12345, 123456...
            for(j = 0; j <= v; j++){
                for(k = 0; k <= j; k++){
                    // skip the 3 original vertices
                    if(!((j == 0 && k == 0) || (j == v & k == 0) || (j == v && k == v))){  //ignore 3 points of the triangle
                        // POINTS
                        newPointsArray[newPI*3+X] = pointA[X] + j * AB[X] + k * BC[X];
                        newPointsArray[newPI*3+Y] = pointA[Y] + j * AB[Y] + k * BC[Y];
                        newPointsArray[newPI*3+Z] = pointA[Z] + j * AB[Z] + k * BC[Z];
                        newPI++;
                    }
                    // FACES
                    if(k != 0){
                        // build a vertical pointing triangle face
                        faceP1 = (newPI-1);
                        faceP2 = (newPI-1)-j-1;
                        faceP3 = (newPI-1)-1;
                        if(j == v) faceP2++;  // last row->parent row is offset by one because of skipping one of the original triangle points
                        if((j == v && k == v)){  // i have no idea why the last triangle on the last row differs from the other triangles on the last row
                            faceP2++;
                            faceP3++;
                        }
                        // special case, preserve 3 original points when available
                        if(j == 1) faceP2 = faceA;  // (original pointA)
                        if(j == v && k == 1) faceP3 = faceB;
                        if(j == v && k == v) faceP1 = faceC;
                        
                        newFacesArray[newFI*3+0] = faceP1;
                        newFacesArray[newFI*3+1] = faceP2;
                        newFacesArray[newFI*3+2] = faceP3;
                        newFI++;
                        
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
                    // LINES maybe?
                }
            }
        }
        
        g->numPoints = newPI;
//        delete g->points;
        free(g->points);
        g->points = (floater*)malloc(sizeof(floater)*g->numPoints*3);
        for(int i = 0; i < g->numPoints*3; i++)
            g->points[i] = newPointsArray[i];

        g->numFaces = newFI;
//        delete g->faces;
        free(g->faces);
        g->faces = (unsigned short*)malloc(sizeof(unsigned short)*g->numFaces*3);
        for(int i = 0; i < g->numFaces*3; i++)
            g->faces[i] = newFacesArray[i];
        
//        removeDuplicatePoints();
//        [self removeDuplicatePoints];
    }
}
 */
 
/*
void _remove_duplicate_points(geodesic *g)
{
//    NSMutableArray *duplicateIndexes = [[NSMutableArray alloc] init];
//    NSMutableArray *points = [[NSMutableArray alloc] init];
    int duplicateIndexes[g->numPoints];
    for(int i = 0; i < g->numPoints; i++)
        duplicateIndexes[i] = -1;
//    memset(duplicateIndexes, -1, numPoints);
    int i, j;
    int numDuplicates = 0;
//    bool found;
    double elbow = .00000000001;
    for(i = 0; i < g->numPoints - 1; i++){
        bool duplicate = false;
        for(j = i+1; j < g->numPoints; j++){
            if (g->points[X+i*3] - elbow < g->points[X+j*3] && g->points[X+i*3] + elbow > g->points[X+j*3] &&
                g->points[Y+i*3] - elbow < g->points[Y+j*3] && g->points[Y+i*3] + elbow > g->points[Y+j*3] &&
                g->points[Z+i*3] - elbow < g->points[Z+j*3] && g->points[Z+i*3] + elbow > g->points[Z+j*3] )
            {
                //NSLog(@"Duplicates(X): %.21g %.21g",[points_[i] getX], [points_[j] getX]);
//                [duplicateIndexes addObject:[[NSNumber alloc] initWithInt:j]];
                duplicateIndexes[j] = i;
                duplicate = true;
            }
        }
        if(duplicate)
            numDuplicates++;
    }
    for(i = 0; i < g->numPoints; i++){
        printf("P: %d\n",duplicateIndexes[i]);
    }
    
    for(i = 0; i < g->numPoints; i++)
        if(duplicateIndexes[i] != -1)
            for(int f = 0; i < g->numFaces; i++)
                for(int e = 0; e < 3; e++)
                    if(g->faces[f*3+e] == i)
                        g->faces[f*3+e] = duplicateIndexes[i];

    for(i = 0; i < g->numLines; i++)
        if(duplicateIndexes[i] != -1)
            for(int f = 0; i < g->numLines; i++)
                for(int e = 0; e < 2; e++)
                    if(g->lines[f*2+e] == i)
                        g->lines[f*2+e] = duplicateIndexes[i];

    floater newPointsArray[g->numPoints - numDuplicates];
    int index = 0;
    for(i = 0; i < g->numPoints; i++){
        if(duplicateIndexes[i] == -1){
            newPointsArray[index] = g->points[i];
            index++;
        }
    }
    
//    delete points;
    g->numPoints = g->numPoints - numDuplicates;
    memcpy(g->points, newPointsArray, g->numPoints);
    
//    for(i = 0; i < numPoints; i++)
//    {
//        found = false;
//        for(j = 0; j < duplicateIndexes.count; j++){
//            if(i == [duplicateIndexes[j] integerValue])
//                found = true;
//                }
//        if(!found) [points addObject:points_[i]];
//    }
//    points_ = [[NSArray alloc] initWithArray:points];

}*/

void _spherize_points(floater *points, unsigned int numPoints){
    int i;
    floater difference, distance;
    floater maxdistance = 1.0;//sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
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

// V0: 1           +2 =
// V1: 3 per face  +3 =
// V2: 6           +4 =
// V3: 10          +5 =
// V4: 15          +6 =
// V5: 21

// V1: 3    3
// V2: 9    1*3 + 2*3
// V3: 18   1*3 + 2*3 + 3*3
// V4: 30
/*
void Geodesic::initDiagramData(){
    
    delete lineClass;
    delete lineClassLengths;
    lineClass = (int*)malloc(sizeof(int)*numLines);
    // this now gets allocated at the end of classifyLines() //    lineClassLengths = (floater*)malloc(sizeof(floater)*numLines);   // allocating WAY too many places
    for(int i = 0; i < numLines; i++){
        lineClass[i] = 0;
    }
    lineClassLengths[0] = sqrt((points[lines[1] + X] - points[lines[0] + X]) * (points[lines[1] + X] - points[lines[0] + X]) +
                               (points[lines[1] + Y] - points[lines[0] + Y]) * (points[lines[1] + Y] - points[lines[0] + Y]) +
                               (points[lines[1] + Z] - points[lines[0] + Z]) * (points[lines[1] + Z] - points[lines[0] + Z]) );
}

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

void Geodesic::classifyLines(){
    int i, j;
    unsigned int rounded;
    floater distance;
    bool found;
    unsigned int elbow = 100000000;
    double nudge = .00000000001;
    unsigned int lengths[numLines];  // allocating WAY too much space here
    floater originalLengths[numLines];     // "
    
    int numLengths = 0;
    int numOriginalLengths = 0;
    
    for(i = 0; i < numLines; i++){
        // all lines, calculate distance
        distance = sqrt(  pow(points[ lines[i*2+0] + X] - points[ lines[i*2+1] + X],2)
                        + pow(points[ lines[i*2+0] + Y] - points[ lines[i*2+1] + Y],2)
                        + pow(points[ lines[i*2+0] + Z] - points[ lines[i*2+1] + Z],2));
        // ignore all but 8 decimal places
        rounded = floor((distance+nudge)*elbow);
        // begin building lengths array
        if(i == 0){
            // first one will always be new, add it to the list
            lineClass[0] = 0;
            lengths[0] = rounded;
            originalLengths[0] = distance;
            
            numLengths++;
            numOriginalLengths++;
        }
        else{
            // search existing lengths
            found = false;
            j = 0;
            while(!found && j < numLengths){
                if(rounded == lengths[j]){
                    // if found, set the lineClass to point to an index in lengths
                    found = true;
                    lineClass[i] = j;
                    //NSLog(@"O:%.21g ->%d",distance,j);
                }
                j++;
            }
            if(!found){
                // if not found, make a new entry in lengths and originalLengths, point line class to it.
                lineClass[i] = j;
                lengths[numLengths] = rounded;
                originalLengths[numOriginalLengths] = distance;
                
                numLengths++;
                numOriginalLengths++;
                //NSLog(@"O:%.21g ->%d",distance,j);
            }
        }
    }
    
    // copy line lengths data into an appropriately sized array
    lineClassLengths = (floater*)malloc(sizeof(floater)*numOriginalLengths);
    for(int i = 0; i < numOriginalLengths; i++)
        lineClassLengths[i] = originalLengths[i];
    
    //    NSLog(@"%d, %d", lineClass.count, lines_.count);
    //for(i=0; i < lineClass_.count; i++) NSLog(@"%d", [lineClass_[i] integerValue]);
    //NSLog(@"%d, %d, %d", lines_.count, lineClass_.count, lineClassLengths_.count);
    //NSLog(@"*****************");
    //for(i=0; i < lineClassLengths_.count; i++) NSLog(@"Strut %d: %f", i, [lineClassLengths_[i] floatValue]);
}

//-(void) removeDuplicateLines
//{
//    //Unwrapping NSNumbers is slow as fuck. first step = convert to C array
//    NSMutableArray *lines = [[NSMutableArray alloc] initWithArray:lines_];
//    int linesC[lines_.count];
//    int i, j, count = [lines count];
//    bool duplicates[lines_.count];
//    
//    for(i = 0; i < lines_.count; i++)
//    {
//        linesC[i] = [lines_[i] integerValue];
//        duplicates[i] = false;
//    }
//    for(i = 0; i < count; i+=2)
//    {
//        for(j = i+2; j < count; j+=2)
//        {
//            if ( (linesC[i] == linesC[j] && linesC[i+1] == linesC[j+1]) ||
//                (linesC[i] == linesC[j+1] && linesC[i+1]== linesC[j] ) )
//            {
//                duplicates[j] = [[NSNumber alloc] initWithBool:true];
//            }
//        }
//    }
//    for(i=lines_.count-2; i >= 0; i-=2)
//    {
//        if(duplicates[i] == true)[lines removeObjectsInRange:NSMakeRange(i, 2)];
//    }
//    lines_ = [[NSArray alloc] initWithArray:lines];
//}
//
 */


geodesic tetrahedron(int v){
    geodesic g;
    _make_tetrahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
//    _divide_geodesic_faces(&g, v);
//    _spherize_points(g.points, g.numPoints);
//    _generate_geodesic_normals(&g);
    return g;
}

geodesic icosahedron(int v){
    geodesic g;
    _make_icosahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
//    _divide_geodesic_faces(&g, v);
//    _spherize_points(g.points, g.numPoints);
//    _generate_geodesic_normals(&g);
    return g;
}

geodesic octahedron(int v){
    geodesic g;
    _make_octahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
//    _divide_geodesic_faces(&g, v);
//    _spherize_points(g.points, g.numPoints);
//    _generate_geodesic_normals(&g);
    return g;
}
