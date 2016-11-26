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

#include <treeLib.h>

/**
 *
 */
void delete(void* d);

/**
 *
 */
void print(void* d);

/**
 *
 */
void incEq(void* d);

/**
 *
 */
int aboveFreq(void* data, void* freq);

/**
 *
 */
TNode* specialRemove(TNode* root, StrRec* odat);

/**
 *
 */
TNode* construct(char* fname);

/**
 *
 */
int menu();

#endif
