#include <GL/glew.h>
#include <GL/glut.h>
#include "OpenGL.h"
#include <stdio.h>


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glutWireSphere(0.5,50,50);
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
	glutCreateWindow("First OpenGL Program");
	glClearColor(0.0,0.0,0.0,0.5);
	const char* version =  (const char*)glGetString(GL_VERSION);
	printf("OpenGL version %s\n",version);
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		printf("glew error");
	}
	// const GLubyte *str = glGetString(GL_EXTENSIONS); 
	// printf("%s",str);
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
	// getchar();
    return 0;
}