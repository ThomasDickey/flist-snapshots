 			/* Copyright 1985 (C) Thomas E. Dickey */

#include	<rms.h>
#include	<stsdef.h>

/*
 * Title:	sysdelete.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	22 May 1985
 * Last update:	22 May 1985
 *
 * Function:	delete a file, given its file-specification
 *
 * Parameters:	dspec	= file-specification string
 *
 * Returns:	nonzero VMS status value iff an error is detected.
 */

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
