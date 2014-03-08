attribute vec4 vPosition;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp  * vPosition;
	//gl_Position = vPosition;  
}