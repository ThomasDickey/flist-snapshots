   	 	/* Copyright 1985 (C), Thomas E. Dickey */
#include	<rms.h>

/*
 * Title:	xabprouic.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	15 Jun 1985
 * Last update:	15 Jun 1985
 *
 * Function:	Extract uic fields (group and member) from a XABPRO structure.
 *		This function changed with CC2.0 (from CC1.5).
 *
 * Arguments:	pro_	=> XABPRO structure to extract from
 *		grp_	=> word to load with group
 *		mbm_	=> word to load with member
 */

xabprouic (pro_, grp_, mbm_)
struct	XABPRO	*pro_;
short	*grp_, *mbm_;
{
	*grp_	= pro_->xab$l_uic >> 16;
	*mbm_	= pro_->xab$l_uic & 0xffff;
}
