#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <CxImage\ximage.h>
#include <stdio.h>

#pragma comment(lib, "png.lib")
#pragma comment(lib, "libdcr.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "tiff.lib")
#pragma comment(lib, "jasper.lib")
#pragma comment(lib, "cximage.lib")
#pragma comment(lib, "mng.lib")


int main()
{
	CxImage img;
	img.Load("Popo.png",CXIMAGE_FORMAT_PNG);
	if(img.IsValid())
	{
		img.Save("Popo.tif",CXIMAGE_FORMAT_TIF);
	}
	getchar();
	return 0;
}