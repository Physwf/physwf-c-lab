#include <libpng/png.h>
#include <stdio.h>
#include <stdlib.h>

//#pragma comment (lib,"")

int main(int argc,char** argv)
{
	FILE *f = fopen("./Data/Popo.png","rb");
	
	if(f == NULL)
	{
		exit(-1);
	}
	
	fseek(f,0,SEEK_END);
	int fSize = ftell(f);
	rewind(f);
	unsigned char* buffer = (unsigned char*)malloc(fSize);
	fread(buffer,1,fSize,f);
	int is_png = !png_sig_cmp(buffer,0,8);
	if(!is_png)
	{
		printf("NOT PNG!\n");
		exit(-1);
	}
	
	png_structp png_ptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL, NULL, NULL);
	if(!png_ptr)
	{
		printf("create png struct failed!\n");
		exit(-1);
	}
	png_infop info_ptr;
	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		printf("create info struct failed!\n");
		png_destroy_read_struct(&png_ptr,NULL,NULL);
		exit(-1);
	}
	png_infop end_info;
	end_info = png_create_info_struct(png_ptr);
	if(!end_info)
	{
		printf("create end info failed!\n");
		png_destroy_read_struct(&png_ptr,NULL,NULL);
		exit(-1);
	}
	png_init_io(png_ptr,f);
	png_set_sig_bytes(png_ptr,8);
	
	return 0;
}