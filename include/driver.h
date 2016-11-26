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

#ifndef __GSOVERNIGO_DRIVER_H__
#define __GSOVERNIGO_DRIVER_H__

#include <strRecord.h>
#include <treeLib.h>

/**
 * 	delete
 * 	This is a wrapper function around destroyRecord, intended to be used to
 * 	delete the contents of a strrec, but while casting it to void.
 * 	IN:			d		- the data to be destroyed (must be strrec)
 * 	OUT:		void
 * 	POST:		d has been deallocated.  Use at your own risk.
 * 	ERROR:		none
 */
void delete(void* d);

/**
 *	print
 *	prints a strrec to the screen, cast as a void pointer originally.  This
 *	is simply a way of getting around the treelib's required void pointers.
 *	IN:			d 		- the data to be printed.
 *	OUT:		void
 *	POST:		d has been printed to stdout
 *	ERROR:		
 */
void print(void* d);

/**
 *	incEq
 *	Also a wrapper around strRecord's incriment function
 *	IN:			d		- void pointer strrec that will be incrimented
 *	OUT:		void
 *	POST:		d->count has been incrimented.
 *	ERROR:		none
 */
void incEq(void* d);

/**
 *	aboveFreq
 *	Wrapper function that compares data->count to (int*) freq, returing 1 if
 *	they match.
 *	IN:			data	- the strrec data
 *				freq	- the int pointer frequency
 *	OUT:		1 on match, 0 on not, -1 on error.
 *	POST:		integer returned.
 *	ERROR:		data or freq is null.
 */
int aboveFreq(void* data, void* freq);

/**
 *	specialRemove
 *	recurses through the tree, using special techniques if the node->data->count
 *	is above 1.
 *	IN:			root	- the tree root.
 *				odat	- the other data that we need to remove.
 *	OUT:		the new root of the tree.
 *	POST:		something got removed or decrimented in root's tree.
 *	ERROR:		either is null
 */
TNode* specialRemove(TNode* root, StrRec* odat);

/**
 *	construct
 *	reads in a file, makes a tree from it.
 *	IN:			fname	- the char pointer filename.
 *	OUT:		a fully built tree
 *	POST:		a tree has been built. use it.
 *	ERROR:		fname is null or does not actually represent a valid file.
 */
TNode* construct(char* fname);

/**
 *	menu
 *	runs through the main menu of the program.
 *	IN:			void
 *	OUT:		0 on success.
 *	POST:		a tree has been allocated and deallocated, and abunch of stuf
 *				has happened.
 *	ERROR:		malloc fails, various errors
 */
int menu();

#endif
