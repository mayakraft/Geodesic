#include <math.h>
#include "platonic.c"

#define X 0
#define Y 1
#define Z 2

#include "geodesic.h"

// SPHERE
void _divide_geodesic_faces(geodesic *g, int v);
void _remove_duplicate_points_lines(geodesic *g);
void _spherize_points(float_t *points, unsigned int numPoints);
void _apply_geodesic_sphere_normals(geodesic *g);

// DOME
void _make_meridians(geodesicDome *dome, int v);
void _crop_geodesic(geodesicDome *dome, unsigned short crop);


// TODO:
// for cropping
// introduce this idea of rows
// each triangle is a member of a row
// starting from the top, 5 triangles in row 1
// 10 in row 2
// 15 in row 3
// ...
// rows will be encoded into the platonic solids
//


geodesic tetrahedron(int v){
    geodesic g;
    _tetrahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
    _divide_geodesic_faces(&g, v);
    _spherize_points(g.points, g.numPoints);
    _apply_geodesic_sphere_normals(&g);
    return g;
}
geodesic octahedron(int v){
    geodesic g;
    _octahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
    _divide_geodesic_faces(&g, v);
    _spherize_points(g.points, g.numPoints);
    _apply_geodesic_sphere_normals(&g);
    return g;
}
geodesic icosahedron(int v){
    geodesic g;
    _icosahedron(&g.points, &g.numPoints, &g.lines, &g.numLines, &g.faces, &g.numFaces);
    _divide_geodesic_faces(&g, v);
    _spherize_points(g.points, g.numPoints);
    _apply_geodesic_sphere_normals(&g);
    return g;
}

geodesicDome tetrahedronDome(int v, float crop) {
    geodesicDome dome;
    _tetrahedron(&(dome.g).points, &(dome.g).numPoints, &(dome.g).lines, &(dome.g).numLines, &(dome.g).faces, &(dome.g).numFaces);
    _divide_geodesic_faces(&(dome.g), v);
    // _make_meridians(&dome, v); // does not work with tetrahedron, I think
    _spherize_points((dome.g).points, (dome.g).numPoints);
    _apply_geodesic_sphere_normals(&(dome.g));
    _crop_geodesic(&dome, crop*v);
    return dome;
}
geodesicDome octahedronDome(int v, float crop) {
    geodesicDome dome;
    _octahedron(&(dome.g).points, &(dome.g).numPoints, &(dome.g).lines, &(dome.g).numLines, &(dome.g).faces, &(dome.g).numFaces);
    _divide_geodesic_faces(&(dome.g), v);
    _make_meridians(&dome, v);
    _spherize_points((dome.g).points, (dome.g).numPoints);
    _apply_geodesic_sphere_normals(&(dome.g));
    _crop_geodesic(&dome, crop*v);
    return dome;
}
geodesicDome icosahedronDome(int v, float crop) {
    geodesicDome dome;
    _icosahedron(&(dome.g).points, &(dome.g).numPoints, &(dome.g).lines, &(dome.g).numLines, &(dome.g).faces, &(dome.g).numFaces);
    _divide_geodesic_faces(&(dome.g), v);
    _make_meridians(&dome, v);
    _spherize_points((dome.g).points, (dome.g).numPoints);
    _apply_geodesic_sphere_normals(&(dome.g));
    _crop_geodesic(&dome, crop*v);
    return dome;
}

void deleteGeodesic(geodesic *g){
    // be careful with this one:
    // an initially unallocated geodesic will still register
    // TRUE on the if()s and call free() and crash
    g->numPoints = 0;
    g->numLines = 0;
    g->numFaces = 0;
    if(g->points){          free(g->points);        g->points = NULL; }
    if(g->lines){           free(g->lines);         g->lines = NULL; }
    if(g->faces){           free(g->faces);         g->faces = NULL; }
    if(g->pointNormals){    free(g->pointNormals);  g->pointNormals = NULL; }
    if(g->lineNormals){     free(g->lineNormals);   g->lineNormals = NULL; }
    if(g->faceNormals){     free(g->faceNormals);   g->faceNormals = NULL; }
}

void deleteGeodesicDome(geodesicDome *d){
    // same. be careful with this one
    deleteGeodesic(&(d->g));
    if(d->faceAltitudes){   free(d->faceAltitudes);   d->faceAltitudes = NULL;  }
    if(d->faceMeridians){   free(d->faceMeridians);   d->faceMeridians = NULL;  }
    if(d->pointMeridians){  free(d->pointMeridians);  d->pointMeridians = NULL; }
}

void _apply_geodesic_sphere_normals(geodesic *g){
    // shortcuts are made possible due to
    // - all points lying on the surface of a sphere
    // - centered at the origin
    if(g->numPoints){
//        float_t length = 1.0;  // shortcut
        g->pointNormals = malloc(sizeof(float_t)*g->numPoints*3);
        for(int i = 0; i < g->numPoints; i++){
//            length = sqrtf( pow(g->points[X+3*i],2) + pow(g->points[Y+3*i],2) + pow(g->points[Z+3*i],2) ); // shortcut: radius of the sphere
            g->pointNormals[X+3*i] = g->points[X+3*i];//  / length;// * (i/12.0);
            g->pointNormals[Y+3*i] = g->points[Y+3*i];//  / length;// * (i/12.0);
            g->pointNormals[Z+3*i] = g->points[Z+3*i];//  / length;// * (i/12.0);
        }
    }
    if(g->numLines){
        g->lineNormals = malloc(sizeof(float_t)*g->numLines*3);
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
        g->faceNormals = malloc(sizeof(float_t)*g->numFaces*3);
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
        float_t newPointsArray[g->numFaces * pointsPerFace * 3 + g->numPoints];
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
        float_t *edgePointA, *edgePointB, *edgePointC;
        // vectors: line segments AB and BC divided by the frequency number
        float_t dAB[3], dBC[3];
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
        g->points = malloc(sizeof(float_t)*g->numPoints*3);
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
        // that have the same coordinates into one point
        // and update pointers in lines[] and faces[] arrays
        _remove_duplicate_points_lines(g);
    }
}

