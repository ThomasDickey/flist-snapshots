#ifndef NO_IDENT
static char *Id = "$Id: sydelete.c,v 1.2 1985/05/22 10:36:20 tom Exp $";
#endif

/*
 * Title:	sysdelete.c
 * Author:	Thomas E. Dickey
 * Created:	22 May 1985
 * Last update:	22 May 1985
 *
 * Function:	delete a file, given its file-specification
 *
 * Parameters:	dspec	= file-specification string
 *
 * Returns:	nonzero VMS status value iff an error is detected.
 */

#include	<rms.h>
#include	<stsdef.h>

#define	ok(x) 	status = x; if (!$VMS_STATUS_SUCCESS(status)) return(status)

long	sysdelete (dspec)
char	*dspec;
{
struct	FAB	dFAB;
struct	NAM	dNAM;
long	status;
int	len;
char	dRSA	[NAM$C_MAXRSS],	dESA	[NAM$C_MAXRSS];

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
