#ifndef NO_IDENT
static char *Id = "$Id: flescp.c,v 1.3 1985/06/11 10:47:46 tom Exp $";
#endif

/*
 * Title:	flescp.c
 * Author:	Thomas E. Dickey
 * Created:	11 Jul 1984
 * Last update:	11 Jun 1985, added cli-argument to dds_spawn
 *		11 Jul 1984
 *
 * Function:	Spawn an external process to permit command entry outside
 *		FLIST.
 */

#include	<ctype.h>

#include	"flist.h"
#include	"dclarg.h"

flescp (curfile_, xcmd_, xdcl_)
int	*curfile_;
char	*xcmd_;
DCLARG	*xdcl_;
{
	dds_spawn ((_toupper(xcmd_[1]) == 'H') ? "shell" : nullC,
		*curfile_, 0, 0, FALSE, 2);
}
