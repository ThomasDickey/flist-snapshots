 			/* Copyright 1984 (C) Thomas E. Dickey */

#include	"ctype.h"

/*
 * Title:	strabbr.c
 * Author:	T.E.Dickey (ITT/ATC)
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
