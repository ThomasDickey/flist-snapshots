  	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<ctype.h>

#include	"flist.h"
#include	"dclarg.h"

/*
 * Title:	flescp.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	11 Jul 1984
 * Last update:	11 Jun 1985, added cli-argument to dds_spawn
 *		11 Jul 1984
 *
 * Function:	Spawn an external process to permit command entry outside
 *		DIRED.
 */

flescp (curfile_, xcmd_, xdcl_)
int	*curfile_;
char	*xcmd_;
DCLARG	*xdcl_;
{
	dds_spawn ((_toupper(xcmd_[1]) == 'H') ? "shell" : nullC,
		*curfile_, 0, 0, FALSE, 2);
}
