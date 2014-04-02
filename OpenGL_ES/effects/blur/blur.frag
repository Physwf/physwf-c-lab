precision mediump float;

varying vec2 v_texCoords;



uniform sampler2D s_tex;

uniform int blurX;
uniform int blurY;
uniform int width;
uniform int height;

#define PI 3.1415


float Gaussian(float x,float y,float sigma)
{
	float sigma_pow = sigma*sigma;
	return 0.5 * 1.0/(PI*sigma_pow) * exp(-0.5*float(x*x+y*y)/sigma_pow);
}

float normal(float x, float y, float sigma,float u)
{
	float coefficient = 1.0/(sigma*sqrt(2.0*PI));
	float index = -0.5 * pow(sqrt(x*x+y*y)-u,2.0)/(sigma*sigma);
	return coefficient * exp(index);
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
			//float g = Gaussian(offsetX,offsetY,2.5);
			float g = normal(offsetX,offsetY,2.5,0.0);
			color += texture2D(s_tex,t_coord)*g;
			sum += g;
		}
	}
	color /= sum;
	gl_FragColor = color;
}

