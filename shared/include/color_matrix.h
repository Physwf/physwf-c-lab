#define IDENTITY {1,0,0,0,0,  0,1,0,0,0,  0,0,1,0,0,  0,0,0,1,0}

typedef float color_matrix[20];

void adjustHue(color_matrix mat,float value);
void adjustSaturation(color_matrix mat,float sat);
void adjustBrightness(color_matrix mat,float value);
void adjustContrast(color_matrix mat,float value);
void invert(color_matrix mat);
void concat(color_matrix left,color_matrix right,color_matrix out);
void color_matrix_print(color_matrix cm);