/*
 * Title:	strnull
 * Author:	Thomas E. Dickey
 * Created:	03 Aug 1983
 * Last update:	11 Nov 1983
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