void _spherize_points(float_t *points, unsigned int numPoints){
    int i;
    float_t difference, distance;
    float_t maxdistance = 1.0;//sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
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


////////////////////////////////////
//
//       DOME FUNCTIONS
//
////////////////////////////////////

int _qsort_compare (const void * a, const void * b){
    if (*(float_t*)a < *(float_t*)b) return -1;
    if (*(float_t*)a > *(float_t*)b) return 1;
    return 0;
}
void _make_meridians(geodesicDome *d, int v){
    geodesic *g = &(d->g);
    float_t meridianFaceData[g->numFaces];
    float_t lowest;
    // sort faces by their lowest point (in the Y-axis)
    for(int i = 0; i < g->numFaces; i++){
        lowest = g->points[g->faces[i*3+0]*3+1];
        if(g->points[g->faces[i*3+1]*3+1] < lowest)
            lowest = g->points[g->faces[i*3+1]*3+1];
        if(g->points[g->faces[i*3+2]*3+1] < lowest)
            lowest = g->points[g->faces[i*3+2]*3+1];
        meridianFaceData[i] = lowest;
    }
    /////////////////////
    d->numMeridians = 0;
    float_t pointMeridians[g->numFaces];
    for(int i = 0; i < g->numFaces; i++)
        pointMeridians[i] = 0;
    for(int i = 0; i < g->numFaces; i++){
        unsigned short alreadyEntered = 0;
        for(int j = 0; j < d->numMeridians; j++){
            if(floorf((pointMeridians[j]+.00001)*1000.0) == floorf((meridianFaceData[i]+.00001)*1000.0))
                alreadyEntered = 1;
        }
        if(!alreadyEntered){
            pointMeridians[d->numMeridians] = meridianFaceData[i];
            d->numMeridians++;
        }
    }
    // add one last row
    pointMeridians[d->numMeridians] = 1.0;
//    g->numMeridians++;  // don't increment so that it's relative to faces, not points
    qsort(pointMeridians, d->numMeridians, sizeof(float_t), _qsort_compare);
    d->pointMeridians = malloc(sizeof(float_t)*(d->numMeridians+1));
    for(int i = 0; i < d->numMeridians+1; i++)
        d->pointMeridians[i] = pointMeridians[i];
    
    //TODO: will crash if no meridians are found
    
    d->faceMeridians = malloc(sizeof(float_t)*d->numMeridians);

    for(int i = 0; i < d->numMeridians; i++)
        d->faceMeridians[i] = (pointMeridians[i] + pointMeridians[i+1])*.5;

    d->faceAltitudes = malloc(sizeof(unsigned short)*g->numFaces);
    for(int i = 0; i < g->numFaces; i++)
        d->faceAltitudes[i] = 99;
    for(int i = 0; i < g->numFaces; i++){
        for(unsigned short j = 0; j < d->numMeridians+1; j++){
            if(floorf((pointMeridians[j]+.00001)*1000.0) == floorf((meridianFaceData[i]+.00001)*1000.0)){
                d->faceAltitudes[i] = j;
                break;
            }
        }
    }

//    printf("NUM MERIDIANS: %d\n",g->numMeridians);
//    for(int i = 0; i < g->numMeridians; i++){
//        printf("%d: P:%f\n",i, g->pointMeridians[i]);
//        printf(" -  F:%f\n", g->faceMeridians[i]);
//    }
//    printf("%d: P:%f\n",g->numMeridians, g->pointMeridians[g->numMeridians]);
//    printf("FACES stacking order: %d\n",g->numMeridians);
//    for(int i = 0; i < g->numFaces; i++){
//        printf(":%d\n", g->faceAltitudes[i]);
//    }
}

void _crop_geodesic(geodesicDome *d, unsigned short crop){
    // if(crop >= g->numMeridians) return;
    
    // float_t newPointsArray[g->numPoints];
    // for(int i = 0; i < g->numPoints; i++){
        
    // }
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

// sample 128 precision: 1.189731495357231765085759326628007
// sample 64 precision: 1.7976931348623157
// sample 32 precision: 3.4028234
#if _float_tprecision==128
#define ELBOW .0000000000000001
#elif _float_tprecision==64
#define ELBOW .00000000001
#elif _float_tprecision==32
#define ELBOW .00001
#else
#define ELBOW .00001
#endif

// subdividing faces without face-neighbor data allows more freedom
// for the algorithm to work on many objects, but requires more work:
// for each set of joined faces duplicate points will be generated along their shared line

void _remove_duplicate_points_lines(geodesic *g){
    
    // make array of size numPoints which looks like this:
    // -1  -1  -1  -1   3  -1  -1  -1  -1  -1  5   5  -1  -1  -1
    // mostly -1s, except at duplicate points, store the index of the first instance of duplication
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

    float_t *newPointsArray = malloc(sizeof(float_t)*newNumPoints*3);
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
