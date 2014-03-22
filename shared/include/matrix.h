#include <vector2d.h>

typedef float matrix2d[9];

void matrix2d_concat(matrix2d* source,matrix2d* m);
void matrix2d_rotate(matrix2d* source,float angle);
void matrix2d_transform_vector2d(matrix2d* source,vector2d* v);

void matrix2d_get_identity(matrix2d* output);

void matrix2d_print(matrix2d* source);