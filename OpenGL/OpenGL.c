#include <GL/glut.h>
#include "OpenGL.h"
#include <stdio.h>

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    //glutCreateWindow("第一个OpenGL程序");
	glutCreateWindow("First OpenGL Program");
	const char* version = (const char*)glGetString(GL_VERSION);
	printf("OpenGL version %s\n", version);
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}