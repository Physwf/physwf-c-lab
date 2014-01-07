#include "geometry.h"
#include "draw.h"

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// glRectf(-0.5,-0.5,0.5,0.5);
	// glRectf(100,100,200,200);
	// drawPoints();
	// drawLines();
	// drawLineStrip();
	// drawLineLoop();
	// drawTriangles();
	// drawTriangleStrip();
	// drawTriangleFan();
	// drawQuads();
	// drawQuadStrip();
	drawPolygon();
	glFlush();
}

void onResize(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
}

int main(int argc,char *argv[])
{
	//init window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(STAGE_WIDTH,STAGE_HEIGHT);
	glutCreateWindow("Geometry!");
	//init glew
	GLenum err = glewInit();
	if(err!=GLEW_OK)
	{
		printf("Glew Init Error!");
		return 1;
	}
	//set clear color
	glClearColor(0.0,0.0,0.0,1.0);
	glutReshapeFunc(&onResize);
	glutDisplayFunc(&draw);
	glutMainLoop();
	return 0;
}
