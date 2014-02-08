#include "LoadShaders.h"

enum VAO_IDs { Triangles,NumVAOs};
enum Buffer_IDs { ArrayBuffer,NumBuffers };
enum Attrib_IDs { vPosition=0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices =6;

void init()
{
	printf("init start\n");
#if defined(WIN)
	glGenVertexArrays(NumVAOs,VAOs);
    glBindVertexArray(VAOs[Triangles]);
#endif
#if defined(MAC)
    glGenVertexArraysAPPLE(NumVAOs,VAOs);
    glBindVertexArrayAPPLE(VAOs[Triangles]);
#endif
	
	
	GLfloat vertices[NumVertices][2] = {
		{-0.90,-0.90},
		{0.85,-0.90},
		{-0.90,0.85},
		{0.90,0.90},
		{0.90,-0.85},
		{-0.85,0.90}
	};
	
	glGenBuffers(NumBuffers,Buffers);
	glBindBuffer(GL_ARRAY_BUFFER,Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"./triangles.vert"},
		{GL_FRAGMENT_SHADER,"./triangles.frag"},
		{GL_NONE,NULL}
	};
	printf("init 2\n");
	GLuint program = LoadShaders(shaders);
	if(program == 0) return;
	glUseProgram(program);
	
	glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
#if defined(WIN)
	glBindVertexArray(VAOs[Triangles]);
#endif
#if defined(MAC)
    glBindVertexArrayAPPLE(VAOs[Triangles]);
#endif
	glDrawArrays(GL_TRIANGLES,0,NumVertices);
	
	glFlush();
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
#if defined(WIN)
	GLenum err = glewInit();
	if(err!=GLEW_OK)
	{
		printf("Glew Init Error!");
		return 1;
	}
#endif
	init();
	glutDisplayFunc(&display);
	glutMainLoop();
}

