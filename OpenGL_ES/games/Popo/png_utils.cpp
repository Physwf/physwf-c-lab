#include <libpng/png.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER 8
//#pragma comment (lib,"")
int read_chunk_callback(png_structp ptr,png_unknown_chunkp chunk)
{
	return 1;
}

void read_row_callback(png_structp ptr,png_uint_32 row,int pass)
{
	
}

int main(int argc,char** argv)
{
	FILE *f = fopen("./Data/green.png","rb");
	
	if(f == NULL)
	{
		// exit(-1);
	}
	
	fseek(f,0,SEEK_END);
	int fSize = ftell(f);
	rewind(f);
	unsigned char* buffer = (unsigned char*)malloc(fSize);
	fread(buffer,1,fSize,f);
	int is_png = !png_sig_cmp(buffer,0,HEADER);
	if(!is_png)
	{
		printf("NOT PNG!\n");
		// exit(-1);
	}
	
	png_structp png_ptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL, NULL, NULL);
	if(!png_ptr)
	{
		printf("create png struct failed!\n");
		// exit(-1);
	}
	png_infop info_ptr;
	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		printf("create info struct failed!\n");
		png_destroy_read_struct(&png_ptr,NULL,NULL);
		// exit(-1);
	}
	png_infop end_info;
	end_info = png_create_info_struct(png_ptr);
	if(!end_info)
	{
		printf("create end info failed!\n");
		png_destroy_read_struct(&png_ptr,NULL,NULL);
		// exit(-1);
	}
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,&end_info);
		return (-1);
	}
	png_init_io(png_ptr,f);
	png_set_sig_bytes(png_ptr,HEADER);
	// png_voidp user_chunk_ptr = png_get_user_chunk_ptr(png_ptr);
	// png_set_read_user_chunk_fn(png_ptr,user_chunk_ptr,read_chunk_callback);
	// png_set_keep_unknown_chunks(png_ptr,PNG_HANDLE_CHUNK_NEVER,NULL,0);
	
	//png_set_read_status_fn(png_ptr,read_row_callback);
	//low lever read
	png_read_info(png_ptr,info_ptr);
	png_uint_32 width;
	png_uint_32 height;
	int bit_depth;
	int color_type;
	// png_get_IHDR(png_ptr,info_ptr,&width,&height,&bit_depth,&color_type,NULL,NULL,NULL);
	// printf("width:%d,height:%d,bit_depth:%d,color_type:%d",width,height,bit_depth,color_type);
	getchar();
	return 0;
}