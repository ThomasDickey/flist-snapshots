#include	"ctype.h"

/*
 * Title:	strtrim
 * Author:	Thomas E. Dickey
 * Created:	11 Aug 1983
 * Last update:	11 Aug 1983
 *
 * Function:	This procedure trims trailing "blank" characters from a null-
 *		ended ASCII string, by replacing the blanks with nulls.
 *
 * Parameters:	c_ 	=> string to trim
 *
 * Returns:	The length of the string after trimming it.
 */

int
strtrim (c_)
char	*c_;
 {
int	len;

	for (len = strlen(c_--);
		(len > 0) && isspace(*(c_+len));
			*(c_+len--) = '\0');
	return (len);
 }
