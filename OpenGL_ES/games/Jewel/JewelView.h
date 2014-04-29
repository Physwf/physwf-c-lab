#include <EGL/egl.h>
#include <GLES2/gl2.h>

#define VIEW_W 640
#define VIEW_H 640
#define GRID_SIZE 80

void initView();
void render();
void onMousePressed(float x,float y);