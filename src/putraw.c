  	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<descrip.h>

/*
 * Title:	putraw.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	12 Nov 1984
 * Last update:	12 Nov 1984
 *
 * Function:	Print a null-ended string on the terminal.  Unlike 'printf',
 *		this VMS function will not be confused by backspaces.  (The
 *		problem with 'printf' is that it does not track backspaces
 *		when determining the wraparound column.)
 */

putraw (s_)
char	*s_;
{
static
$DESCRIPTOR(DSC_bell," ");

	DSC_bell.dsc$a_pointer = s_;
	DSC_bell.dsc$w_length = strlen(s_);
	lib$put_screen (&DSC_bell);
}
