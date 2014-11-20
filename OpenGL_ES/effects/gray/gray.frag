precision mediump float;

varying vec2 v_texCoords;



uniform sampler2D s_tex;


float calcGray1(vec4 color)
{
	vec4 factor = vec4(0.299,0.587,0.114,1.0);
	color = color * factor;
	return color.r+color.g+color.b;
}

float calcGray2(vec4 color)
{
	return (color.r+color.g+color.b)/3.0;
}

void main()
{
	vec4 color = texture2D(s_tex,v_texCoords);
	float gray = calcGray1(color);
	color.r = color.g = color.b = gray;
	gl_FragColor = color;
}

