
#import "Geodesic.h"

#define phi (1 + sqrt(5)) / 2.0

#define X 0
#define Y 1
#define Z 2

void Geodesic::loadTetrahedron(){
    
    double side = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
    
    numPoints = 4;
    numLines = 6;
    numFaces = 4;
    
    delete points;
    points = (double*)malloc(sizeof(double)*numPoints*3);
    
    points[X+3*0] = 0.0;    points[Y+3*0] = side;    points[Z+3*0] = side;
    points[X+3*1] = 0.0;    points[Y+3*1] = side;    points[Z+3*1] = -side;
    points[X+3*2] = side;   points[Y+3*2] = -side;   points[Z+3*2] = 0.0;
    points[X+3*3] = -side;  points[Y+3*3] = -side;   points[Z+3*3] = 0.0;
    
    delete lines;
    lines = (int*)malloc(sizeof(int)*numLines*2);
    
    lines[0+2*0] = 0;  lines[1+2*0] = 1;
    lines[0+2*1] = 0;  lines[1+2*1] = 2;
    lines[0+2*2] = 0;  lines[1+2*2] = 3;
    lines[0+2*3] = 1;  lines[1+2*3] = 2;
    lines[0+2*4] = 1;  lines[1+2*4] = 3;
    lines[0+2*5] = 2;  lines[1+2*5] = 3;
    
    delete faces;
    faces = (int*)malloc(sizeof(int)*numFaces*3);
    
    faces[0+3*0] = 0;  faces[1+3*0] = 1;  faces[2+3*0] = 2;
    faces[0+3*1] = 0;  faces[1+3*1] = 1;  faces[2+3*1] = 3;
    faces[0+3*2] = 2;  faces[1+3*2] = 3;  faces[2+3*2] = 0;
    faces[0+3*3] = 2;  faces[1+3*3] = 3;  faces[2+3*3] = 1;
    
    //    alignTetrahedron();
}

void Geodesic::alignTetrahedron(){
    double offset =  -M_PI/4.0f;
    double distance, angle;
    //rotate around the z until one point is at the zenith, along the (Y or X?) axis
    for(int i = 0; i < numPoints; i++){
        angle = atan2(points[i*3+X], points[i*3+Y]);
        distance = sqrt( pow(points[i*3+X], 2) + pow(points[i*3+Y], 2) );
        points[i*3+X] = distance*sin(angle+offset);
        points[i*3+Y] = distance*cos(angle+offset);
        //points[i*3+Z] stays the same
    }
}

void Geodesic::loadOctahedron(){
    
    double radius = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
    
    numPoints = 6;
    numLines = 12;
    numFaces = 8;
    
    delete points;
    points = (double*)malloc(sizeof(double)*numPoints*3);
    
    points[X+3*0] = 0.0;      points[Y+3*0] = radius;   points[Z+3*0] = 0.0;
    points[X+3*1] = radius;   points[Y+3*1] = 0.0;      points[Z+3*1] = 0.0;
    points[X+3*2] = 0.0;      points[Y+3*2] = 0.0;      points[Z+3*2] = -radius;
    
    points[X+3*3] = -radius;  points[Y+3*3] = 0.0;      points[Z+3*3] = 0.0;
    points[X+3*4] = 0.0;      points[Y+3*4] = 0.0;      points[Z+3*4] = radius;
    points[X+3*5] = 0.0;      points[Y+3*5] = -radius;  points[Z+3*5] = 0.0;
    
    delete lines;
    lines = (int*)malloc(sizeof(int)*numLines*2);
    
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
    
    delete faces;
    faces = (int*)malloc(sizeof(int)*numFaces*3);
    
    faces[0+3*0] = 0;  faces[1+3*0] = 4;  faces[2+3*0] = 1;
    faces[0+3*1] = 0;  faces[1+3*1] = 1;  faces[2+3*1] = 2;
    faces[0+3*2] = 0;  faces[1+3*2] = 2;  faces[2+3*2] = 3;
    faces[0+3*3] = 0;  faces[1+3*3] = 3;  faces[2+3*3] = 4;
    faces[0+3*4] = 5;  faces[1+3*4] = 1;  faces[2+3*4] = 4;
    faces[0+3*5] = 5;  faces[1+3*5] = 4;  faces[2+3*5] = 3;
    faces[0+3*6] = 5;  faces[1+3*6] = 3;  faces[2+3*6] = 2;
    faces[0+3*7] = 5;  faces[1+3*7] = 2;  faces[2+3*7] = 1;
}

