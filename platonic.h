// the 3 platonic solids made of triangles
// centered at origin
// radius = 1
// one point along +Y axis

void _tetrahedron(float_t **po, unsigned int *numPoints,
                  unsigned short **li, unsigned int *numLines,
                  unsigned short **fa, unsigned int *numFaces);
void _octahedron(float_t **po, unsigned int *numPoints,
                 unsigned short **li, unsigned int *numLines,
                 unsigned short **fa, unsigned int *numFaces);
void _icosahedron(float_t **po, unsigned int *numPoints,
                  unsigned short **li, unsigned int *numLines,
                  unsigned short **fa, unsigned int *numFaces);