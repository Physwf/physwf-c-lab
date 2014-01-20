#include "LoadShaders.h"
#include "utils.h"

GLuint LoadShaders(ShaderInfo* shaders)
{
	printf("load shaders start\n");
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char ** vSrc;
	const char ** fSrc;
	const GLint vLen = t_read(shaders[0].filename,&vSrc);
	const GLint fLen = t_read(shaders[1].filename,&fSrc);
    if (vLen < 0 || fLen < 0) {
        printf("load shader failed!\n");
        return 0;
    }
	printf("read complete\n");
	glShaderSource(vShader,sizeof(**vSrc),vSrc,&vLen);
	glShaderSource(fShader,sizeof(**fSrc),fSrc,&fLen);
	printf("start compile\n");
	glCompileShader(vShader);
	glCompileShader(fShader);
    
	GLint vStatus=1;
	GLint fStatus=1;
	glGetShaderiv(vShader,GL_COMPILE_STATUS,&vStatus);
	glGetShaderiv(fShader,GL_COMPILE_STATUS,&fStatus);
	printf("vStatus:%d\n",vStatus);
	printf("fStatus:%d\n",fStatus);
    
    GLsizei vInfoLen;
	GLsizei fInfoLen;
    char vInfoLog[100];
	char fInfoLog[100];
    glGetShaderInfoLog(vShader,100,&vInfoLen,vInfoLog);
	glGetShaderInfoLog(fShader,100,&fInfoLen,fInfoLog);
    printf("Compile Vertex Shader:%s\n",vInfoLog);
	printf("Compile Fragment Shader:%s\n",fInfoLog);
    
	if(vStatus == GL_FALSE) {
        printf("vertex shader compile failed!\n");
        return 0;
    }
	if(fStatus == GL_FALSE) {
        printf("fragment shader compile failed!\n");
        return 0;
    }
	printf("compile complete\n");

	printf("start create program\n");
	GLuint program = glCreateProgram();
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
	printf("attach shader complete\n");
	glLinkProgram(program);
	printf("link program complete\n");
	GLint param;
	glGetProgramiv(program,GL_LINK_STATUS,&param);
	
	printf("glGetProgramiv complete\n");
	if(param == GL_TRUE)
	{
		printf("Compile success!");
		return program;
	}
	else
	{
		printf("Compile failed!");
		return 0;
	}
	
}

