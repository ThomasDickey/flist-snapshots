  	/* Copyright 1984 (C) Thomas E. Dickey */

/*
 * Title:	strform2.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	13 Jul 1984
 * Last update:	13 Jul 1984
 *
 * Function:	Format a message into a buffer with restricted size.  The
 *		message consists of tag and text portions, with a separator.
 *
 * Parameters:	out	= output buffer
 *		maxout	= maximum length of out[], including null.
 *		s1[]	= tag (or message)
 *		len1	= length(s1), if > 0.
 *		s2[]	= object/text portion
 *		len2	= length(s2), if > 0.
 */

char	*strnull();	/* => end of null-ended string	*/

strform2 (out, maxout, s1, len1, s2, len2)
char	out[], s1[], s2[];
int	maxout, len1, len2;
{
	maxout--;	/* count one for the trailing null	*/
	out[0]	= '\0';
	maxout	= strform1 (out,	  maxout, s1, len1);
	maxout	= strform1 (strnull(out), maxout, ": ", 0);
	maxout	= strform1 (strnull(out), maxout, s2, len2);
}

/*
 * Title:	strform1
 *
 * Function:	Perform a restricted string-copy into the output buffer if
 *		the input string is non-null, and if there is any space in
 *		the output buffer.
 *
 * Parameters:	out[]	= output buffer
 *		maxout	= space left in buffer
 *		s1	= string to copy, if non-null.
 *		len1	= length(s1), if > 0.  If zero, do 'strlen()' to get
 *			  the actual length.
 *
 * Returns:	the space left in 'out[]' after the copy.
 */

strform1 (out, maxout, s1, len1)
char	out[], s1[];
int	maxout, len1;
{
	if (s1 && (maxout > 0))
	{
		if (len1 <= 0)		len1	= strlen(s1);
		if (len1 > maxout)	len1	= maxout;
		strncpy (out, s1, len1);
		out[len1] = '\0';
		maxout	-= len1;
	}
	return (maxout);	/* return the remaining space in buffer	*/
}