void Geodesic::loadIcosahedron(){
    
    numPoints = 12;
    numLines = 30;
    numFaces = 20;
    
    delete points;
    points = (double*)malloc(sizeof(double)*numPoints*3);
    
    points[X+3*0] = 0.0;  points[Y+3*0] = 1.0;  points[Z+3*0] = phi;
    points[X+3*1] = 0.0;  points[Y+3*1] = -1.0;  points[Z+3*1] = phi;
    points[X+3*2] = 0.0;  points[Y+3*2] = -1.0;  points[Z+3*2] = -phi;
    points[X+3*3] = 0.0;  points[Y+3*3] = 1.0;  points[Z+3*3] = -phi;
    points[X+3*4] = phi;  points[Y+3*4] = 0.0;  points[Z+3*4] = 1.0;
    points[X+3*5] = -phi;  points[Y+3*5] = 0.0;  points[Z+3*5] = 1.0;
    points[X+3*6] = -phi;  points[Y+3*6] = 0.0;  points[Z+3*6] = -1.0;
    points[X+3*7] = phi;  points[Y+3*7] = 0.0;  points[Z+3*7] = -1.0;
    points[X+3*8] = 1.0;  points[Y+3*8] = phi;  points[Z+3*8] = 0.0;
    points[X+3*9] = -1.0;  points[Y+3*9] = phi;  points[Z+3*9] = 0.0;
    points[X+3*10] = -1.0;  points[Y+3*10] = -phi;  points[Z+3*10] = 0.0;
    points[X+3*11] = 1.0;  points[Y+3*11] = -phi;  points[Z+3*11] = 0.0;
    
    delete lines;
    lines = (int*)malloc(sizeof(int)*numLines*2);
    
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
    
    delete faces;
    faces = (int*)malloc(sizeof(int)*numFaces*3);
    
    faces[0+3*0] = 0;  faces[1+3*0] = 8;  faces[2+3*0] = 9;
    faces[0+3*1] = 0;  faces[1+3*1] = 8;  faces[2+3*1] = 4;
    faces[0+3*2] = 0;  faces[1+3*2] = 9;  faces[2+3*2] = 5;
    faces[0+3*3] = 0;  faces[1+3*3] = 1;  faces[2+3*3] = 4;
    faces[0+3*4] = 0;  faces[1+3*4] = 1;  faces[2+3*4] = 5;
    faces[0+3*5] = 8;  faces[1+3*5] = 3;  faces[2+3*5] = 9;
    faces[0+3*6] = 8;  faces[1+3*6] = 3;  faces[2+3*6] = 7;
    faces[0+3*7] = 8;  faces[1+3*7] = 7;  faces[2+3*7] = 4;
    faces[0+3*8] = 9;  faces[1+3*8] = 3;  faces[2+3*8] = 6;
    faces[0+3*9] = 9;  faces[1+3*9] = 6;  faces[2+3*9] = 5;
    
    faces[0+3*10] = 7;  faces[1+3*10] = 4;  faces[2+3*10] = 11;
    faces[0+3*11] = 7;  faces[1+3*11] = 3;  faces[2+3*11] = 2;
    faces[0+3*12] = 7;  faces[1+3*12] = 2;  faces[2+3*12] = 11;
    faces[0+3*13] = 2;  faces[1+3*13] = 10;  faces[2+3*13] = 11;
    faces[0+3*14] = 2;  faces[1+3*14] = 10;  faces[2+3*14] = 6;
    faces[0+3*15] = 2;  faces[1+3*15] = 3;  faces[2+3*15] = 6;
    faces[0+3*16] = 10;  faces[1+3*16] = 11;  faces[2+3*16] = 1;
    faces[0+3*17] = 10;  faces[1+3*17] = 5;  faces[2+3*17] = 6;
    faces[0+3*18] = 10;  faces[1+3*18] = 5;  faces[2+3*18] = 1;
    faces[0+3*19] = 11;  faces[1+3*19] = 1;  faces[2+3*19] = 4;
    
    alignIcosahedron();
}

