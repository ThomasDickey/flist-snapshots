#ifndef NO_IDENT
static char *Id = "$Id: putraw.c,v 1.2 1984/11/13 01:57:42 tom Exp $";
#endif

/*
 * Title:	putraw.c
 * Author:	Thomas E. Dickey
 * Created:	12 Nov 1984
 * Last update:	12 Nov 1984
 *
 * Function:	Print a null-ended string on the terminal.  Unlike 'printf',
 *		this VMS function will not be confused by backspaces.  (The
 *		problem with 'printf' is that it does not track backspaces
 *		when determining the wraparound column.)
 */

#include	<descrip.h>

putraw (s_)
char	*s_;
{
static
$DESCRIPTOR(DSC_bell," ");

	DSC_bell.dsc$a_pointer = s_;
	DSC_bell.dsc$w_length = strlen(s_);
	lib$put_screen (&DSC_bell);
}
