#ifndef NO_IDENT
static char *Id = "$Id: setctrl.c,v 1.3 1984/12/19 00:33:32 tom Exp $";
#endif

/*
 * Title:	setctrl.c
 * Author:	Thomas E. Dickey
 * Created:	18 Dec 1984
 * Last update:	18 Dec 1984
 *
 * Function:	Set/clear the VMS control functions for ^T, ^Y.  This is used
 *		by FLIST.
 */

#define	LIB$M_CLI_CTRLT	0x00100000
#define	LIB$M_CLI_CTRLY	0x02000000

setctrl (turnon)
int	turnon;
{
static
int	newmask	= (LIB$M_CLI_CTRLT | LIB$M_CLI_CTRLY),
	oldmask;

	oldmask |= LIB$M_CLI_CTRLY;	/* Should be set always	*/
	if (turnon)
		lib$enable_ctrl (&oldmask);
	else
		lib$disable_ctrl (&newmask, &oldmask);
}
