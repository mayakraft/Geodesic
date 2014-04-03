//
//  Mesh.h
//  StagingArea
//
//  Created by Robby Kraft on 3/27/14.
//  Copyright (c) 2014 Robby Kraft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>
#import "Geodesic.h"

@class OBJ;

@interface GeodesicMesh : NSObject

-(void) load:(Geodesic*)geodesic;

-(void) draw;  // (draw triangles)

-(void) drawPoints;
-(void) drawLines;
-(void) drawNormalLines;
-(void) drawFaceNormalLines;

@end
