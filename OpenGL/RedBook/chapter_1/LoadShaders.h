#include "vgl.h"

typedef struct {
	GLenum type;
	const char* fileName;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo shaders);