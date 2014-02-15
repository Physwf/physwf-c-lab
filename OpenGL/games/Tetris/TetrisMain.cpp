#include "TetrisMain.h"
#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + bytes)

enum Buffer_IDs {VERTEX,INDEX,NumBuffers};
GLuint buffers[NumBuffers];
enum Attrib_IDs {vPosition};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_QUADS,0,4);
	glFlush();
}

void init()
{
	GLfloat vertices[] = 
	{
		10.0,10.0,
		110.0,10.0,
		110.0,110.0,
		10.0,110.0
	};
	glGenBuffers(NumBuffers,buffers);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[VERTEX]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char* vSrc = t_read("tetris.vert");
	const char* fSrc = t_read("tetris.frag");
	
	glShaderSource(vShader,1,&vSrc,0);
	glShaderSource(fShader,1,&fSrc,0);
	
	glCompileShader(vShader);
	glCompileShader(fShader);
	
	GLint vStatus;
	GLint fStatus;
	glGetShaderiv(vShader,GL_COMPILE_STATUS,&vStatus);
	glGetShaderiv(fShader,GL_COMPILE_STATUS,&fStatus);
	if(!vStatus)
	{
		GLint infoLen;
		char* infoLog;
		glGetShaderiv(vShader,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*)malloc(infoLen);
		glGetShaderInfoLog(vShader,infoLen,NULL,infoLog);
		printf("vertex shader compile error:%s\n",infoLog);
		free(infoLog);
	}
	if(!fStatus)
	{
		GLint infoLen;
		char* infoLog;
		glGetShaderiv(fShader,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*) malloc(infoLen);
		glGetShaderInfoLog(fShader,infoLen,NULL,infoLog);
		printf("fragment shader compile error:%s\n",infoLog);
		free(infoLog);
	}
	if(!vStatus || !fStatus) return;
	
	GLuint program = glCreateProgram();
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
	glLinkProgram(program);
	
	GLint pStatus;
	glGetProgramiv(program,GL_LINK_STATUS,&pStatus);
	if(!pStatus)
	{
		GLint infoLen;
		char* infoLog;
		glGetProgramiv(program,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*) malloc(infoLen);
		glGetProgramInfoLog(program,infoLen,NULL,infoLog);
		printf("program link error:%s\n",infoLog);
		free(infoLog);
		return;
	}
	glUseProgram(program);
}

void update()
{
	
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(0,0);
	glutInitContextVersion(3,0);
	// glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Tetris");
	if(glewInit() != GLEW_OK)
	{
		printf("Glew Init Error!");
		return 1;
	}
	init();
	glClearColor(0.0,0.0,0.0,1.0);
	glutDisplayFunc(&display);
	glutMainLoop();
}