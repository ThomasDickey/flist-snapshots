#include	<ctype.h>

/*
 * Title:	scanint.c
 * Author:	Thomas E. Dickey
 * Created:	17 Jun 1985
 * Last update:	04 Jul 1985, stepped on my good copy!!
 *
 * Function:	Translate an unsigned decimal integer, returning a pointer past
 *		the decoded part.
 *
 * Arguments:	string	=> string to decode
 *		int_	= address of number to load, iff a number is found
 *
 * Returns:	Address of first character past the string of decimal digits.
 */

char	*scanint (string, int_)
char	*string;
int	*int_;
{
register first = 1;
	while (isdigit(*string))
	{
		if (first)	first = *int_ = 0;
		*int_	= (*int_ * 10) + (*string++ - '0');
	}
	return (string);
}
