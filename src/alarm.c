#ifndef NO_IDENT
static char *Id = "$Id: alarm.c,v 1.4 1995/05/29 00:26:38 tom Exp $";
#endif

/*
 * Title:	alarm.c
 * Author:	Thomas E. Dickey
 * Created:	10 Sep 1984
 * Last update:	10 Sep 1984
 *
 * Function:	Use VAX/VMS run-time routine to make an audible tone (BELL)
 *		on the user's terminal.  This is used rather than 'putchar'
 *		because we wish to avoid using the VMS-C run-time support.
 */

#include	<lib$routines.h>
#include	<descrip.h>

sound_alarm ()
{
	static $DESCRIPTOR(DSC_bell,"\007");

	lib$put_screen (&DSC_bell);
}
