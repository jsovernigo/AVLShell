
#include "strRecord.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tryRead(char* fname)
{
	char c;
	char* buff;
	FILE* f;
	int p;

	p = 0;

	StrRec* strrec;

	strrec = NULL;

	f = fopen(fname,"r");
	buff = malloc(sizeof(char) * 32);

	while(1)
	{
		c = fgetc(f);
		if(c == EOF)
		{
			break;
		}
		else if(c == ' ' || c == '\n' || c == '\t')
		{
			buff[p] = '\0';
			p = 0;

			if(strlen(buff) > 1)
			{
				if(strrec == NULL)
				{
					strrec = makeRecord(buff);
				}
				else
				{
					if(matches(strrec, buff) == 1)
					{
						incriment(strrec, buff);
					}
				}
			}
		}
		else
		{
			buff[p] = c;
			p++;
		}
	}

	printf("Found %s %d times.\n",strrec->string, strrec->count);
	return 0;
}

int main(int argc, char** argv)
{
	if(argc > 1)
	{
		tryRead(argv[1]);
	}
	return 0;
}
