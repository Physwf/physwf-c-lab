#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <math.h>

#define RADIUS 64.0

#define VIEW_W 640.0//NUM_POPO_ROW*RADIUS
#define VIEW_H 560.0

#define FIRE_POS_X VIEW_W/2
#define FIRE_POS_Y VIEW_H

extern const float EVEN_OFFSET_X;
extern const float ODD_OFFSET_X;
extern const float OFFSET_Y;

extern const float DIST_ROW;
extern const float DIST_COLLUM;

extern const float TEX_TYPES[4][2];

void initView();
void render();
void onMousePressed(int x,int y);