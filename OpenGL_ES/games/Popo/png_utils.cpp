#include <libpng/png.h>

int main(int argc,char** argv)
{
	png_structp png_ptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL, NULL, NULL);
	return 0;
}