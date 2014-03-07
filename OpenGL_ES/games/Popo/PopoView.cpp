#include "PopoView.h"
#include "utils.h"
#include <atlstr.h>
#include <atlimage.h>

#define BUFFER_OFFSET(offset) ((GLbyte*)NULL+offset)
GLfloat *vertices;
GLshort *indices;

enum VBO_IDs {vertex,index,numVBOs};
enum Attr_IDs {a_postion,a_texCoord};
enum Tex_IDs {s_all,numTexs};

void initView()
{
	glClearColor(0,0,0,1);
	glViewport(0,0,VIEW_W,VIEW_H);
	
	GLuint vbos[numVBOs];
	glGenBuffers(numVBOs,vbos);
	glBindBuffer(GL_ARRAY_BUFFER,vbos[vertex]);
	// vertices = (GLfloat*)calloc(4*4,sizeof(GLfloat));
	GLfloat square[] = 
	{
		0,0,0,0,
		100,0,1,0,
		100,100,1,1,
		0,100,0,1
	};
	glBufferData(GL_ARRAY_BUFFER,4*4*sizeof(GLfloat),square,GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER,vbos[index]);
	GLshort square_indices[] = {0,1,2,2,3,0};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(GLshort),square_indices,GL_STATIC_DRAW);
	
	indices = square_indices;
	
	glVertexAttribPointer(a_postion,2,GL_FLOAT,false,4,BUFFER_OFFSET(0));
	glEnableVertexAttribArray(a_postion);
	
	glVertexAttribPointer(a_texCoord,2,GL_FLOAT,false,4,BUFFER_OFFSET(2));
	glEnableVertexAttribArray(a_texCoord);
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char* vSrc = t_read("popo.vert");
	const char* fSrc = t_read("popo.frag");
	
	glShaderSource(vShader,1,&vSrc,0);
	glShaderSource(fShader,1,&fSrc,0);
	
	glCompileShader(vShader);
	glCompileShader(fShader);
	
	GLint vStatus,fStatus;
	glGetShaderiv(vShader,GL_COMPILE_STATUS,&vStatus);
	glGetShaderiv(fShader,GL_COMPILE_STATUS,&fStatus);
	
	if(!vStatus)
	{
		GLint infoLen;
		char* infoLog;
		glGetShaderiv(vShader,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*) malloc(infoLen);
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
		printf("program link error:%s\n");
		free(infoLog);
	}
	
	
	GLint mvpLoc = glGetUniformLocation(program,"u_mvp");
	GLfloat mvp[] =
	{
		2.0/VIEW_W,		0.0,		0.0, 0.0,
		0.0,		-2.0/VIEW_H,	0.0, 0.0,
		0.0,		0.0,				1.0, 0.0,
		-1.0,		1.0,				0.0, 1.0
	};
	glUniformMatrix4fv(mvpLoc,1,GL_FALSE,mvp);
	
	GLuint textures[numTexs];
	glGenTextures(numTexs,textures);
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	
	BITMAP bm;
	CImage img;
	HRESULT hr = img.Load("./Data/Popo.png");
	if(!SUCCEEDED(hr))
	{
		printf("load image error!\n");
	}
	HBITMAP hbmp = img;
	
	glTexImage2D(GL_TEXTURE_2D,0,
				GL_RGBA,
				bm.bmWidth,bm.bmHeight,0,
				GL_RGBA,GL_UNSIGNED_BYTE,bm.bmBits);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	
	GLint sampleLoc = glGetUniformLocation(program,"s_texture");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glUniform1i(sampleLoc,0);
	
	
	glUseProgram(program);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,indices);
	glFlush();
}