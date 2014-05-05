# geodesic geometry

R. Buckminster Fuller method 1 spheres and domes from icosahedra, octahedra, and tetrahedra

# properties

``` c
 unsigned int    numPoints;
 unsigned int    numLines;
 unsigned int    numFaces;

 double          *points;  // count(numPoints*3)
 unsigned short  *lines;   // count(numLines*2)
 unsigned short  *faces;   // count(numFaces*3), clockwise winding
    
 double          *pointNormals;  // count(numPoints*3)
 double          *lineNormals;   // count(numLines*3)
 double          *faceNormals;   // count(numFaces*3)
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

// free memory
void deleteGeodesic(geodesic *g);
```

# usage

``` c
 // make a sphere
geodesic icosphere = icosahedron(3)  // 3V icosahedron
geodesic octahedron = octahedron(1)  // a regular octahedron (1V)

 // or make a dome
geodesic dome = icosahedronDome(3, 5/9.);  // 3V 5/9 dome

 // reuse an object, free it first
deleteGeodesic(&dome);  // don’t call unless it’s been allocated!
```

![picture](https://raw.github.com/robbykraft/Geodesic/master/picture.png)