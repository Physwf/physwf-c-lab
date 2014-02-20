#include "TetrisMain.h"
#include "TetrisData.h"

#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + bytes)
#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 300
#define SQUARE_WIDTH (WINDOW_WIDTH/NUM_X)
#define SQUARE_HEIGHT (WINDOW_HEIGHT/NUM_Y)

enum Buffer_IDs {VERTEX,INDEX,NumBuffers};
GLuint buffers[NumBuffers];
enum Attrib_IDs {vPosition};

GLfloat *vertices;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_QUADS,0,4*num_squares);
	// glDrawArrays(GL_LINE_STRIP,0,4*num_squares);
	glFlush();
}

void init()
{
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
	
	GLint mvpLoc = glGetUniformLocation(program,"mvp");
	GLfloat mvp[] = 
	{
		2.0/WINDOW_WIDTH,		0.0,		0.0, 0.0,
		0.0,		-2.0/WINDOW_HEIGHT,	0.0, 0.0,
		0.0,		0.0,				1.0, 0.0,
		-1.0,		1.0,				0.0, 1.0
	};
	printf("mvp:%f\n",mvp[0]);
	printf("mvp:%f\n",mvp[5]);
	glUniformMatrix4fv(mvpLoc,1,GL_FALSE,mvp);
}

void post()
{
	vertices = (GLfloat*) calloc(num_squares*8,sizeof(GLfloat));
	for(int i=0;i < num_squares;i++)
	{
		// printf("%d:%d\n",i,squares[i].x);
		// printf("%d:%d\n",i,squares[i].y);
	}
	for(int i=0;i < num_squares;i++)
	{
		vertices[i*8] = squares[i].x * (int)SQUARE_WIDTH;
		vertices[i*8+1] = squares[i].y * (int)SQUARE_HEIGHT;
		vertices[i*8+2] = squares[i].x * (int)SQUARE_WIDTH + (int)SQUARE_WIDTH;
		vertices[i*8+3] = squares[i].y * (int)SQUARE_HEIGHT;
		vertices[i*8+4] = squares[i].x * (int)SQUARE_WIDTH + (int)SQUARE_WIDTH;
		vertices[i*8+5] = squares[i].y * (int)SQUARE_HEIGHT + (int)SQUARE_HEIGHT;
		vertices[i*8+6] = squares[i].x * (int)SQUARE_WIDTH;
		vertices[i*8+7] = squares[i].y * (int)SQUARE_HEIGHT + (int)SQUARE_HEIGHT;
	}
	for(int i=0;i < num_squares;i++)
	{
		// printf("%d:%f\n",i,vertices[i*8]);
		// printf("%d:%f\n",i,vertices[i*8+1]);
		// printf("%d:%f\n",i,vertices[i*8+2]);
		// printf("%d:%f\n",i,vertices[i*8+3]);
		// printf("%d:%f\n",i,vertices[i*8+4]);
		// printf("%d:%f\n",i,vertices[i*8+5]);
		// printf("%d:%f\n",i,vertices[i*8+6]);
		// printf("%d:%f\n",i,vertices[i*8+7]);
	}
	glBufferData(GL_ARRAY_BUFFER,num_squares*8*sizeof(GLfloat),vertices,GL_DYNAMIC_DRAW);
	glutPostRedisplay();
	free(vertices);
}

void update(int value)
{
	if(loop())
		;
	post();
	glutTimerFunc(500,update,0);
}

void onKeyBoardEvent(int keycode,int x,int y)
{
	onKeyDown(keycode);
	post();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(200,300);
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
	initData();
	glClearColor(0.0,0.0,0.0,1.0);
	glutDisplayFunc(&display);
	glutSpecialFunc(onKeyBoardEvent);
	glutTimerFunc(500,update,0);
	glutMainLoop();
}