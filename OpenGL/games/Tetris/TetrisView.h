#define VIEW_W 200
#define VIEW_H 300

#include "utils.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glew32s.lib")
#pragma comment(lib,"freeglut.lib")

extern bool initialized;

void initView();
void display();
void update(int value);
void onKeyBoardEvent(int keycode,int x,int y);