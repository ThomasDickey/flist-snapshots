#ifndef NO_IDENT
static char *Id = "$Id: syhour.c,v 1.3 1995/02/19 18:20:09 tom Exp $";
#endif

/*
 * Title:	syshour.c
 * Author:	Thomas E. Dickey
 * Created:	02 Aug 1984
 * Last update:
 *		19 Feb 1995, prototypes
 *		25 Jun 1985, corrected comments.
 *		21 Dec 1984, test for special cases 0, -1 which cause the system
 *			     routines to supriously generate current-time-of-day.
 *
 * Function:	Given a 64-bit VMS date+time, return a corresponding
 *		single-word value for hours and minutes within the day.
 *
 * Parameters:	q_	=> 64-bit (quad-word) system date
 *
 * Returns:	A single (32-bit) unsigned integer.  This function is used
 *		to sort filedates by time-of-day.  Since the actual number
 *		of 10MHz clock ticks would not really fit within 32 bits,
 *		the entire result must be right-shifted by at least 3 bits.
 *		(A full day is 0xC9.2A69C000.)
 */

#include <string.h>

#include "sysutils.h"

#define	SHR	8
#define	WORD	32

static	char	origin[] = "17-NOV-1858";

unsigned
syshour (long *q_)
{
	unsigned quad[2];
	char	bfr[80];

	if (q_[0] == 0)
		quad[0] = 0;
	else if (q_[1] == -1)
		quad[0] = -1;
	else
	{
		sysasctim (bfr, q_, sizeof(bfr));
		strncpy (bfr, origin, sizeof(origin)-1);
		sysbintim (bfr, quad);
		quad[0] >>= SHR;
		quad[0] += (quad[1] << (WORD-SHR));
	}
	return (quad[0]);
}

/*
 * Function:	Convert the integer returned by 'syshour' to a string (hours
 *		and minutes only).
 *
 * Parameters:	co_	=> output string
 *		q	=  single-word integer to convert
 *		len	=  maximum length of output string
 */
void
syshours (char *co_, unsigned q, int len)
{
	unsigned quad[2];
	int	max;
	char	bfr[80], *ci_;

	quad[1] = q >> (WORD-SHR);		/* Reconstruct 64-bit time */
	quad[0] = q << SHR;
	sysasctim (bfr, quad, sizeof(bfr)); 	/* Get a string (from origin) */
	ci_ = &bfr[sizeof(origin)];		/* => hh:mm:ss.cc	*/
	if (len < (max = strlen(ci_)))	max = len;
	strncpy (co_, ci_, max);
	co_[max] = '\0';
}
