//
//  geodesic
//  overhead assembly diagram generator
//  Copyright (c) 2013 Robby Kraft
//  MIT License
//

#ifndef __geodesic__diagram__
#define __geodesic__diagram__

struct geodesic;

typedef struct geodesicNet geodesicNet;

struct geodesicNet{
    float           *points;  // 2D points, a circle diagram growing from the center (0,0) 2x2 square from (-1 to 1)
    unsigned short  *lines;
    unsigned short  *faces;
    
    unsigned int    *pointCategory;
    unsigned int    *lineCategory;
    unsigned int    *faceCategory;
    
    double          *lineCategoryLengths;
};

geodesicNet makeDiagram(struct geodesic *g);

#endif
