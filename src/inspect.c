  	/* Copyright 1984, 1985 (C) Thomas E. Dickey */

#include	<ctype.h>

#include	"bool.h"

/*
 * Title:	inspect.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	17 Nov 1984
 * Last update:	15 Jun 1985, typed 'ropen'
 *		04 Feb 1985, block-encrypted files do not have proper record
 *			     structure and so will exit immediately with
 *			     an error/end-of-file.  Forgot to check for null
 *			     file.
 *
 * Function:	Read the beginning of a specified file, to see if it seems
 *		to be ordinary source-text.  If so, return TRUE.  We accepts
 *		any combination of the normal "printing" set, or the VAX/VMS
 *		"space" characters (space, tab, line feed, carriage return or
 *		form feed).
 *
 * Arguments:	filespec - null-ended string defining file name.
 *		toscan	 - minimum number of characters to scan (unless we
 *			   get an end-of-file first).
 *
 * Returns:	TRUE iff all scanned characters are as expected, and if the
 *		longest-record length is reasonable.
 */

char	*ropen();

#define	LEGAL(c) (isascii(c) && ((c == '\b') || isspace(c) || isprint(c)))

inspect (filespec, toscan)
char	*filespec;
int	toscan;
{
int	j, c,
	lenr,
	mark,
	success	= FALSE;
char	*file_	= ropen (filespec, "r"),
	z[1024];


	/*
	 * We need at least one non-null record, with all legal-characters.
	 */
	if (file_)
	{
		if (rsize(file_) < sizeof(z))
		{
			while ((lenr = rgetr(file_, z, sizeof(z), &mark)) >= 0)
			{
				for (j = 0; j < lenr; j++)
				{
					c = z[j];
					if (! LEGAL(c))
					{
						success = FALSE;
						goto done;
					}
				}
				if (mark > toscan)	break;
				success	= TRUE;
			}
		}
done:		rclose (file_);
	}
	return (success);
}
