  	/* Copyright 1984 (C) Thomas E. Dickey */

/*
 * Title:	setctrl.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	18 Dec 1984
 * Last update:	18 Dec 1984
 *
 * Function:	Set/clear the VMS control functions for ^T, ^Y.  This is used
 *		by DIRED.
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
