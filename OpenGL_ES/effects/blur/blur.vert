attribute vec4 a_position;
attribute vec2 a_texCoords;
varying vec2 v_texCoords;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * a_position;
	v_texCoords = a_texCoords;
}