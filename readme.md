# geodesic geometry

R. Buckminster Fuller method 1 spheres and domes from icosahedra, octahedra, and tetrahedra

# properties

``` c
 unsigned int    numPoints;
 unsigned int    numLines;
 unsigned int    numFaces;

 double          *points;        // numPoints*3
 unsigned short  *lines;         // numLines*2
 unsigned short  *faces;         // numFaces*3, clockwise winding
    
 double          *pointNormals;  // numPoints*3
 double          *lineNormals;   // numLines*3
 double          *faceNormals;   // numFaces*3
```

# methods

``` c
 // geodesic sphere
geodesic icosahedron(int v);
geodesic octahedron(int v);
geodesic tetrahedron(int v);

 // geodesic dome
geodesic icosahedronDome(int v, float crop);
geodesic octahedronDome(int v, float crop);
geodesic tetrahedronDome(int v, float crop);
```

# usage

``` c
 // make
geodesic icosphere = icosahedron(3)  // 3v icosahedron
geodesic octahedron = octahedron(1)  // regular octahedron
geodesic dome = icosahedronDome(3, 5/9);  // 3v 5/9 dome

 // remember to delete
deleteGeodesic(&dome);
```

![picture](https://raw.github.com/robbykraft/Geodesic/master/picture.png)