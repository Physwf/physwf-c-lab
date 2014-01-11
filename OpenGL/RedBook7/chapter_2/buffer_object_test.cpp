#include "geometry.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *) NULL + (bytes))
#define VERTICES 0
#define INDICES 1
#define NUM_BUFFERS 2

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	
	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,BUFFER_OFFSET(0));
	glFlush();
}

void onResize(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
}

void initBuffers()
{
	GLuint buffers[NUM_BUFFERS];

	GLfloat vertices[] =
	{
		100.0,100.0,
		100.0,200.0,
		200.0,200.0,
		200.0,100.0,
	};

	GLubyte indices[] =
	{
		0,1,2,3
	};
	glGenBuffers(NUM_BUFFERS,buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexPointer(2,GL_FLOAT,0,BUFFER_OFFSET(0));
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
}

void initBuffersUseStride()
{
	GLuint buffers[NUM_BUFFERS];

	GLfloat vertices[] =
	{
		100.0,100.0,1.0,0.0,0.0,
		100.0,200.0,1.0,1.0,0.0,
		200.0,200.0,1.0,0.0,1.0,
		200.0,100.0,0.0,1.0,0.0
	};

	GLubyte indices[] =
	{
		0,1,2,3
	};
	glGenBuffers(NUM_BUFFERS,buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexPointer(2,GL_FLOAT,5*sizeof(GLfloat),BUFFER_OFFSET(0));
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3,GL_FLOAT,5*sizeof(GLfloat),BUFFER_OFFSET(2*sizeof(GLfloat)));
	glEnableClientState(GL_COLOR_ARRAY);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
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
	// initBuffers();
	initBuffersUseStride();
	glutReshapeFunc(&onResize);
	glutDisplayFunc(&draw);
	glutMainLoop();
	return 0;
}