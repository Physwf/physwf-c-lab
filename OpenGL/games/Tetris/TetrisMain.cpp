#include "TetrisMain.h"

void display()
{
	
}

void init()
{
	
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(0,0);
	glutInitContextVersion(3,0);
	// glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Triangles");
	if(glewInit() != GLEW_OK)
	{
		printf("Glew Init Error!");
		return 1;
	}
	init();
	glutDisplayFunc(&display);
	glutMainLoop();
}