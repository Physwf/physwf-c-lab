#version 330 core
in vec4 vPosition;

void main()
{
	mat4 mvp = mat4
	(
		0.0039,		0,		0,0,
		0,		-0.0039,		0,0,
		0,		0,		1,0,
		-1,		1,		0,1
	);
	gl_Position = mvp * vPosition;
} 