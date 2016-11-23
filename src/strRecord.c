/**
 *	Giuliano Sovernigo		0948924
 *	gsoverni@mail.uoguelph.ca
 *
 *	CIS*2520				A4: AVL
 *
 *	This file contains the declaration for the functions that are to be used
 *	to maintain String Records, a data type that contains the frequency of a
 *	given string.  The struct contains a frequency, and the string which is to
 *	be measured.  These are both to be used in combination with an AVL tree to
 *	measure the frequency fo a string's occurence in a file.
 */

#include <strRecord.h>
#include <stdlib.h>
#include <string.h>

StrRec* makeRecord(char* string)
{
	StrRec* newRecord;

	newRecord = malloc(sizeof(StrRec));
	if(newRecord == NULL)
	{
		return NULL;
	}

	newRecord->count = 1;

	newRecord->string = malloc(sizeof(char)*strlen(string)+1); // reserves a string in memory

	if(newRecord->string == NULL) // if the malloc failed
	{
		return NULL;
	}

	if(string != NULL)
	{
		strcpy(newRecord->string, string);
	}
	else
	{
		strcpy(newRecord->string, "NO_STRING");
	}

	return newRecord;
}

void destroyRecord(StrRec* strrec)
{
	if(strrec != NULL)
	{
		free(strrec->string);
	}
	free(strrec);
}

int compare(void* rc1, void* rc2)
{
	int result;


	StrRec* rec1 = (StrRec*)rc1;
	StrRec* rec2 = (StrRec*)rc2;

	result = 0;
	if(rec1 == NULL || rec2 == NULL)
	{
		return 0;
	}
	else if(rec1->string == NULL || rec2->string == NULL)
	{
		return 0;
	}

	result = strcmp(((StrRec*)rec1)->string, ((StrRec*)rec2)->string);
	
	return result;
}

void incriment(StrRec* strrec, char* stringCompare)
{
	if(matches(strrec, stringCompare) == 1)
	{
		strrec->count++;
	}
}

void decriment(StrRec* strrec, char* stringCompare)
{
	if(matches(strrec, stringCompare) == 1)
	{
		strrec->count--;
	}
}

int matches(StrRec* strrec, char* stringCompare)
{
	if(stringCompare == NULL || strrec == NULL || strrec->string == NULL)
	{
		return -1;
	}
	else if(strcmp(strrec->string, stringCompare) == 0)
	{
		return 1;
	}
	return 0;
}


