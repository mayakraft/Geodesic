#include "geodiagram.h"

#include "geodesic.h"

#include <stdlib.h>
#include <math.h>

void _classify_lines(geodesicNet *diagram, geodesic *g);

geodesicNet makeDiagram(geodesic *g){
    geodesicNet diagram;
    
//    delete lineClass;
//    delete lineClassLengths;
    diagram.lineCategory = malloc(sizeof(unsigned int)*g->numLines);
    // this now gets allocated at the end of classifyLines()
    diagram.lineCategoryLengths = malloc(sizeof(double)*g->numLines);   //TODO: allocating WAY too many places
    for(int i = 0; i < g->numLines; i++){
        diagram.lineCategory[i] = 0;
    }
    diagram.lineCategoryLengths[0] =
                sqrt((g->points[g->lines[1] + X] - g->points[g->lines[0] + X]) * (g->points[g->lines[1] + X] - g->points[g->lines[0] + X]) +
                     (g->points[g->lines[1] + Y] - g->points[g->lines[0] + Y]) * (g->points[g->lines[1] + Y] - g->points[g->lines[0] + Y]) +
                     (g->points[g->lines[1] + Z] - g->points[g->lines[0] + Z]) * (g->points[g->lines[1] + Z] - g->points[g->lines[0] + Z]) );
    
    
    _classify_lines(&diagram, g);
    return diagram;
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


void _classify_lines(geodesicNet *diagram, geodesic *g){
    int i, j;
    unsigned int rounded;
    float_ distance;
    unsigned short found;  // bool
    //TODO: gotta test 128 bit sometime
    unsigned long long ELBOW_INV = 1.0/ELBOW;

    unsigned int lengths[g->numLines];  // allocating WAY too much space here
    float_ originalLengths[g->numLines];     // "
    
    for(int i = 0; i < g->numLines; i++){
        lengths[i] = 0;
        originalLengths[i] = 0.0;
    }
    int numLengths = 0;
    int numOriginalLengths = 0;
    
    for(i = 0; i < g->numLines; i++){
        // all lines, calculate distance
        distance = sqrt(  pow(g->points[ g->lines[i*2+0] + X] - g->points[ g->lines[i*2+1] + X],2)
                        + pow(g->points[ g->lines[i*2+0] + Y] - g->points[ g->lines[i*2+1] + Y],2)
                        + pow(g->points[ g->lines[i*2+0] + Z] - g->points[ g->lines[i*2+1] + Z],2));
        // ignore all but 8 decimal places
        rounded = floor((distance+ELBOW)*ELBOW_INV);
        // begin building lengths array
        if(i == 0){
            // first one will always be new, add it to the list
            diagram->lineCategory[0] = 0;
            lengths[0] = rounded;
            originalLengths[0] = distance;
            
            numLengths++;
            numOriginalLengths++;
        }
        else{
            // search existing lengths
            found = 0;
            j = 0;
            while(!found && j < numLengths){
                if(rounded == lengths[j]){
                    // if found, set the lineClass to point to an index in lengths
                    found = 1;
                    diagram->lineCategory[i] = j;
                    //NSLog(@"O:%.21g ->%d",distance,j);
                }
                j++;
            }
            if(!found){
                // if not found, make a new entry in lengths and originalLengths, point line class to it.
                diagram->lineCategory[i] = j;
                lengths[numLengths] = rounded;
                originalLengths[numOriginalLengths] = distance;
                
                numLengths++;
                numOriginalLengths++;
                //NSLog(@"O:%.21g ->%d",distance,j);
            }
        }
    }
    
    // copy line lengths data into an appropriately sized array
    diagram->lineCategoryLengths = malloc(sizeof(double)*numOriginalLengths);
    for(int i = 0; i < numOriginalLengths; i++)
        diagram->lineCategoryLengths[i] = originalLengths[i];
    
//    printf("%d, %d\n", numLengths, numOriginalLengths);
//    for(i=0; i < g->numLines; i++)
//        printf("%d\n", lengths[i]);
//    printf("%d, %d, %d\n", lines_.count, lineClass_.count, lineClassLengths_.count);
//    printf("*****************\n");
//    for(i=0; i < numOriginalLengths; i++)
//        printf("Strut %d: %f\n", i, diagram->lineCategoryLengths[i]);

//    NSLog(@"%d, %d", lineClass.count, lines_.count);
//    for(i=0; i < lineClass_.count; i++) NSLog(@"%d", [lineClass_[i] integerValue]);
//    NSLog(@"%d, %d, %d", lines_.count, lineClass_.count, lineClassLengths_.count);
//    NSLog(@"*****************");
//    for(i=0; i < lineClassLengths_.count; i++) NSLog(@"Strut %d: %f", i, [lineClassLengths_[i] floatValue]);
}



/*void drawDiagram(){
    int halfHeight = [self bounds].size.height / 2.0;
    int halfWidth = [self bounds].size.width / 2.0;
    Point3D *point1 = [[Point3D alloc] init];
    Point3D *point2 = [[Point3D alloc] init];
    int count, countByOne;
    double angle, yOffset, scale;
    double lowest = 0;
    double fisheye; // close-to-sphere domes are further extended at their edges to prevent overlapping lines
    
    CGFloat dashedLine[2] = {0.5,1.5};
    
    //NSArray *lengthOrder = [[NSArray alloc] initWithArray:[self getLengthOrder]];
    
    for(count = 0; count < dome.points_.count; count++)
    {
        if( count != octantis &&[dome.invisiblePoints_[count] boolValue] == FALSE)
        {
            yOffset = asin([dome.points_[count] getY]/1.9022) / (M_PI/2) + 1;
            if(yOffset > lowest) lowest = yOffset;
        }
    }
    if([dome.invisiblePoints_[octantis] boolValue] == TRUE)
    {
        if(lowest > 1.63) scale = size/(lowest*1.25);
        else scale = size/(lowest);
    }
    else scale = size/(2.5);
    
    [[UIColor colorWithWhite:1.0 alpha:1.0] setStroke];
    CGContextSetLineWidth(context, lineWidth);
    CGContextSetLineCap(context, kCGLineCapRound);
    
    int index1, index2;
    countByOne = 0;
    for(count = 0; count < dome.lines_.count; count+=2)
    {
        //if( [lengthOrder[ [dome.lineClass_[countByOne] integerValue] ]integerValue] < colorTable.count-1)
        //    [(UIColor*)colorTable[[lengthOrder[ [dome.lineClass_[countByOne] integerValue] ]integerValue]] setStroke];
        if( [ dome.lineClass_[countByOne] integerValue] < colorTable.count-1)
            [(UIColor*)colorTable[ [dome.lineClass_[countByOne] integerValue]] setStroke];
        else
            [(UIColor*)colorTable[colorTable.count-1] setStroke];
        
        if( [dome.invisibleLines_[count] boolValue] == FALSE)
        {
            index1 = [dome.lines_[count] integerValue];
            index2 = [dome.lines_[count+1] integerValue];
            if(index1 != octantis && index2 != octantis)
            {
                point1 = dome.points_[index1];
                point2 = dome.points_[index2];
                
                angle = atan2([point1 getZ],
                              [point1 getX]);
                yOffset = asin([point1 getY]/1.9022) / (M_PI/2) + 1;
                
                if(yOffset > 1.63) fisheye = pow((yOffset-1.63)/(lowest-1.63),8)*.25+1;
                else fisheye = 1;
                
                CGContextBeginPath(context);
                CGContextMoveToPoint(context, fisheye*yOffset*sin(angle)*scale+halfWidth,
                                     fisheye*yOffset*cos(angle)*scale+halfHeight);
                angle = atan2([point2 getZ],
                              [point2 getX]);
                yOffset = asin([point2 getY]/1.9022) / (M_PI/2) + 1;
                
                if(yOffset > 1.63) fisheye = pow((yOffset-1.63)/(lowest-1.63),8)*.25+1;
                else fisheye = 1;
                
                CGContextAddLineToPoint(context, fisheye*yOffset*sin(angle)*scale+halfWidth,
                                        fisheye*yOffset*cos(angle)*scale+halfHeight);
                CGContextClosePath(context);
                CGContextDrawPath(context, kCGPathFillStroke);
            }
            else
            {
                point1 = dome.points_[index1];
                point2 = dome.points_[index2];
                if (index1 == octantis)
                {
                    angle = atan2([point2 getZ],
                                  [point2 getX]);
                    yOffset = asin([point2 getY]/1.9022) / (M_PI/2) + 1;
                    if(yOffset > 1.63) fisheye = pow((yOffset-1.63)/(lowest-1.63),8)*.25+1;
                    else fisheye = 1;
                }
                else if(index2 == octantis)
                {
                    angle = atan2([point1 getZ],
                                  [point1 getX]);
                    yOffset = asin([point1 getY]/1.9022) / (M_PI/2) + 1;
                    if(yOffset > 1.63) fisheye = pow((yOffset-1.63)/(lowest-1.63),8)*.25+1;
                    else fisheye = 1;
                }
                CGContextBeginPath(context);
                CGContextSetLineDash(context, 0.0f, dashedLine, 2);
                CGContextSetLineCap(context, kCGLineCapButt);
                CGContextMoveToPoint(context, fisheye*yOffset*sin(angle)*scale+halfWidth,
                                     fisheye*yOffset*cos(angle)*scale+halfHeight);
                CGContextAddLineToPoint(context, fisheye*2*sin(angle)*scale+halfWidth,
                                        fisheye*2*cos(angle)*scale+halfHeight);
                CGContextClosePath(context);
                CGContextDrawPath(context, kCGPathFillStroke);
                CGContextSetLineDash(context, 0, NULL, 0);
                CGContextSetLineCap(context, kCGLineCapRound);
            }
        }
        countByOne++;
    }
}*/


