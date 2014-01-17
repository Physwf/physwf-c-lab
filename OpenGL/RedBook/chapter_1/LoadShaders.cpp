#include "LoadShaders.h"
#include "utils.h"

GLuint LoadShaders(ShaderInfo* shaders)
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	char ** vSrc = t_read("triangles.vert");
	char ** fSrc = t_read("triangles.frag");
	glShaderSource(vShader,sizeof(**src));
	glShaderSource(fShader,sizeof(**src));
	glCompileShader(vShader);
	glCompileShader(fShader);
	GLsizei vInfoLen;
	GLsizei fInfoLen;
	char* vInfoLog = NULL;
	char* fInfoLog = NULL
	glGetShaderInfoLog(vShader,100,&vInfoLen,vInfoLog)
	glGetShaderInfoLog(fShader,100,&fInfoLen,fInfoLog)
	printf("Compile Vertex Shader:%s",vInfoLog);
	printf("Compile Fragment Shader:%s",fInfoLog);
	GLuint program = glCreateProgram();
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
	glLinkProgram(program);
	if(glGetProgramiv(GL_LINK_STATUS) == GL_TRUE)
	{
		return program;
	}
	return 0;
}

