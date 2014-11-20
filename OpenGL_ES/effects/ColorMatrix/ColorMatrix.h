#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <utils.h>

#define VIEW_W 500.0
#define VIEW_H 400.0

void initGray();
void update(int eclipse);
void render();
void updateHue(float H);
void updateSat(float S);
void updateBri(float B);