 			/* Copyright 1984 (C) Thomas E. Dickey */

#include	"flist.h"
#include	"dirent.h"
#include	"dclarg.h"

/*
 * Title:	flnoid.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	22 May 1984
 * Last update:	11 Jun 1985, added cli-argument to dds_spawn
 *		26 Jul 1984, modified 'dirseek()'
 *		16 Jul 1984
 *		10 Jul 1984, re-coded to DCLARG-list.
 *		03 Jul 1984, changed name 'faccess' to 'dirent_acc'
 *		22 May 1984
 *
 * Function:	Spawn an external process (PRINT or SUBMIT).  To avoid messing
 *		up the screen, append the NOIDENTIFY option.  These use the
 *		NOWAIT version of spawning, since their intent is only to
 *		queue a request.
 *
 *		The arguments need not be members of 'filelist[]', since they
 *		are not modified.
 *
 * Patch:	I would rather capture and display the enqueued-message.
 */

char	*calloc();		/* => dynamically allocated memory	*/

static
char	format[] = "%s/noidentify";

flnoid (curfile_, xcmd_, xdcl_)
int	*curfile_;
char	*xcmd_;
DCLARG	*xdcl_;
{
int	pr_cmd	= (strcmp ("PRINT", xdcl_->dcl_text) == 0);
char	*full_;

	if (! dirseek (xcmd_, xdcl_, 1, TRUE))	return;

	full_ = calloc (1, strlen(xcmd_)+sizeof(format));
	sprintf (full_, format, xcmd_);

	dds_spawn (0, *curfile_, full_, (pr_cmd ? "Printing..." : 0), TRUE, 1);
	cfree (full_);
}
