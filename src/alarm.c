   	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<descrip.h>

/*
 * Title:	alarm.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	10 Sep 1984
 * Last update:	10 Sep 1984
 *
 * Function:	Use VAX/VMS run-time routine to make an audible tone (BELL)
 *		on the user's terminal.  This is used rather than 'putchar'
 *		because we wish to avoid using the VMS-C run-time support.
 */

alarm ()
{
static
$DESCRIPTOR(DSC_bell,"\007");

	lib$put_screen (&DSC_bell);
}
