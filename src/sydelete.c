#ifndef NO_IDENT
static char *Id = "$Id: sydelete.c,v 1.3 1995/06/04 02:02:06 tom Exp $";
#endif

/*
 * Title:	sysdelete.c
 * Author:	Thomas E. Dickey
 * Created:	22 May 1985
 * Last update:
 *		03 Jun 1995, prototyped
 *
 * Function:	delete a file, given its file-specification
 *
 * Parameters:	dspec	= file-specification string
 *
 * Returns:	nonzero VMS status value iff an error is detected.
 */

#include	<starlet.h>
#include	<rms.h>
#include	<stsdef.h>

#include	"rmsinit.h"

#include	"sysutils.h"

#define	ok(x) 	status = x; if (!$VMS_STATUS_SUCCESS(status)) return(status)

long	sysdelete (char *dspec)
{
	struct	FAB	dFAB;
	struct	NAM	dNAM;
	long	status;
	int	len;
	char	dRSA	[NAM$C_MAXRSS];
	char	dESA	[NAM$C_MAXRSS];

	/*
	 * Check for the delete-name:
	 */
	rmsinit_fab (&dFAB, &dNAM, 0, dspec);
	rmsinit_nam (&dNAM, dRSA, dESA);

	ok(sys$parse(&dFAB));
	ok(sys$search(&dFAB));
	ok((sys$erase (&dFAB, 0,0)));

	return (0);
}
