precision mediump float;

varying vec2 v_texCoords;



uniform sampler2D s_tex;

uniform int blurX;
uniform int blurY;
uniform int width;
uniform int height;

const int radial = 150;

#define PI 3.1415


float Gaussian(float x,float y,float sigma)
{
	float sigma_pow = sigma*sigma;
	return 0.5 * 1.0/(PI*sigma_pow) * exp(-0.5*float(x*x+y*y)/sigma_pow);
}

float Gaussian(float r,float sigma)
{
	float sigma_pow = sigma*sigma;
	return 0.5 * 1.0/(PI*sigma_pow) * exp(-0.5*float(r*r)/sigma_pow);
}

float normal(float x, float y, float sigma,float u)
{
	float coefficient = 1.0/(sigma*sqrt(2.0*PI));
	float index = -0.5 * pow(sqrt(x*x+y*y)-u,2.0)/(sigma*sigma);
	return coefficient * exp(index);
}

vec4 blur()
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
			float g = Gaussian(offsetX,offsetY,2.5);
			//float g = normal(offsetX,offsetY,2.5,0.0);
			color += texture2D(s_tex,t_coord)*g;
			sum += g;
		}
	}
	color /= sum;
	return color;
}

vec4 radialBlur()
{
	vec4 color = texture2D(s_tex,v_texCoords);
	vec4 sum=color;
	vec2 dir = v_texCoords - vec2(0.5,0.5);
	float dist = sqrt(dir.x*dir.x + dir.y*dir.y);
	dir /= dist;
		
	for(int r=-5;r<=5;r++)
	{
		float offsetR = float(r)/float(radial);
		float g = Gaussian(offsetR,1.5);
		vec2 t_coord = v_texCoords + dir * float(r) * g;
		sum += texture2D(s_tex,t_coord) ;
	}
	sum *= 1.0/11.0;
	float t = dist * 2.2;
    t = clamp( t ,0.0,1.0); 
 
    color = mix(color, sum, t );
	return color;
}

void main()
{
	vec4 color = blur();
	//vec4 color = radialBlur();
	gl_FragColor = color;
}

