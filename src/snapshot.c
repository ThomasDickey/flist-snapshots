 			/* Copyright 1984, 1985 (C) Thomas E. Dickey */
#include	 <stdio.h>
#include	<ctype.h>

#include	"crt.h"

/*
 * Title:	snapshot.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	15 Oct 1984
 * Last update:	27 Jan 1985	save old-sgr on status line to restore it.
 *		17 Oct 1984
 *
 * Function:	This procedure copies the current screen-contents from the
 *		CRT module to the output file SNAPSHOT.CRT, doing minor
 *		formatting to make it readable on a printer.
 */

extern	char	*crtvec[];

static	FILE	*fp	= 0;
static	int	calls	= 0;

#define	out(s)	fprintf(fp,s)
#define	CORNER	out("+")
#define	BAR	CORNER; for(j=0; j < width; j++) out("-"); CORNER; out("\n")
#define	VERT	out("|")
#define	VEC(j)	((j == lpp1) ? sline : crtvec[j])

snapshot ()
{
int	top	= crt_top (),
	end	= crt_end (),
	lpp	= crt_lpp (),
	width	= crt_width () - 1,
	save_x	= crt_x (),
	save_y	= crt_y (),
	oldsgr	= crt_qsgr(lpp-1),
	date[2];
register
int	lpp1	= lpp - 1,
	j,	k,	over;
char	bfr	[CRT_COLS],
	sline	[CRT_COLS];
register
char	*s_,	c;

	if (!fp)
	{
		fp = fopen ("sys$login:snapshot.crt", "w");
		if (!fp)
		{
			alarm ();
			return;
		}
		calls = 0;
	}

	strcpy (sline, crtvec[lpp1]);
	sprintf (bfr, "%03d: Copying screen to SNAPSHOT.CRT ... ", ++calls);
	crt_high (bfr, strlen(bfr));
	crt_text (bfr, lpp1, 2);	/* Show this in REVERSE		*/

	sys$gettim (date);
	sysasctim (bfr, date, 21);

	fprintf (fp, "\f\nScreen dumped: %s\nImage top: %d  bottom: %d\n\n",
		bfr, top, end);

	BAR;
	for (j = 0; j < lpp; j++)
	{
		VERT;
		for (s_ = VEC(j), k = over = 0;
			k < width;
				k++)
		{
			if (*s_)
			{
				c = *s_++;
				if (!isascii(c))
				{
					c = toascii(c);
					over = k + 1;
				}
				fprintf (fp, "%c", c);
			}
			else
				fprintf (fp, " ");
		}
		VERT;
		if (over)
		{
			out("\r ");
			for (s_ = VEC(j), k = 0; k < over; k++)
			{
				c = *s_++;
				fprintf (fp, "%c", isascii(c) ? ' ' : '_');
			}
		}
		fprintf (fp, "\n");
	}
	BAR;

	sleep(1);			/* Make sure user sees message	*/
	crt_text ("",    lpp1, 0);	/* flush differences in highlit	*/
	crt_text (sline, lpp1, oldsgr);	/* Use original highlighting	*/
	crt_move (save_y, save_x);
}
