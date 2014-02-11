#include "TetrisMain.h"
#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + bytes)

enum Buffer_IDs {VERTEX,INDEX,NumBuffers};
GLuint buffers[NumBuffers];
enum Attrib_IDs {vPosition};

void display()
{
	
}

void init()
{
	GLint vertices[];
	glGenBuffers(NumBuffers,buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
	
	glVetexAttribPointer(vPosition,2,GL_INT,GLfalse,0,BUFFER_OFFSET(0));
	glEnableVertexAttribPointer(vPosition);
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(0,0);
	glutInitContextVersion(3,0);
	// glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Triangles");
	if(glewInit() != GLEW_OK)
	{
		printf("Glew Init Error!");
		return 1;
	}
	init();
	glutDisplayFunc(&display);
	glutMainLoop();
}