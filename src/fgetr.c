  	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<stdio.h>

/*
 * Title:	fgetr.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	11 Sep 1984
 * Last update:	17 Sep 1984, return -1 on EOF
 *
 * Function:	This procedure reads a line from an (assumed) VMS carriage-
 *		control format file.  It is used by the MORE program as an
 *		interim solution until a suitable set of RMS-oriented routines
 *		can be developed to read other formats.
 *
 */
fgetr (file_, bfr, maxbfr, mark_)
FILE	*file_;		/* file-descriptor pointer	*/
char	bfr[];		/* buffer to load		*/
int	maxbfr,		/* ...its size			*/
	*mark_;		/* file-address of buffer	*/
{
int	len = 0,	got;

	while ((got = fgetc (file_)) != EOF)
	{
		if (len < (maxbfr-1))		bfr[len++] = got;
		if (got == '\n')		break;
	}
	*mark_ = ftell(file_);
	if (len <= 0)	len = -1;
	return (len);
}
