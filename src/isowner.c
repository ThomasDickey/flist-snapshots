#ifndef NO_IDENT
static char *Id = "$Id: isowner.c,v 1.3 1989/12/05 11:57:50 tom Exp $";
#endif

/*
 * Title:	isowner.c
 * Author:	T.E.Dickey
 * Created:	20 Dec 1984
 * Last update:
 *		04 Nov 1988, removed masking from getuid/getgid calls.
 *		12 Nov 1985, patch (for v4.x) to use only low-byte of uid codes
 *		20 Dec 1984
 *
 * Function:	Test (for FLIST) a file's UIC to see if it is either owned
 *		by the current process, or if the process has sufficient
 *		privilege to modify it.
 *
 * Arguments:	z	=> FILENT structure defining file.
 */

#include	<prvdef.h>

#include	"flist.h"
#include	"dirent.h"

/*
 * External procedures and data:
 */
char	*strnull();		/* => end of line		*/

#define	CMP(func,offset) (func() != z->offset)

isowner (z)
FILENT	*z;
{
char	msg	[CRT_COLS];

	if (CMP(getgid,f_grp) || CMP(getuid,f_mbm)
	&& ! sysrights(PRV$M_SYSPRV,0))
	{
		strcpy (msg, "You are not the file's owner");
		if (z->f_grp == -1)
			strcat (msg, "(NO Privilege)");
		else
			sprintf (strnull(msg), ": [%03o,%03o]",
				z->f_grp, z->f_mbm);
		warn2 (msg);
		return (FALSE);
	}
	return (TRUE);
}
