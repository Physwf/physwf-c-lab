#include <EGL/egl.h>
#include <GLES2/gl2.h>

#define VIEW_W 640.0
#define VIEW_H 640.0
#define GRID_SIZE 80.0

void initView();
void render();
void onMousePressed(float x,float y);