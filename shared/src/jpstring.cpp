#include <ctype.h>
#include <string.h>

#include "jpstring.h"

/*
 trim white spaces of two ends
*/
char* jptrim(char* input)
{
  char* end;
  while(isspace(*input)) input++;
  if(*input == 0) return input;

  end = input + strlen(input) -1;
  while(end > input && isspace(*end)) end --;
  *(end+1) = 0;
  return input;
}

int jpsplit(char* input, const char* delimiters, char** list)
{
  int listlen = 0;
  bool headflag = true;
  while(*input)
  {
	const char* d = delimiters;
    while(*d++)
    {
      if(*input == *d)
      {
        *input = 0;
        headflag = true;
      }
      else
      {
		  if (headflag)
		  {
			  list[listlen] = input;
			  headflag = false;
			  listlen++;
		  }
      }
    }
    input++;
  }
  return listlen;
}
