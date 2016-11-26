/**
 *	Giuliano Sovernigo		0948924
 *	gsoverni@mail.uoguelph.ca
 *
 *	CIS*2520				A4: AVL
 *
 */

#include <stdio.h>
#include <driver.h>

/**
 *
 */
int main()
{
	int result;

	result = menu();

	if(result != 0)
	{
		printf("Whoops, an error occurred.\n");
	}
	return 0;
}
