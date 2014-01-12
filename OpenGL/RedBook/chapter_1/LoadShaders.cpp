#include "LoadShaders.h"
#include "utils.h"

GLuint LoadShaders(ShaderInfo shaders)
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	char ** src = t_read("triangles.vert");
	glShaderSource(vShader,sizeof(**src));
}

