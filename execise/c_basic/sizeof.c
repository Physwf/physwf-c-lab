#include <stdio.h>

int main()
{
	short int s;
	printf("s size is %d,&s size is %d\n",sizeof(s),sizeof(&s));
	short int *ps;
	ps = &s;
	printf("ps size is %d, *ps size is %d\n",sizeof(ps),sizeof(*ps));
	return 0;
}
