 			/* Copyright 1984 (C) Thomas E. Dickey */

#include	<rms.h>
#include	<stsdef.h>

/*
 * Title:	highver.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	08 Sep 1984 (from 'mv$current', 17-May-1984)
 * Last update:	23 Jun 1985, use 'scanver' to decode version number
 *		08 Sep 1984
 *
 * Function:	Given a filename (no wildcards are assumed), return the
 *		highest version number which it has in the directory.
 *
 * Parameters:	name_	=> Filename string.  This is returned without a version
 *			   on the end.
 *
 * Returns:	the actual version, if the file is found, else 0.
 */
highver (name_)
char	*name_;
{
struct	FAB	tmpFAB;
struct	NAM	tmpNAM;
unsigned long	status;
int	len;			/* length to ending ";" */
char	tmpRSA	[NAM$C_MAXRSS],	tmpESA	[NAM$C_MAXRSS];


#define	ok(x)	status = x; if (!$VMS_STATUS_SUCCESS(status))	return (0)

	rmsinit_fab (&tmpFAB, &tmpNAM, 0, name_);
	rmsinit_nam (&tmpNAM, tmpRSA, tmpESA);

	ok(sys$parse(&tmpFAB));		/* parse the name to find version */

	strncpy (name_, tmpESA, len = (tmpNAM.nam$l_ver - tmpNAM.nam$l_node));
	name_[len] = '\0';		/* strip off version code	*/

	rmsinit_fab (&tmpFAB, &tmpNAM, 0, name_);
	rmsinit_nam (&tmpNAM, tmpRSA, tmpESA);

	ok(sys$parse(&tmpFAB));		/* parse the name	*/
	ok(sys$search(&tmpFAB));	/* ...find the file	*/

	return (scanver (tmpNAM.nam$l_ver, tmpNAM.nam$b_ver));
}
