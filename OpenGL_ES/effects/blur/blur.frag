precision mediump float;

varying vec2 v_texCoords;



uniform sampler2D s_tex;

uniform int blurX;
uniform int blurY;
uniform int width;
uniform int height;

#define PI 3.1415


float Gaussian(int x,int y,float sigma)
{
	float sigma_pow = sigma*sigma;
	return 0.5 * 1.0/(PI*sigma_pow) * exp(-0.5*float(x*x+y*y)/sigma_pow);
}

float normal(int x, int y)
{
	return 0.0;
}

void main()
{
	vec4 color;
	float sum=0.0;
	for(int i=-blurX;i<=blurX;i++)
	{
		for(int j=-blurY;j<=blurY;j++)
		{
			float offsetX = float(i)/float(width);
			float offsetY = float(j)/float(height);
			vec2 t_coord = v_texCoords + vec2(offsetX,offsetY);
			float g = Gaussian(i,j,1.5);
			color += texture2D(s_tex,t_coord)*g;
			sum += g;
		}
	}
	color /= sum;
	gl_FragColor = color;
}

