# geodesic geometry

R. Buckminster Fuller method 1 spheres and domes from icosahedra or octahedra

# try it out

`make` then `./world`

# files

* `platonic.h/.c` static platonic solids geometry
* `geodesic.h/.c` process a platonic solid into a geodesic dome or sphere
* `geomesh.h/.c`  make an OpenGL ES mesh of a geodesic object

# data

* points are stored (X, Y, Z) as `float` or `double`
* lines/faces are pairs/trios of indices in point array `unsigned short`
* you also get number of points, lines, and faces as an `unsigned int`
* point, line, and face normals as (X, Y, Z) `float` or `double`

# methods

### undergoing lots of development right now. features being added, functions changing, this will be updated in the end

``` c
 // geodesic sphere
geodesicSphere icosahedronSphere(int v);
geodesicSphere octahedronSphere(int v);
geodesicSphere tetrahedronSphere(int v);

 // geodesic dome
geodesicDome icosahedronDome(int v, float crop);
geodesicDome octahedronDome(int v, float crop);
geodesicDome tetrahedronDome(int v, float crop);
```

# usage

``` c
 // make
geodesicSphere icosphere = icosahedron(3)  // 3v icosahedron
geodesicDome dome = icosahedronDome(3, 5/9);  // 3v 5/9 dome
// draw
geodesicDrawTriangles(&icosphere);

// make
geomeshTriangles mesh = makeMeshTriangles(&icosphere, .75){
// draw
geodesicMeshDrawExtrudedTriangles(&mesh);

// make
geomeshNormals normals = makeMeshNormals(&icosphere);
// draw
geodesicMeshDrawVertexNormalLines(&normals);
geodesicMeshDrawFaceNormalLines(&normals);
```

``` c
 // remember to delete
deleteGeodesicSphere(&geodesic);
deleteGeodesicDome(&dome);

deleteMeshNormals(&normals);
deleteMeshTriangles(&mesh);
```

![picture](https://raw.github.com/robbykraft/Geodesic/master/picture.png)