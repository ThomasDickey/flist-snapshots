#ifndef NO_IDENT
static char *Id = "$Id: strlcpy.c,v 1.2 1985/05/15 10:59:16 tom Exp $";
#endif

/*
 * Title:	strlcpy.c
 * Author:	Thomas E. Dickey
 * Created:	28 Jun 1984
 * Last update: 15 May 1985, use macro, not routine for convert
 *		28 Jun 1984
 *
 * Function:	Copy a string, converting it to lowercase.
 *
 * Parameters:	optr -	output string pointer
 * 		iptr -	input string pointer
 *
 * Returns:	Pointer to final null in output buffer.
 */

#include	"ctype.h"

char	*strlcpy (optr, iptr)
char	*optr,				/* => output string		*/
	*iptr;				/* => input string		*/
{
	if (iptr == 0)
		iptr = optr;

	while (*iptr)
	{
		*optr++ = _tolower(*iptr);
		iptr++;
	}
	*optr = '\0';			/* Copy a trailing null		*/
	return (optr);
}