void Geodesic::alignIcosahedron(){
    double offset =  (M_PI/2) - atan( (1 + sqrt(5)) / 2 );
    double distance, angle;
    //rotate around the z until one point is at the zenith, along the (Y or X?) axis
    for(int i = 0; i < numPoints; i++){
        angle = atan2(points[i*3+X], points[i*3+Y]);
        distance = sqrt( pow(points[i*3+X], 2) + pow(points[i*3+Y], 2) );
        points[i*3+X] = distance*sin(angle+offset);
        points[i*3+Y] = distance*cos(angle+offset);
        //points[i*3+Z] stays the same
    }
}

void Geodesic::generateNormals(){
    if(numPoints){
        delete normals;
        normals = (double*)malloc(sizeof(double)*numPoints*3);
        for(int i = 0; i < numPoints; i++){
            float length = sqrtf( pow(points[X+3*i],2) + pow(points[Y+3*i],2) + pow(points[Z+3*i],2) );
            normals[X+3*i] = points[X+3*i] / length;
            normals[Y+3*i] = points[Y+3*i] / length;
            normals[Z+3*i] = points[Z+3*i] / length;
        }
    }
}

void Geodesic::initShape(){
    v = 1;
    
    delete visiblePoints;
    delete visibleLines;
    delete visibleFaces;
    delete lineClass;
    delete lineClassLengths;
    visiblePoints = (bool*)malloc(sizeof(bool)*numPoints);
    visibleLines = (bool*)malloc(sizeof(bool)*numLines);
    visibleFaces = (bool*)malloc(sizeof(bool)*numFaces);
    lineClass = (int*)malloc(sizeof(int)*numLines);
    // this now gets allocated at the end of classifyLines()
    //    lineClassLengths = (double*)malloc(sizeof(double)*numLines);   // allocating WAY too many places
    
    for(int i = 0; i < numPoints; i++)
        visiblePoints[i] = true;
    for(int i = 0; i < numLines; i++){
        visibleLines[i] = true;
        lineClass[i] = 0;
    }
    for(int i = 0; i < numFaces; i++)
        visibleFaces[i] = true;
    
    lineClassLengths[0] = sqrt((points[lines[1] + X] - points[lines[0] + X]) * (points[lines[1] + X] - points[lines[0] + X]) +
                               (points[lines[1] + Y] - points[lines[0] + Y]) * (points[lines[1] + Y] - points[lines[0] + Y]) +
                               (points[lines[1] + Z] - points[lines[0] + Z]) * (points[lines[1] + Z] - points[lines[0] + Z]) );
}

void Geodesic::setTetrahedron(){
    loadTetrahedron();
    generateNormals();
    //    initShape();
}

void Geodesic::setIcosahedron(){
    loadIcosahedron();
    generateNormals();
    //    initShape();
}

void Geodesic::setOctahedron(){
    loadOctahedron();
    generateNormals();
    //    initShape();
}

void Geodesic::classifyLines(){
    int i, j;
    unsigned int rounded;
    double distance;
    bool found;
    unsigned int elbow = 100000000;
    double nudge = .00000000001;
    unsigned int lengths[numLines];  // allocating WAY too much space here
    double originalLengths[numLines];     // "
    
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
    lineClassLengths = (double*)malloc(sizeof(double)*numOriginalLengths);
    for(int i = 0; i < numOriginalLengths; i++)
        lineClassLengths[i] = originalLengths[i];
    
    //    NSLog(@"%d, %d", lineClass.count, lines_.count);
    //for(i=0; i < lineClass_.count; i++) NSLog(@"%d", [lineClass_[i] integerValue]);
    //NSLog(@"%d, %d, %d", lines_.count, lineClass_.count, lineClassLengths_.count);
    //NSLog(@"*****************");
    //for(i=0; i < lineClassLengths_.count; i++) NSLog(@"Strut %d: %f", i, [lineClassLengths_[i] floatValue]);
}

void Geodesic::geodecise(int vFreq){
    if(primitiveType == 0)
        loadIcosahedron();
    else if (primitiveType == 1)
        loadOctahedron();
    else if (primitiveType == 2)
        loadTetrahedron();
    divideFaces(vFreq);
    spherize();
    if(vFreq != 1)
        connectTheDots();
    classifyLines();
}

