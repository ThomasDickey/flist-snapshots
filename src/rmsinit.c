 			/* Copyright 1984 (C) Thomas E. Dickey */

#include	<rms.h>

/*
 * Title:	rmsinit.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	05 Sep 1984 (from 'mv', 17 May 1984)
 * Last update:	06 Sep 1984
 *
 * Function:	These procedures do the most common type of RMS initialization,
 *		that of FAB- and NAM-block initialization for filename parsing
 *		and directory lookup.
 */

/*
 * Initialize a FAB block:
 *
 *	fab_	=> FAB block to initialize
 *	nam_	=> NAM block to use in parse
 *	dna_	=> string to use (if nonnull) in parse-default
 *	fna_	=> string to use (if nonnull) for input filename
 */
rmsinit_fab(fab_, nam_, dna_, fna_)
struct	FAB *fab_;
struct	NAM *nam_;
char	*dna_,
	*fna_;
{
	*fab_ = cc$rms_fab;

	fab_->fab$l_fop = FAB$M_NAM;
	fab_->fab$l_nam = nam_;			/* FAB => NAM block	*/
	if (dna_)
	{
		fab_->fab$l_dna = dna_;		/* Default-selection	*/
		fab_->fab$b_dns = strlen(dna_);
	}
	if (fna_)
	{
		fab_->fab$l_fna = fna_;
		fab_->fab$b_fns = strlen(fna_);
	}
}

/*
 * Initialize a NAM-block:
 *
 *	nam_	=> NAM-block to initialize
 *	rsa_	=> "resultant string" address (loaded by SYS$SEARCH)
 *	esa_	=> "expanded string" address (loaded by SYS$PARSE)
 */
rmsinit_nam (nam_, rsa_, esa_)
struct	NAM *nam_;
char	*rsa_, *esa_;
{
	*nam_ = cc$rms_nam;

	if (esa_)
	{
		nam_->nam$b_ess = NAM$C_MAXRSS;
		nam_->nam$l_esa = esa_;
	}
	if (rsa_)
	{
		nam_->nam$b_rss = NAM$C_MAXRSS;
		nam_->nam$l_rsa = rsa_;
	}
}
