#ifndef NO_IDENT
static char *Id = "$Id: strabbr.c,v 1.2 1984/09/01 13:28:12 tom Exp $";
#endif

/*
 * Title:	strabbr.c
 * Author:	Thomas E. Dickey
 * Created:	11 Jul 1984
 * Last update:	01 Sep 1984, use '_toupper'
 *
 * Function:	Compare two strings, ignoring case, to see if the first is
 *		an allowable abbreviation of the second.
 *
 * Parameters:	tst_	=> string to test
 *		ref_	=> string to use as a reference
 *		cmplen	=  length of 'tst_' to compare (should be determined
 *			   by either 'strlen', or delimiter).
 *		abbr	=  minimum match length needed for legal abbreviation
 *
 * Returns:	TRUE if the strings are matched.
 */

#include	"ctype.h"

strabbr (tst_, ref_, cmplen, abbr)
char	*tst_, *ref_;
int	cmplen, abbr;
{
	while (*tst_ && *ref_ && (cmplen > 0))
	{
		if (_toupper(*tst_) != _toupper(*ref_))	break;
		tst_++;
		ref_++;
		cmplen--;
		abbr--;
	}
	return ((abbr <= 0) && (cmplen <= 0));
}
