/*
 * Title:	strnull
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	03 Aug 83
 * Last update:	11 Nov 83
 *
 * Function:	Return a pointer to the null which ends (by convention) a
 *		character string.
 */

char	*strnull (cptr)
char	*cptr;
 {
	while (*cptr)
		cptr++;
	return (cptr);
 }
