/**
 *	Giuliano Sovernigo		0948924
 *	gsoverni@mail.uoguelph.ca
 *
 *	CIS*2520				A4: AVL
 *
 *	This file contains the main function for the program.  It calls the menu
 *	function in driver.c
 */

#include <stdio.h>
#include <driver.h>

/**
 * 	main
 * 	this is the main function in the program. 
 * 	IN:			void
 * 	OUT:		0 or 1
 * 	POST:		program has been executed.
 * 	ERROR:		various; malloc, etc.
 *
 */
int main()
{
	int result;

	result = menu();

	if(result != 0)
	{
		printf("Whoops, an error occurred.\n");
		return 1;
	}
	return 0;
}
