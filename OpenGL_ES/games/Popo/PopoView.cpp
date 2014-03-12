#include "PopoView.h"
#include "PopoData.h"
#include "utils.h"
#include <math.h>

#define BUFFER_OFFSET(offset) ((GLfloat*)NULL+offset)
#define STRIDE 4

GLfloat *vertices;
	// {
		// 0,0,0,0,	
		// 128,0,	1,0,
		// 128,128,1,1,
		// 0,128,0,1
	// };
GLushort *indices;
// {0,1,2,2,3,0};

enum VBO_IDs {vertex,index,numVBOs};
enum Attr_IDs {a_postion,a_texCoord};
enum Tex_IDs {s_popo,numTexs};
int num_squares;

void initView()
{
	glClearColor(0,0,0,1);
	glViewport(0,0,VIEW_W,VIEW_H);
	
	GLuint vbos[numVBOs];
	glGenBuffers(numVBOs,vbos);
	
	glBindBuffer(GL_ARRAY_BUFFER,vbos[vertex]);
	
	int vSize = num_slots * 16 * sizeof(GLfloat);
	vertices = (GLfloat*)malloc(vSize);
	memset(vertices,0,vSize);
	
	int iSize = num_slots * 6 * sizeof(GLushort);
	indices = (GLushort*)malloc(iSize);
	memset(indices,0,iSize);
	
	// glBufferData(GL_ARRAY_BUFFER,4*4*sizeof(GLfloat),vertices,GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbos[index]);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(GLushort),indices,GL_STATIC_DRAW);
	
	glVertexAttribPointer(a_postion,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),BUFFER_OFFSET(0));
	glEnableVertexAttribArray(a_postion);
	
	glVertexAttribPointer(a_texCoord,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),BUFFER_OFFSET(2));
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
	
	glBindAttribLocation(program,a_postion,"a_position");
	glBindAttribLocation(program,a_texCoord,"a_texCoord");
	
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
	
	glUseProgram(program);
	
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
	glBindTexture(GL_TEXTURE_2D,textures[s_popo]);
	
	// BITMAP bm;
	// CImage img;
	// HRESULT hr = img.Load("./Data/Popo.png");
	// if(!SUCCEEDED(hr))
	// {
		// printf("load image error!\n");
	// }
	// HBITMAP hbmp = img;
	// GetObject(hbmp, sizeof(bm), &bm);
	
	png_data_t png_data;
	if(!png_read("./Data/Popo.png",&png_data))
	{
		glTexImage2D(GL_TEXTURE_2D,0,
					GL_RGBA,
					png_data.width,png_data.height,0,
					GL_RGBA,GL_UNSIGNED_BYTE,png_data.data);
		free(png_data.data);
	}
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_PACK_ALIGNMENT, 1); 
	
	GLint sampleLoc = glGetUniformLocation(program,"s_texture");
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D,textures[s_popo]);
	glUniform1i(sampleLoc,0);
}

const float EVEN_OFFSET_X = RADIUS/2;
const float ODD_OFFSET_X = RADIUS;
const float OFFSET_Y = RADIUS/2;

const float DIST_ROW = sqrt(3.0) * RADIUS;
const float DIST_COLLUM = RADIUS;

void setVertex(popo_ptr popo,GLfloat* vertex,int index)
{
	int orginX,orginY;
	orginX = ((popo->row%2 == 0)?EVEN_OFFSET_X:ODD_OFFSET_X) + popo->collum * DIST_COLLUM;
	orginY = OFFSET_Y + popo->row * DIST_ROW;
	*vertex = orginX + (index%2-0.5) * RADIUS;
	*(vertex+1) = orginY + (index/2-0.5) * RADIUS/2;
	
	*(vertex+2) = (index%2)*0.5;//to do
	*(vertex+3) = (index/2)*0.5;
}

void scan()
{
	int offset;
	num_squares = 0;
	for(int i=0;i<num_slots;i++)
	{
		popo_ptr popo = popos+i;
		offset = i*16*sizeof(GLfloat);
		if(popo->type != POPO_TYPE_NONE)
		{
			
			for(int j=0;j<4;j++)
			{
				GLfloat* vertex = vertices + offset;
				setVertex(popo,vertex+i*STRIDE,i);
			}
			for(int j=0;j<6;j++)
			{
				unsigned short index_offset = num_squares*4;
				indices[0+index_offset] = 0+index_offset;
				indices[1+index_offset] = 1+index_offset;
				indices[2+index_offset] = 2+index_offset;
				indices[3+index_offset] = 2+index_offset;
				indices[4+index_offset] = 3+index_offset;
				indices[5+index_offset] = 0+index_offset;
			}
			num_squares++;
		}
	}
	
	glBufferData(GL_ARRAY_BUFFER,num_squares*4*4*sizeof(GLfloat),vertices,GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,num_squares*6*sizeof(GLushort),indices,GL_DYNAMIC_DRAW);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	scan();
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);
	glFlush();
}