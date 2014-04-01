precision mediump float;

varying vec2 v_texCoords;



uniform sampler2D s_tex;

void main()
{
	vec4 color = texture2D(s_tex,v_texCoords);
	vec4 factor = vec4(0.299,0.587,0.114,1.0);
	color = color * factor;
	float gray = color.r+color.g+color.b;
	color.r = color.g = color.b = gray;
	gl_FragColor = color;
}