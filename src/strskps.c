#include	"ctype.h"

/*
 * Title:	strskps.c
 * Author:	Thomas E. Dickey
 * Created:	14 Sep 1983
 * Last update:	29 Dec 1984, to use ctype-include
 *		05 Dec 1983
 *
 * Function:	Skip over spaces and other blank characters.
 *
 * Parameters:	c_	=> string to skip over.
 *
 * Returns:	Updated pointer, after skipping blanks.  If null is found,
 *		the procedure stops on null.
 */

char	*strskps (c_)
char	*c_;
{
	if (c_)
	{
		while (*c_)
			if (isspace(*c_))
				c_++;
			else
				break;
	}
	return (c_);
}