//-(void) geodeciseTriangle:(int)vNum
//{
//    [self loadTriangle];
//    [self divideFaces:vNum];
//    //[self spherize];
//    icosahedron = true;
//    if(vNum!=1)[self connectTheDots];
//    [self classifyLines];
//}

// V0: 1           +2 =
// V1: 3 per face  +3 =
// V2: 6           +4 =
// V3: 10          +5 =
// V4: 15          +6 =
// V5: 21

void Geodesic::divideFaces(int vFreq){
    v = vFreq;
    if(v > 1)
    {
        //NSLog(@"DivideFaces");
        int pointsPerFace = 3;
        for(int i = 1; i < vFreq; i++)
            pointsPerFace += (i+2);
        double newPointsArray[numFaces * pointsPerFace * 3];
        printf("This needs to be tested - the number of points after a subdivision was just approximated");
        int newI = 0;
        
        int i, j, k;//, counter = 0;
        double pointA[3];
        double pointB[3];
        double pointC[3];
        double xAB, xAC, yAB, yAC, zAB, zAC;
        for(i=0; i < numFaces*3; i+=3)  // this is backwards from how i was doing it
        {
            pointA[X] = points[faces[i+0] + X];  pointA[Y] = points[faces[i+0] + Y];  pointA[Z] = points[faces[i+0] + Z];
            pointB[X] = points[faces[i+1] + X];  pointB[Y] = points[faces[i+1] + Y];  pointB[Z] = points[faces[i+1] + Z];
            pointC[X] = points[faces[i+2] + X];  pointC[Y] = points[faces[i+2] + Y];  pointC[Z] = points[faces[i+2] + Z];
            
            xAB = ( pointB[X] - pointA[X] ) / (double)v;
            yAB = ( pointB[Y] - pointA[Y] ) / (double)v;
            zAB = ( pointB[Z] - pointA[Z] ) / (double)v;
            xAC = ( pointC[X] - pointA[X] ) / (double)v;
            yAC = ( pointC[Y] - pointA[Y] ) / (double)v;
            zAC = ( pointC[Z] - pointA[Z] ) / (double)v;
            
            for(j = 0; j <= v; j++)
            {
                for(k = 0; k <= v - j; k++)
                {
                    if(!((j == 0 && k == 0) || (j == 0 & k == v) || (j == v && k == v)))
                    {
                        newPointsArray[newI*3+X] = pointA[X] + j * xAB + k * xAC;
                        newPointsArray[newI*3+Y] = pointA[Y] + j * yAB + k * yAC;
                        newPointsArray[newI*3+Z] = pointA[Z] + j * zAB + k * zAC;
                    }
                }
            }
        }
        numPoints = newI;
        delete points;
        memcpy(points, newPointsArray, newI);
        //        points_ = [[NSArray alloc] initWithArray:points];
        //        removeDuplicatePoints();
        //        [self removeDuplicatePoints];
    }
}

