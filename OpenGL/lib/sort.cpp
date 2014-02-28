#include <stdio.h>

void qsort(int s[] int l,int r)
{
	if(l>=i) return;
	int i=l,j=r;
	int x = s[l];
	while(i<j)
	{
		while(i<j)
		{
			if(s[j] < x)
			{
				s[i++] = s[j];
				break;
			}
			j--;				
		}
		while(i<j)
		{
			if(s[i]>x)
			{
				s[i] = s[j--];
				break;
			}
			i++;
		}
		s[i] = x;
	}
}