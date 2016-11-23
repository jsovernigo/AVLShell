#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <treeLib.h>
#include <strRecord.h>

/*
int compare(void* i1, void* i2)
{
	int* int1 = (int*)i1;
	int* int2 = (int*)i2;

	return *int2 - *int1;
}
*/


void print(void* d)
{
	StrRec* s;

	s = (StrRec*)d;
	printf("%s:%d",s->string,s->count);
}

TNode* construct(char* fname)
{
	char c;
	int p;
	char* buff;
	FILE* f;
	TNode* root;

	f = fopen(fname, "r");

	buff = malloc(sizeof(char)*32);

	root = NULL;

	p = 0;

	while(1)
	{
		c = fgetc(f);
		if(c == EOF)
		{
			printf("Done reading file.\n");
			break;
		}
		else if(c == ' ' || c == '\n' || c == '\t')
		{
			buff[p] = '\0';
			p = 0;

			if(strlen(buff) > 1)
			{
				StrRec* record;
				record = makeRecord(buff);

				if(root == NULL)
				{
					root = makeNode(NULL,NULL,record);
				}
				else
				{
					root = add(root, makeNode(NULL, NULL, record), &compare, NULL); // no EQUAL ACTION.
				}
			}
		}
		else
		{
			buff[p] = c;
			p++;
		}
	}
	return root;
}

int main()
{
	char* fname = "assets/basic.txt";

	TNode* AVLTree;

	AVLTree = construct(fname);

	AVLTree = balance(AVLTree);

	printTree(AVLTree, 0, &print);

	return 0;
}


