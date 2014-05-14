#include "JewelView.h"
#include "JewelData.h"
#include "utils.h"
#include <random.h>
#include <math.h>

#define BUFFER_OFFSET(offset) ((GLfloat*)NULL+offset)
#define STRIDE 4

GLfloat *vertices;
GLushort *indices;

enum VBO_IDs {vertex,index,numVBOs};
enum Attr_IDs {a_postion,a_texCoord};
enum Tex_IDs {s_popo,numTexs};
const float coords_unit_x = GRID_SIZE/468.0;
const float coords_unit_y = GRID_SIZE/234.0;
float tex_coords[NUM_TYPES][4][2] = { 
		{ {coords_unit_x,0},{coords_unit_x+coords_unit_x,0},{coords_unit_x,coords_unit_y},{coords_unit_x+coords_unit_x,coords_unit_y} },//cyan
		{ {2*coords_unit_x,0},{2*coords_unit_x+coords_unit_x,0},{2*coords_unit_x,coords_unit_y},{2*coords_unit_x+coords_unit_x,coords_unit_y} },//red
		{ {3*coords_unit_x,0},{3*coords_unit_x+coords_unit_x,0},{3*coords_unit_x,coords_unit_y},{3*coords_unit_x+coords_unit_x,coords_unit_y} },//purple
		{ {0,coords_unit_y+0},{coords_unit_x,coords_unit_y+0},{0,coords_unit_y+coords_unit_y},{coords_unit_x,coords_unit_y+coords_unit_y} },//yellow
		{ {5*coords_unit_x+0,coords_unit_y+0},{5*coords_unit_x+coords_unit_x,coords_unit_y+0},{5*coords_unit_x+0,coords_unit_y+coords_unit_y},{5*coords_unit_x+coords_unit_x,coords_unit_y+coords_unit_y} },//yellow
	};

float *dragXs;
float *dragYs;

void initView()
{
	glClearColor(0,0,0,1);
	glViewport(0,0,VIEW_W,VIEW_H);
	
	GLuint vbos[numVBOs];
	glGenBuffers(numVBOs,vbos);
	
	glBindBuffer(GL_ARRAY_BUFFER,vbos[vertex]);
	
	int vSize = num_jewels * 16 * sizeof(GLfloat);
	vertices = (GLfloat*)malloc(vSize);
	memset(vertices,0,vSize);
	
	int iSize = num_jewels * 6 * sizeof(GLushort);
	indices = (GLushort*)malloc(iSize);
	memset(indices,0,iSize);

	dragXs = (float*) malloc(num_jewels * sizeof(float));
	dragYs = (float*) malloc(num_jewels * sizeof(float));
	// glBufferData(GL_ARRAY_BUFFER,4*4*sizeof(GLfloat),vertices,GL_STATIC_DRAW);
	memset(dragXs,0,num_jewels * sizeof(float));
	memset(dragYs,0,num_jewels * sizeof(float));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbos[index]);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(GLushort),indices,GL_STATIC_DRAW);
	
	glVertexAttribPointer(a_postion,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),BUFFER_OFFSET(0));
	glEnableVertexAttribArray(a_postion);
	
	glVertexAttribPointer(a_texCoord,2,GL_FLOAT,GL_FALSE,4*sizeof(GLfloat),BUFFER_OFFSET(2));
	glEnableVertexAttribArray(a_texCoord);
	
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char* vSrc = t_read("jewel.vert");
	const char* fSrc = t_read("jewel.frag");
	
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
	
	png_data_t png_data;
	if(!png_read("./Data/Jewels.png",&png_data))
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
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}
/**
	0--1
	|  |
	2--3
**/
void post()
{
	//calculate offsetY
	for(int i=0;i<num_jewels;i++)
	{
		int col = i % 8;
		int row = i / 8;
		float offsetY = *(offsetYs+i);
		float dragX = *(dragXs+i);
		float dragY = *(dragYs+i);
		float paddingX = 2.0;
		float paddingY = 2.0;
		int type = *(jewels+i);
		float ltx = col * GRID_SIZE + dragX+paddingX;
		float lty = row * GRID_SIZE + offsetY + dragY + paddingY;
		// printf("%d\n",i);
		int r = log2((float)type);
		// printf("r:%d,type:%d\n",r,type);
		for(int j=0;j<4;j++)
		{
			*(vertices+i*16+0+j*4) = (ltx + j%2*GRID_SIZE);//x
			*(vertices+i*16+1+j*4) = (lty + j/2*GRID_SIZE);//y
			
			*(vertices+i*16+2+j*4) = tex_coords[r][j][0];//u
			*(vertices+i*16+3+j*4) = tex_coords[r][j][1];//v
			
			
		}
		*(indices+6*i+0) = 4 * i + 0;
		*(indices+6*i+1) = 4 * i + 1;
		*(indices+6*i+2) = 4 * i + 3;
		*(indices+6*i+3) = 4 * i + 3;
		*(indices+6*i+4) = 4 * i + 2;
		*(indices+6*i+5) = 4 * i + 0;
		// printf("%d\n",*(indices+6*i+0));
		// printf("%d\n",*(indices+6*i+1));
		// printf("%d\n",*(indices+6*i+2));
		// printf("%d\n",*(indices+6*i+3));
		// printf("%d\n",*(indices+6*i+4));
		// printf("%d\n",*(indices+6*i+5));
	}
	glBufferData(GL_ARRAY_BUFFER,num_jewels*4*4*sizeof(GLfloat),vertices,GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,num_jewels*6*sizeof(GLushort),indices,GL_DYNAMIC_DRAW);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	post();
	glDrawElements(GL_TRIANGLES,num_jewels*6,GL_UNSIGNED_SHORT,NULL);
	glFlush();
}

