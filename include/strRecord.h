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

#ifndef __GSOVERNIGO_STRRECORD_H__
#define __GSOVERNIGO_STRRECORD_H__

#define INVALID_COMPARISON -1

struct strrec
{
	int count;
	char* string;
};

typedef struct strrec StrRec;

/**
 *	makeRecord
 *	creates a record struct that contains a string, and its frequency.
 *	IN:			string			- the string that will be stored.
 *	OUT:		a brand new record struct that can be used to store frequency.
 *	POST:		a new strrec has been returned.
 *	ERROR:		malloc fails
 */
StrRec* makeRecord(char* string);

/**
 *	destroyRecord
 *	destroys and deallocates a strrec pointer, freeing its member if possible.
 *	IN:			strrec			- the string record to be destroyed
 *	OUT:		void
 *	POST:		strrec has been deallocated and should be handled with caution
 *	ERROR:		none
 */
void destroyRecord(StrRec* strrec);

/**
 *	compare
 *	compares two records, cast as void pointers (to be used in a library)
 *	IN:			rec1			- the first record
 *				rec2			- the second record
 *				err				- an integer to check for and return errors
 *	OUT:		the result of strcmp(rec1->string, rec2->string)
 *	POST:		err has been updated.
 *	ERROR:		err is null, or either record is null.
 */
int compare(void* rec1, void* rec2);

/**
 * 	incriment
 * 	increases the counter of strrec by 1 
 * 	IN:			strrec			- the string record that will be incrimented
 *	OUT:		void
 *	POST:		strrec->counter will have been incrimented
 *	ERROR:		strrec is null
 */
void incriment(StrRec* strrec);

/**
 * 	decriment
 * 	decreases the counter, should a string be required to decrease in frequency
 * 	IN:			strrec			- a string record pointer.
 * 	OUT:		void
 * 	POST:		strrec->counter could have been updated
 *  ERROR:		strrec is null
 */
void decriment(StrRec* strrec);

/**
 *	matches
 *	returns values depending on the matching status of strrec->string and
 *	the stringCompare value.
 *	IN:			strrec			- the string record to be checked against.
 *				stringCompare	- the string we are examining
 *	OUT:		1 on match, 0 on no match, -1 on error condition.
 *	POST:		integer has been returned.				
 * 	ERROR:		either pointer is null, or strrec->string is null.
 */
int matches(StrRec* strrec, char* stringCompare);

#endif
