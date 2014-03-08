attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 v_texCoord;

uniform mat4 u_mvp;

void main()
{
	
	gl_Position = u_mvp * a_position;
	v_texCoord = a_texCoord;
}
