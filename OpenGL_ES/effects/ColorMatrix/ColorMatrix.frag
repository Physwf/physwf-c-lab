precision mediump float;

varying vec2 v_texCoords;

uniform sampler2D s_tex;
uniform float cm[20];

vec4 transform(vec4 input)
{
	vec4 color;
	color.r   = (cm[0]  * input.r) + (cm[1]  * input.g) + (cm[2]  * input.b) + (cm[3]  * input.a) + cm[4];
	color.g = (cm[5]  * input.r) + (cm[6]  * input.g) + (cm[7]  * input.b) + (cm[8]  * input.a) + cm[9];
	color.b  = (cm[10] * input.r) + (cm[11] * input.g) + (cm[12] * input.b) + (cm[13] * input.a) + cm[14];
	color.a = (cm[15] * input.r) + (cm[16] * input.g) + (cm[17] * input.b) + (cm[18] * input.a) + cm[19];
	return color;
}

void main()
{
	vec4 color = texture2D(s_tex,v_texCoords);
	gl_FragColor = transform(color);
}

