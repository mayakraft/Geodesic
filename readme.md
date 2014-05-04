# geodesic geometry generator

R. Buckminster Fuller method 1 spheres and domes from icosahedra, octahedra, and tetrahedra

# properties

``` c
unsigned int    numPoints;
unsigned int    numLines;
unsigned int    numFaces;

float           *points;  // count(numPoints*3)
unsigned short  *lines;   // count(numLines*2)
unsigned short  *faces;   // count(numFaces*3), clockwise winding
    
float           *pointNormals;  // count(numPoints*3)
float           *lineNormals;   // count(numLines*3)
float           *faceNormals;   // count(numFaces*3)
```

# methods

``` c
// get a geodesic object
geodesic icosahedron(int v);
geodesic octahedron(int v);
geodesic tetrahedron(int v);

geodesic tetrahedronDome(int v, float crop);
geodesic octahedronDome(int v, float crop);
geodesic icosahedronDome(int v, float crop);

/// wait, migrating from C++
//export OBJ file

// render
void geodesicDrawTriangles(geodesic *g);  // GL_TRIANGLES
void geodesicDrawLines(geodesic *g);      // GL_LINES
void geodesicDrawPoints(geodesic *g);   // GL_POINTS

// free() object
void freeGeodesic(geodesic *g);
```

# usage

``` c
 // make a sphere
geodesic sphere1 = icosahedron(3)  // 3V icosahedron
geodesic sphere2 = tetrahedron(4)  // 4V tetrahedron
geodesic sphere3 = octahedron(1)  // a regular octahedron

 // make a dome
geodesic dome1 = icosahedronDome(3, 5/9.); // 3V 5/9 dome
geodesic dome2 = octahedronDome(8, 1/2.); // 8V 8/16 dome

 // reuse an object, free it first
freeGeodesic(&dome);  // don’t call unless it’s been allocated!

 // in an OpenGL context
glPushMatrix();
geodesicDrawTriangles(&dome);
glPopMatrix();
```

![picture](https://raw.github.com/robbykraft/Geodesic/master/picture.png)
