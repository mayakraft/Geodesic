# geodesic geometry generator

points, lines, faces in clockwise winding

# methods

``` c++
 // make a sphere
geodesic.icosahedron(3)  // 3V icosahedron
geodesic.tetrahedron(4)  // 4V tetrahedron
geodesic.octahedron(1)  // an octahedron

 // crop sphere into 5/9 dome
geodesic.crop(5/9.); 
```