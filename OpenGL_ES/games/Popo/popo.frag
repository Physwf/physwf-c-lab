precision medium float;

varying vec2 v_texCoord;

uniform sample2D s_texture;

void main()
{
	gl_FragColor = texture2D(s_texture,v_texCoord);
}
