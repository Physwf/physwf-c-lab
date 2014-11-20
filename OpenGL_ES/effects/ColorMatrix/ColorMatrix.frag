precision mediump float;

varying vec2 v_texCoords;

uniform sampler2D s_tex;
uniform float cm[20];

vec4 transform(vec4 i)
{
	vec4 o;
	o.r   = (cm[0]  * i.r) + (cm[1]  * i.g) + (cm[2]  * i.b) + (cm[3]  * i.a) + cm[4];
	o.g = (cm[5]  * i.r) + (cm[6]  * i.g) + (cm[7]  * i.b) + (cm[8]  * i.a) + cm[9];
	o.b  = (cm[10] * i.r) + (cm[11] * i.g) + (cm[12] * i.b) + (cm[13] * i.a) + cm[14];
	o.a = (cm[15] * i.r) + (cm[16] * i.g) + (cm[17] * i.b) + (cm[18] * i.a) + cm[19];
	return o;
}

void main()
{
	vec4 color = texture2D(s_tex,v_texCoords);
	gl_FragColor = transform(color);
}

