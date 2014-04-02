#include "blur.h"

enum VBO_IDs {vertex,index,numVBOs};
enum Attr_IDs {a_position,a_texCoords};
enum Tex_IDs {s_tex,numTexs};

GLfloat vertices[] = {  0,0,	0,0,
						256,0,	1,0,
						256,256,1,1,
						0,256,	0,1 };
GLushort indices[] = {0,1,2,2,3,0};

void initGray()
{
	//basic
	glClearColor(0,0,0,1);
	glViewport(0,0,VIEW_W,VIEW_H);
	
	//vbos
	GLuint vbos[numVBOs];
	glGenBuffers(numVBOs,vbos);
	
	glBindBuffer(GL_ARRAY_BUFFER,vbos[vertex]);
	glBufferData(GL_ARRAY_BUFFER,4*4*sizeof(GLfloat),vertices,GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbos[index]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(GLushort),indices,GL_STATIC_DRAW);
	
	glVertexAttribPointer(a_position,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),(GLfloat*)NULL+0);
	glEnableVertexAttribArray(a_position);
	
	glVertexAttribPointer(a_texCoords,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),(GLfloat*)NULL+2);
	glEnableVertexAttribArray(a_texCoords);
	
	//shaders
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char *vSrc = t_read("./blur.vert");
	const char *fSrc = t_read("./blur.frag");
	
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
		char *infoLog;
		glGetShaderiv(vShader,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*) malloc(infoLen);
		glGetShaderInfoLog(vShader,infoLen,NULL,infoLog);
		printf("vertex shader compile:%s\n",infoLog);
		free(infoLog);
	}
	if(!fStatus)
	{
		GLint infoLen;
		char *infoLog;
		glGetShaderiv(fShader,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*) malloc(infoLen);
		glGetShaderInfoLog(fShader,infoLen,NULL,infoLog);
		printf("fragment shader compile:%s\n",infoLog);
		free(infoLog);
	}
	//program
	GLuint program = glCreateProgram();
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
	
	glBindAttribLocation(program,a_position,"a_position");
	glBindAttribLocation(program,a_texCoords,"a_texCoords");
	
	glLinkProgram(program);
	
	GLint pStatus;
	glGetProgramiv(program,GL_LINK_STATUS,&pStatus);
	if(!pStatus)
	{
		GLint infoLen;
		char *infoLog;
		glGetProgramiv(program,GL_INFO_LOG_LENGTH,&infoLen);
		infoLog = (char*)malloc(infoLen);
		glGetProgramInfoLog(program,infoLen,NULL,infoLog);
		printf("program link error:%s\n",infoLog);
		free(infoLog);
	}
	
	glUseProgram(program);
	
	//uniform and texture
	GLint mvpLoc = glGetUniformLocation(program,"u_mvp");
	GLfloat mvp[] = 
	{
		2.0/VIEW_W,		0.0,		0.0, 0.0,
		0.0,		-2.0/VIEW_H,	0.0, 0.0,
		0.0,		0.0,				1.0, 0.0,
		-1.0,		1.0,				0.0, 1.0
	};
	glUniformMatrix4fv(mvpLoc,1,GL_FALSE,mvp);
	
	GLint blurXLoc = glGetUniformLocation(program,"blurX");
	GLint blurYLoc = glGetUniformLocation(program,"blurY");
	glUniform1i(blurXLoc,4);
	glUniform1i(blurYLoc,4);
	
	GLuint textures[numTexs];
	glGenTextures(numTexs,textures);
	glBindTexture(GL_TEXTURE_2D,textures[s_tex]);
	
	png_data_t tex_data;
	if(!png_read("./blur.png",&tex_data))
	{
		glTexImage2D(GL_TEXTURE_2D,0,
					GL_RGBA,
					tex_data.width,tex_data.height,0,
					GL_RGBA,GL_UNSIGNED_BYTE,tex_data.data);
		free(tex_data.data);
	}
	
	GLint wLoc = glGetUniformLocation(program,"width");
	GLint hLoc = glGetUniformLocation(program,"height");
	glUniform1i(wLoc,tex_data.width);
	glUniform1i(hLoc,tex_data.height);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_PACK_ALIGNMENT,1);

	GLint sampleLoc = glGetUniformLocation(program,"s_tex");
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D,textures[s_tex]);
	glUniform1i(sampleLoc,0);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
}

void update(int eclipse)
{

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);
}