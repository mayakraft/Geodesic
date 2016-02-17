# geodesic geometry

R. Buckminster Fuller method 1 spheres and domes from icosahedra or octahedra

# try it out

`make` then `make run`

![picture](https://raw.github.com/robbykraft/Geodesic/master/bin/demo.gif)

# files

* `geodesic.h + .c` data
* `OpenGL/mesh.h + .c` rendering, and more mesh data for rendering

# geodesic.h / .c

### types
``` c
 // sphere
geodesicSphere icosahedronSphere(int v);
geodesicSphere octahedronSphere(int v);
geodesicSphere tetrahedronSphere(int v);
 // dome
geodesicDome icosahedronDome(int v, float crop);
geodesicDome octahedronDome(int v, float crop);
geodesicDome tetrahedronDome(int v, float crop);
```

### usage
``` c
geodesicSphere icosphere = icosahedron(3)  // 3v icosahedron
geodesicDome dome = icosahedronDome(3, 5/9);  // 3v 5/9 dome
```

now you have access to points, lines, face, as well as normals data. For domes, there's also more complicated data involved in slicing the sphere into a dome including number of slice meridians, triangle count on each row, relationship of face to row number.

# mesh.h / .c

### initialize
``` c
geodesicMeshTriangles mesh = makeMeshTriangles(&icosphere, .75){
geodesicMeshNormals normals = makeMeshNormals(&icosphere);
```

### draw
``` c
// draw geodesic objects
drawGeodesicTriangles(&icosphere);
drawDomeMeshTriangles(&dome, &domeTriangleMesh);

// draw mesh objects
drawGeodesicExtrudedTriangles(&mesh);
drawGeodesicVertexNormalLines(&normals);
drawGeodesicFaceNormalLines(&normals);
```

# memory

delete geometry when you are done

``` c
deleteGeodesicSphere(&geodesic);
deleteGeodesicDome(&dome);

deleteMeshNormals(&normals);
deleteMeshTriangles(&mesh);
```

![picture](https://raw.github.com/robbykraft/Geodesic/master/bin/picture.png)