void Geodesic::spherize(){
    int i;
    double difference, distance;
    double maxdistance = 0;
    /*for(i = 0; i < points_.count; i++){
     distance = sqrt(pow([points_[i] getX], 2) + pow([points_[i] getY], 2) + pow([points_[i] getZ], 2) );
     if(distance > maxdistance) maxdistance = distance;
     }*/
    // never mind, i already know the max distance
    maxdistance = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
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

void Geodesic::connectTheDots()
{
    // Calibrated for Regular Domes
    //    NSMutableArray *lines = [[NSMutableArray alloc] init];
    //    int lines[];
    int i, j;
    double elbow = .0000002;
    double distanceSquared, shortest, ceiling;
    bool firstRun;
    for(i = 0; i < 1; i++){  // Shortcut for regular dome
        firstRun = true;
        for(j=0; j < numPoints; j++){
            if(j != i){
                distanceSquared= pow( points[j*3+X] - points[i*3+X], 2) +
                pow( points[j*3+Y] - points[i*3+Y], 2) +
                pow( points[j*3+Z] - points[i*3+Z], 2);
                if(firstRun){
                    shortest = distanceSquared;
                    firstRun = false;
                }
                else{
                    if(distanceSquared+elbow < shortest) shortest = distanceSquared;
                }
            }
        }
    }
    if(primitiveType == 1) ceiling = shortest * 3.4;  // octahedron
    else if (primitiveType == 0) ceiling = shortest * 2.5;  //1.5 if using Distance, not DistanceSquared
    else if (primitiveType == 2) {printf("FAIL: connectTheDots() not set up for Tetrahedra");}
    //all further line segments will be based on this shortest value:
    for(i = 0; i < numPoints; i++){
        for(j=0; j < numPoints; j++){
            if(j != i){
                distanceSquared = pow( points[j*3+X] - points[i*3+X], 2) +
                pow( points[j*3+Y] - points[i*3+Y], 2) +
                pow( points[j*3+Z] - points[i*3+Z], 2);
                if(distanceSquared < ceiling){
                    //                    [lines addObjectsFromArray:[[NSArray alloc] initWithObjects:[[NSNumber alloc] initWithInt:i],
                    //                                                                                [[NSNumber alloc] initWithInt:j],
                    //                                                                                nil]];
                }
            }
        }
    }
    //    lines_ = [[NSArray alloc] initWithArray:lines];
    //    [self removeDuplicateLines];
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
//-(void) removeDuplicatePoints
//{
//    NSMutableArray *duplicateIndexes = [[NSMutableArray alloc] init];
//    NSMutableArray *points = [[NSMutableArray alloc] init];
//    int i, j;
//    bool found;
//    double elbow = .00000000001;
//    for(i = 0; i < points_.count - 1; i++)
//    {
//        for(j = i+1; j < points_.count; j++)
//        {
//            if ([points_[i] getX] - elbow < [points_[j] getX] && [points_[i] getX] + elbow > [points_[j] getX] &&
//                [points_[i] getY] - elbow < [points_[j] getY] && [points_[i] getY] + elbow > [points_[j] getY] &&
//                [points_[i] getZ] - elbow < [points_[j] getZ] && [points_[i] getZ] + elbow > [points_[j] getZ] )
//            {
//                //NSLog(@"Duplicates(X): %.21g %.21g",[points_[i] getX], [points_[j] getX]);
//                [duplicateIndexes addObject:[[NSNumber alloc] initWithInt:j]];
//            }
//        }
//    }
//    for(i = 0; i < points_.count; i++)
//    {
//        found = false;
//        for(j = 0; j < duplicateIndexes.count; j++){
//            if(i == [duplicateIndexes[j] integerValue])
//                found = true;
//        }
//        if(!found) [points addObject:points_[i]];
//    }
//    points_ = [[NSArray alloc] initWithArray:points];
//}
//
//-(void) loadTriangle
//{
//    points_ = [[NSArray alloc] initWithObjects: [[Point3D alloc] initWithCoordinatesX:-1 Y:sqrt(3)/2 Z:100],
//               [[Point3D alloc] initWithCoordinatesX:1 Y:sqrt(3)/2 Z:100],
//               [[Point3D alloc] initWithCoordinatesX:0 Y:-sqrt(3)/2 Z:100], nil];
//    lines_ = [[NSArray alloc] initWithObjects:  [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:0], nil];
//    faces_ = [[NSArray alloc] initWithObjects:
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:2],nil];
//    invisiblePoints_ = [[NSArray alloc] initWithObjects:[[NSNumber alloc] initWithBool:FALSE],
//                        [[NSNumber alloc] initWithBool:FALSE],
//                        [[NSNumber alloc] initWithBool:FALSE],nil];
//    invisibleLines_ = [[NSArray alloc] initWithObjects:
//                       [[NSNumber alloc] initWithBool:FALSE],[[NSNumber alloc] initWithBool:FALSE],
//                       [[NSNumber alloc] initWithBool:FALSE],[[NSNumber alloc] initWithBool:FALSE],
//                       [[NSNumber alloc] initWithBool:FALSE],[[NSNumber alloc] initWithBool:FALSE], nil];
//    lineClass_ = [[NSArray alloc] initWithObjects:  [[NSNumber alloc] initWithInt:1],
//                  [[NSNumber alloc] initWithInt:1],
//                  [[NSNumber alloc] initWithInt:1],nil];
//    lineClassLengths_ = [[NSArray alloc] initWithObjects:   [[NSNumber alloc] initWithInt:2],
//                         [[NSNumber alloc] initWithInt:2],
//                         [[NSNumber alloc] initWithInt:2],nil];
//}


