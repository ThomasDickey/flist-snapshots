  	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<ctype.h>

/*
 * Title:	getpass.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	12 Nov 1984
 * Last update:	12 Nov 1984
 *
 * Function:	Prompt for a password, return it.  Like the Unix routine of
 *		the same name, this procedure returns a pointer to a static
 *		buffer.
 */

#define	MAXBFR	8

char	*getpass (s_)
char	*s_;
{
int	c, len = 0;
static
char	buffer[MAXBFR+1];

	putraw (s_);
	for (;;)
	{
		c = getraw(0,1,0);
		c = toascii(c);
		switch (c)
		{
		case '\b':
		case 0177:
			if (len > 0)
			{
				putraw ("\b \b");
				buffer[--len] = '\0';
			}
			else	alarm();
			break;
		case '\r':
		case '\n':
			if (len)
			{
				putraw ("\r\n");
				return (buffer);
			}
			alarm ();
			break;
		default:
			if (isprint(c) && len < MAXBFR)
			{
				buffer[len++] = c;
				buffer[len] = '\0';
				putraw (".");
			}
			else	alarm ();
		}
	}
}