int switchPositive;
float positiveX;
float positiveY;
int switchPassive;
void onMouseDown(float x,float y)
{
	int col = x / GRID_SIZE;
	int row = y / GRID_SIZE;
	int index = col + row * NUM_COLS;
	switchPositive = index;
	switchPassive = index;
	positiveX = x;
	positiveY = y;
}

void onMouseMove(float x,float y)
{
	float offsetX = x - positiveX;
	float offsetY = y - positiveY;
	dragXs[switchPositive] = 0;
	dragYs[switchPositive] = 0;
	dragXs[switchPassive] = 0;
	dragYs[switchPassive] = 0;
	if(abs(offsetX) > abs(offsetY) && abs(offsetX)/abs(offsetY) > tan(3.14/6.0))
	{
		if(offsetX >= 0)
			switchPassive = switchPositive + 1;
		else
			switchPassive = switchPositive - 1;
		if(switchPassive / NUM_COLS == switchPositive / NUM_COLS)
		{
			dragXs[switchPositive] = (abs(offsetX) > GRID_SIZE) ? GRID_SIZE*(offsetX/abs(offsetX)) : offsetX;
			dragXs[switchPassive] = -dragXs[switchPositive];
		}
	}
	else if(abs(offsetX) < abs(offsetY) && abs(offsetY)/abs(offsetX) > tan(3.14/6.0))
	{
		if(offsetY >= 0)
			switchPassive = switchPositive + NUM_COLS;
		else
			switchPassive = switchPositive - NUM_COLS;
		if(switchPassive % NUM_COLS == switchPositive % NUM_COLS)
		{
			dragYs[switchPositive] = (abs(offsetY) > GRID_SIZE) ? GRID_SIZE *(offsetY/abs(offsetY)): offsetY;
			dragYs[switchPassive] = -dragYs[switchPositive];
		}
	}
}

void onMouseUp(float x,float y)
{
	printf("switchPositive:%d,switchPassive:%d\n",switchPositive,switchPassive);
	if( switchPositive == switchPassive) return;
	if(!trySwitch(switchPositive,switchPassive))
	{
		memset(dragXs,0,num_jewels * sizeof(float));
		memset(dragYs,0,num_jewels * sizeof(float));
	}
}