//-(id) initWithDome:(Dome*) input
//{
//    points_ = [[NSArray alloc] initWithArray:input.points_];
//    lines_ = [[NSArray alloc] initWithArray:input.lines_];
//    faces_ = [[NSArray alloc] initWithArray:input.faces_];
//    invisiblePoints_ = [[NSArray alloc] initWithArray:input.invisiblePoints_];
//    invisibleLines_ = [[NSArray alloc] initWithArray:input.invisibleLines_];
//    lineClass_ = [[NSArray alloc] initWithArray:input.lineClass_];
//    lineClassLengths_ = [[NSArray alloc] initWithArray:input.lineClassLengths_];
//    v = input.v;
//    return self;
//}

//-(id) initWithTriangle
//{
//    [self loadTriangle];
//    v = 1;
//    return self;
//}

//-(void) setIcosahedron {icosahedron = true;}
//-(void) setOctahedron {icosahedron = false;}

//-(void) loadOctahedron
//{
//    double radius = sqrt( ((1 + sqrt(5)) / 2 ) + 2 );
//    points_ = [[NSArray alloc] initWithObjects:
//               [[Point3D alloc] initWithCoordinatesX:0 Y:radius Z:0],
//               [[Point3D alloc] initWithCoordinatesX:radius Y:0 Z:0],
//               [[Point3D alloc] initWithCoordinatesX:0 Y:0 Z:-radius],
//
//               [[Point3D alloc] initWithCoordinatesX:-radius Y:0 Z:0],
//               [[Point3D alloc] initWithCoordinatesX:0 Y:0 Z:radius],
//               [[Point3D alloc] initWithCoordinatesX:0 Y:-radius Z:0], nil];
//
//    lines_ = [[NSArray alloc] initWithObjects:
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:4],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:1],
//              nil];
//
//    faces_ = [[NSArray alloc] initWithObjects:
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:4],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:4],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:1],
//              nil];
//}
//
//-(void) loadIcosahedron
//{
//    double phi = (1 + sqrt(5)) / 2;
//    points_ = [[NSArray alloc] initWithObjects:[[Point3D alloc] initWithCoordinatesX:0 Y:1 Z:phi],
//                                               [[Point3D alloc] initWithCoordinatesX:0 Y:-1 Z:phi],
//                                               [[Point3D alloc] initWithCoordinatesX:0 Y:-1 Z:-phi],
//                                               [[Point3D alloc] initWithCoordinatesX:0 Y:1 Z:-phi],
//
//                                               [[Point3D alloc] initWithCoordinatesX:phi Y:0 Z:1],
//                                               [[Point3D alloc] initWithCoordinatesX:-phi Y:0 Z:1],
//                                               [[Point3D alloc] initWithCoordinatesX:-phi Y:0 Z:-1],
//                                               [[Point3D alloc] initWithCoordinatesX:phi Y:0 Z:-1],
//
//                                               [[Point3D alloc] initWithCoordinatesX:1 Y:phi Z:0],
//                                               [[Point3D alloc] initWithCoordinatesX:-1 Y:phi Z:0],
//                                               [[Point3D alloc] initWithCoordinatesX:-1 Y:-phi Z:0],
//                                               [[Point3D alloc] initWithCoordinatesX:1 Y:-phi Z:0], nil];
//
//    lines_ = [[NSArray alloc] initWithObjects:
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:8],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:9],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:5],
//              [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:9],
//              [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:7],
//              [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:9],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:9],[[NSNumber alloc] initWithInt:6],
//              [[NSNumber alloc] initWithInt:9],[[NSNumber alloc] initWithInt:5],
//              [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:2],
//              [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:11],
//              [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:10],
//              [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:11],
//              [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:3],
//              [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:6],
//              [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:11],
//              [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:5],
//              [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:6],
//              [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:11],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:11],[[NSNumber alloc] initWithInt:4],
//              [[NSNumber alloc] initWithInt:4],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:1],
//              [[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:6],
//              [[NSNumber alloc] initWithInt:6],[[NSNumber alloc] initWithInt:3],
//              nil];
//
//    faces_ = [[NSArray alloc] initWithObjects:
//            [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:9],
//            [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:4],
//            [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:9],[[NSNumber alloc] initWithInt:5],
//            [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:4],
//            [[NSNumber alloc] initWithInt:0],[[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:5],
//            [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:9],
//            [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:7],
//            [[NSNumber alloc] initWithInt:8],[[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:4],
//            [[NSNumber alloc] initWithInt:9],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:6],
//            [[NSNumber alloc] initWithInt:9],[[NSNumber alloc] initWithInt:6],[[NSNumber alloc] initWithInt:5],
//            [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:4],[[NSNumber alloc] initWithInt:11],
//            [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:2],
//            [[NSNumber alloc] initWithInt:7],[[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:11],
//            [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:11],
//            [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:6],
//            [[NSNumber alloc] initWithInt:2],[[NSNumber alloc] initWithInt:3],[[NSNumber alloc] initWithInt:6],
//            [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:11],[[NSNumber alloc] initWithInt:1],
//            [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:6],
//            [[NSNumber alloc] initWithInt:10],[[NSNumber alloc] initWithInt:5],[[NSNumber alloc] initWithInt:1],
//            [[NSNumber alloc] initWithInt:11],[[NSNumber alloc] initWithInt:1],[[NSNumber alloc] initWithInt:4],
//            nil];
//
//    [self alignIcosahedron];
//}
//
//-(void) alignIcosahedron
//{
//    NSMutableArray *points = [[NSMutableArray alloc] init];
//    double offset =  (M_PI/2) - atan( (1 + sqrt(5)) / 2 );
//    double distance, angle;
//    for(int i = 0; i < points_.count; i++)
//    {
//        angle = atan2([points_[i] getX], [points_[i] getY]);
//        distance = sqrt( pow([points_[i] getX], 2) + pow([points_[i] getY], 2) );
//        [points addObject:[[Point3D alloc] initWithCoordinatesX:distance*sin(angle+offset)
//                                                              Y:distance*cos(angle+offset)
//                                                              Z:[points_[i] getZ]]];
//    }
//    points_ = [[NSArray alloc] initWithArray:points];
//}

