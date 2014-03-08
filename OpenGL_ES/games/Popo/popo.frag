precision mediump float;

varying vec2 v_texCoord;

uniform mat4 u_mvp;

uniform sampler2D s_popo;

void main()
{
	gl_FragColor = texture2D(s_popo,v_texCoord);
	//gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}
