  	/* Copyright 1984 (C) Thomas E. Dickey */

/*
 * Title:	strscale.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	06 Jun 1984
 * Last update:	07 Jun 1984
 *
 * Function:	This procedure creates a column-scale, with numbers for use in
 *		editors, etc.  For example, if the initial column is 1, then
 *		a scale such as the following might be returned:
 *
 *		"....+...10....+...20....+...30"
 *
 *		If the starting column is not 1, the procedure properly starts
 *		on the substring of the global scale.
 *
 * Parameters:	co_	=> output buffer
 *		col	=  beginning column number
 *		len	=  length of output buffer
 */

static
char	ten[] = "....+....|";

strscale (co_, col, len)
char	*co_;
int	col, len;
{
int	first	= 1,		/* flag for leading 0's column	*/
	numlen;
char	number[20],
	catbfr[20];

	if (col < 1)	col = 1;
	*co_ = '\0';

	while (len > 0)
	{
		int	base10	= (col / 10) * 10,
			next10	= base10 + 10,
			units	= col - base10;
		char	*s_	= catbfr;

		sprintf (number, "%d", next10);
		numlen	= strlen (number);
		if (units)
		{
			strcpy (catbfr, &ten[units-1]);
			units = strlen (catbfr);
			if (units > numlen + 2)
				strcpy (&catbfr[units-numlen], number);
		}
		else
		{
			if (first)
				*co_++ = '|', *co_ = '\0', len--;
			strcpy (catbfr, ten);
			strcpy (&catbfr[10-numlen], number);
		}
		while (*s_ && len > 0)
		{
			*co_++ = *s_++;
			*co_   = '\0';
			len--;
		}
		col	= next10;
		first	= 0;
	}
}
