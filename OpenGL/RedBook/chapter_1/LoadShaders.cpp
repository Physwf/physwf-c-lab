#include "LoadShaders.h"
#include "utils.h"

GLuint LoadShaders(ShaderInfo* shaders)
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char ** vSrc;
	const char ** fSrc;
	const GLint vLen = t_read(shaders[0].filename,&vSrc);
	const GLint fLen = t_read(shaders[1].filename,&fSrc);
	glShaderSource(vShader,sizeof(**vSrc),vSrc,&vLen);
	glShaderSource(fShader,sizeof(**fSrc),fSrc,&fLen);
	glCompileShader(vShader);
	glCompileShader(fShader);
	GLsizei vInfoLen;
	GLsizei fInfoLen;
	char* vInfoLog = NULL;
	char* fInfoLog = NULL;
	glGetShaderInfoLog(vShader,100,&vInfoLen,vInfoLog);
	glGetShaderInfoLog(fShader,100,&fInfoLen,fInfoLog);
	printf("Compile Vertex Shader:%s",vInfoLog);
	printf("Compile Fragment Shader:%s",fInfoLog);
	GLuint program = glCreateProgram();
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
	glLinkProgram(program);
	// if(glGetProgramiv(program,GL_LINK_STATUS,NULL) == GL_TRUE)
	// {
		
	// }
	return program;
	return 0;
}