/*
-(void) generateFaces
{
    // trace every three-line segment paths, record all paths which are closed
    int i, j, k;
    BOOL found;
    NSNumber *first, *second, *third;   // an index to a Point3D in points_
    NSMutableArray *faces = [[NSMutableArray alloc] init];
    for(i=0;i < lines_.count; i+=2)
    {
        first = lines_[i];
        second = lines_[i+1];
        // search all paths to find another point which touches either *first or *second
        for(j=0; j < lines_.count; j+=2)
        {
            third = nil;
            if (lines_[j] == first && lines_[j+1] != second) third = lines_[j+1];
                else if(lines_[j+1] == first && lines_[j] != second) third = lines_[j];
                    if(third != nil)
                    {
                        found = false;
                        // search all paths again to confirm point touches both *first and *second
                        for(k=0; k< lines_.count; k+=2)
                            if( (lines_[k] == third && lines_[k+1] == second) || (lines_[k] == second && lines_[k+1] == third) )
                                found = true;
                                
                                if(found) [faces addObjectsFromArray:[[NSArray alloc] initWithObjects:first, second, third, nil]];
                    }
        }
    }
    
    // remove duplicates
    for (i = 0; i < faces.count; i+=3) {
        first = faces[i];
        second = faces[i+1];
        third = faces[i+2];
        for (j = 0; j < faces.count; j+=3) {
            if (j != i) {
                if ((first == faces[j] && second == faces[j+1] && third == faces[j+2]) ||
                    (second == faces[j] && first == faces[j+1] && third == faces[j+2]) ||
                    (first == faces[j] && third == faces[j+1] && second == faces[j+2]) ||
                    (second == faces[j] && third == faces[j+1] && first == faces[j+2]) ||
                    (third == faces[j] && first == faces[j+1] && second == faces[j+2]) ||
                    (third == faces[j] && second == faces[j+1] && first == faces[j+2]))
                {
                    [faces removeObjectsInRange:NSMakeRange(j, 3)];
                    j-=3;
                }
            }
        }
    }
    for(i=0; i < faces.count; i+=3) NSLog(@"%@ -- %@ -- %@", faces[i], faces[i+1], faces[i+2]);
        faces_ = [[NSArray alloc] initWithArray:faces];
        }
*/
