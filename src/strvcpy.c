#ifndef NO_IDENT
static char *Id = "$Id: strvcpy.c,v 1.2 1984/11/06 00:43:26 tom Exp $";
#endif

/*
 * Title:	strvcpy.c
 * Author:	Thomas E. Dickey
 * Created:	05 Nov 1984
 * Last update:	05 Nov 1984
 *
 * Function:	Copy a string, making it uppercase, with no more than one
 *		blank in a row.  All blanks are replaced by the space
 *		character.
 *
 * Arguments:	co_	=> output string
 *		ci_	=> input string.  If null, assume 'co_'.
 */

#include	<ctype.h>

strvcpy (co_, ci_)
char	*co_, *ci_;
{
register
char	c = ' ', d = '?';

	if (!ci_)	ci_ = co_;
	do {
		c = toascii(*ci_);
		c = _toupper(c);
		ci_++;
		if (isspace(c))
		{
			if (!isspace(d))	*co_++ = ' ';
		}
		else
			*co_++ = c;
		d = c;
	} while (c);
}
