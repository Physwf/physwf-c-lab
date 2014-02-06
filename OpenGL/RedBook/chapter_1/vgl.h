#include <iostream>

#if defined(WIN)
#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glew32s.lib")
#pragma comment(lib,"freeglut.lib")
#endif

#if defined(MAC)
#include <GLUT/glut.h>
#endif

#define BUFFER_OFFSET(bytes) ((GLubyte *) NULL + (bytes))

