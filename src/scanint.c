#ifndef	NO_IDENT
static	char	*Id = "$Id: scanint.c,v 1.3 1995/02/19 18:17:12 tom Exp $";
#endif

/*
 * Title:	scanint.c
 * Author:	Thomas E. Dickey
 * Created:	17 Jun 1985
 * Last update:
 *		19 Feb 1995, prototypes
 *		04 Jul 1985, stepped on my good copy!!
 *
 * Function:	Translate an unsigned decimal integer, returning a pointer past
 *		the decoded part.
 *
 * Arguments:	string	=> string to decode
 *		int_	= address of number to load, iff a number is found
 *
 * Returns:	Address of first character past the string of decimal digits.
 */

#include	<ctype.h>

#include	"strutils.h"

char *
scanint (char *string, int *int_)
{
	register first = 1;

	while (isdigit(*string))
	{
		if (first)	first = *int_ = 0;
		*int_	= (*int_ * 10) + (*string++ - '0');
	}
	return (string);
}
