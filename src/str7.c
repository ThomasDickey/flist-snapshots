  	/* Copyright 1984 (C) Thomas E. Dickey */

/*
 * Title:	str7.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	15 Jun 1984
 * Last update:	15 Jun 1984
 *
 * Function:	Convert a character string to/from a form in which set-parity-bit
 *		is represented as a repeat-count (less than 32).  For example,
 *		the strings
 *
 *			"A\1BC"
 *			"A\302C"
 *
 *		would be equivalent.  (Note that there is a potential ambiguity
 *		at the source-code level for numeric digits.)  If the repeat
 *		count must be greater than 31, successive bytes are added.
 */

#define	MASK	0200		/* parity mask bit			*/
#define	MRPT	31		/* maximum repeat value in a byte	*/

/*
 * Title:	str7on
 * Function:	Convert a string with embedded repeat-counts to the parity-bit
 *		format.
 *
 * Parameters:	co_	=> output buffer
 *		ci_	=> input string, ended with a null.
 */

str7on (co_, ci_)
char	*co_, *ci_;
{
int	rpt = 0, c;

	while (*ci_)
	{
		if ((c = *ci_++) && c <= MRPT)
			rpt	+= c;
		else
		{
			if (rpt-- > 0)	c	|= MASK;
			else		rpt	= 0;
			*co_++ = c;
		}
	}
	*co_ = '\0';
}

/*
 * Title:	str7off
 * Function:	Convert the parity-bit format to the repeat-count form.
 *
 * Parameters:	co_	=> output buffer
 *		ci_	=> input string, ended with a null.
 */

str7off (co_, ci_)
char	*co_, *ci_;
{
int	rpt = 0, c;

	while (*ci_)
	{
		char	*s_ = ci_;
		while (*s_ & MASK)
			rpt++,	s_++;
		for (; rpt > 0; rpt -= MRPT)
			*co_++	= (rpt > MRPT) ? MRPT : rpt;
		c	= *ci_++;
		*co_++	= c & ~MASK;
	}
	*co_ = '\0';
}
