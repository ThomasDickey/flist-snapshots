#ifndef NO_IDENT
static char *Id = "$Id: flmore.c,v 1.3 1985/07/03 10:30:10 tom Exp $";
#endif

/*
 * Title:	flmore.c
 * Author:	Thomas E. Dickey
 * Created:	20 Jun 1984
 * Last update:	03 Jul 1985, cleanup 'filelist' definition.
 *		30 Dec 1984, provide for current-entry-only call (xdcl_==0).
 *		27 Sep 1984, no need for restriction to source-filetypes.
 *		10 Jul 1984, corrected filename determination
 *		04 Jul 1984, converted to DCLARG-list
 *		03 Jul 1984, changed 'faccess' to 'dirent_acc'
 *		20 Jun 1984
 *
 * Function:	This module performs a call to the BROWSE program (linked) with
 *		FLIST.
 */

#include	"flist.h"
#include	"dirent.h"
#include	"dclarg.h"

import(filelist);

flmore (curfile_, xcmd_, xdcl_)
int	*curfile_;
char	*xcmd_;
DCLARG	*xdcl_;
{
FILENT	ztmp;
int	j, argc;
char	*argv	[3],
	fullname[MAX_PATH],	owncmd[MAX_PATH + 10];

	argv[0] = "BROWSE";	/* patch: WhoAmI */
	argv[1] = xcmd_;
	argv[2] = 0;
	argc = 2;

	if (xdcl_ && xcmd_)
		strcpy (fullname, dclinx (xdcl_, 1, 0));
	else
	{
		dirent_glue (fullname, FK_(*curfile_));
		sprintf (argv[1] = owncmd, "BROWSE %s", fullname);
	}

	if (! dirent_old1 (&ztmp, fullname))	return;

	if (! dirent_acc(&ztmp, "r"))
	{
		warn ("No read-access rights to %s", fullname);
		return;
	}

	more (argc, argv);
	if (!didwarn ())	dds_all (-1, *curfile_);
}