#include	"ctype.h"

/*
 * Title:	strucpy.c
 * Author:	Thomas E. Dickey
 * Created:	22 Aug 1983
 * Last update: 15 May 1985, use ctype-include
 *		11 Nov 1983
 *
 * Function:	Copy a string, converting it to uppercase.
 *
 * Parameters:	optr -	output string pointer
 * 		iptr -	input string pointer
 *
 * Returns:	Pointer to final null in output buffer.
 */

char	*strucpy (optr, iptr)
char	*optr,				/* => output string		*/
	*iptr;				/* => input string		*/
{
	if (!iptr)	iptr = optr;

	while (*iptr)
	{
		*optr++ = _toupper(*iptr);
		iptr++;
	}
	*optr = '\0';			/* Copy a trailing null		*/
	return (optr);
}
