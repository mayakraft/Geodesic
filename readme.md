# geodesic geometry generator

points, lines, and triangles (clockwise winding), vertex normals, face normals

OBJ file export

# methods

``` c++
 // make a sphere
geodesic.icosahedron(3)  // 3V icosahedron
geodesic.tetrahedron(4)  // 4V tetrahedron
geodesic.octahedron(1)  // an octahedron

 // crop sphere into 5/9 dome
geodesic.crop(5/9.); 
```

## mesh class

make OpenGL representation of geodesic object

![picture](https://raw.github.com/robbykraft/Geodesic/master/picture.png)
