/**
 *	Giuliano Sovernigo		0948924
 *	gsoverni@mail.uoguelph.ca
 *
 *	CIS*2520				A4: AVL
 *
 *	This file contains the code for the driving functions in the program.
 *	The functions above menu are all interfaces between the void* world
 *	of the tree library and the STRREC* world of the stringRecord cfile.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <treeLib.h>
#include <strRecord.h>
#include <driver.h>

void delete(void* data)
{
	if(data != NULL)
	{
		destroyRecord((StrRec*)data);
	}
}

void print(void* d)
{
	StrRec* s;

	s = (StrRec*)d;
	printf("Key: %s, Frequency: %d\n",s->string,s->count);
}

void incEq(void* d)
{
	StrRec* s;
	s = (StrRec*)d;
	incriment(s);
}

int aboveFreq(void* data, void* freq)
{
	StrRec* strrec;
	int* ifreq;

	strrec = (StrRec*)data;
	ifreq = (int*)freq;

	if(strrec == NULL || ifreq == NULL || data == NULL)
	{
		return -1;
	}	
	else if(strrec->count >= *ifreq)
	{
		return 1;
	}
	return 0;
}

TNode* specialRemove(TNode* root, StrRec* odat)
{
	if(root == NULL)
	{
		return NULL;
	}

	if(compare(getData(root), (void*)odat) == 0)
	{
		StrRec* srec;
		srec = (StrRec*)getData(root);
		if(srec->count > 1)
		{
			printf("Key frequency reduced.\n");
			srec->count--;
			return root;
		}
		else
		{
			printf("Key removed.\n");
			return tRemove(root, odat, &compare);
		}
	}
	else
	{
		root->left = specialRemove(root->left, odat);
		root->right = specialRemove(root->right, odat);
	}
	
	return root;
}

TNode* construct(char* fname)
{
	char c;
	int p;
	char* buff;
	FILE* f;
	TNode* root;

	int entries;

	entries = 0;
	root = NULL;

	f = fopen(fname, "r");

	if(f == NULL)
	{
		printf("No such file or path: %s\n",fname);
		return NULL;
	}

	buff = malloc(sizeof(char)*32); // prepare the buffer

	if(buff == NULL)
	{
		printf("There was an error in reserving memory space.\n");
		return NULL;
	}

	root = NULL;

	p = 0;

	printf("Reading file and constructing tree; this may take around 30 seconds.\n");
	while(1)
	{
		c = fgetc(f);
		if(c == EOF) // we have found the end of the file.
		{
			printf("Done reading file.\n");
			break;
		}
		else if(c == ' ' || c == '\n' || c == '\t') // we found a word border, so dump the buffer after creating a new variable
		{
			buff[p] = '\0';
			p = 0;

			if(strlen(buff) > 1)
			{
				StrRec* record;
				record = makeRecord(buff);

				if(root == NULL)
				{
					root = makeNode(NULL,NULL,record); // create a new node using the record structs
				}
				else
				{
					root = add(root, makeNode(NULL, NULL, record), &compare, &incEq); // no EQUAL ACTION.
				}
				entries++;
			}
		}
		else
		{
			buff[p] = c;
			p++;
		}
	}
	free(buff);
	printf("Read %d entries total.\n",entries);

	fclose(f);
	return root;
}

int menu()
{
	int choice;

	TNode* root;

	root = NULL;
	choice = 0;

	printf("<Giuliano Sovernigo, 0948924>\nWeclome to the frequency tree.\nThis tree can be used to view the frequency of occuring words in a file.\n\n");

	do
	{
		char input[10];

		printf("1. Initialization\n2. Find\n3. Insert\n4. Remove\n5. Check Height and Size\n6. Find All (above a given frequency)\n7. Exit\n");
		printf("avl\\> ");
		fgets(input, 9, stdin);

		if(sscanf(input, "%d", &choice) == EOF)
		{
			printf("Did not understand that input.\n");
		}
		else if(choice == 1)
		{
			char fname[256];

			printf("filename: ");
			fgets(fname, 255, stdin);
			fname[strlen(fname)-1] = '\0';
			root = construct(fname);
			if(root != NULL)
			{
				printf("Tree constructed.\n");
			}
			else
			{
				printf("There was an error in the creation of the tree.\n");
			}
		}
		else if(choice == 2)
		{
			char key[256];

			StrRec* searchfor;
			TNode* found;

			printf("Find key: ");
			fgets(key, 255, stdin);

			key[strlen(key)-1] = '\0';
			searchfor = makeRecord(key);

			found = find(root, searchfor, &compare);

			if(found == NULL)
			{
				printf("no_such_key\n");
			}
			else
			{
				printf("Found a node matching the key:\n");
				print(found->data);
				printf("\n");
			}

			free(searchfor);
		}
		else if(choice == 3)
		{
			char key[256];
			StrRec* str;

			printf("Insert key: ");
			fgets(key, 255, stdin);
			key[strlen(key)-1] = '\0'; // this eliminates the newline character.

			str = makeRecord(key);

			root = add(root, makeNode(NULL, NULL, (void*)str), &compare, &incEq); // adds and balances the tree.
			printf("Key added succesfully.\n"); 
			
		}
		else if(choice == 4)
		{
			char key[25];
			StrRec* rec;

			printf("Remove key: ");
			fgets(key, 24, stdin);
			key[strlen(key)-1] = '\0';

			rec = makeRecord(key);

			specialRemove(root,rec);
			destroyRecord(rec);
		}
		else if(choice == 5)
		{
			int tHeight;
			int tSize;
			tHeight = 0;
			tSize = 0;
			printf("Checking overall height and size...\n");
			tHeight = height(root);
			tSize = size(root);

			printf("Height: %d\nSize: %d\n", tHeight, tSize);
	
		}
		else if(choice == 6)
		{
			int* frequency;
			frequency = malloc(sizeof(int));
			if(frequency == NULL)
			{
				printf("Huh.  Something went wrong while attempting to malloc.\n");
				continue;
			}
			*frequency = -1;

			do
			{
				char buffer[15];
				printf("Please enter a frequency: ");
				fgets(buffer, 14, stdin);
				if(sscanf(buffer, "%d", frequency) == EOF)
				{
					*frequency = -1;
				}
			}while (*frequency < 0);
			printAllMatchSpec(root, &aboveFreq, (void*)frequency, &print);
			printf("\n");
		}
		else if(choice == 7)
		{
			destroyTree(root,&delete);
		}
		
	}while(choice != 7);

	return 0;
}
