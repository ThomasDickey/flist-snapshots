#ifndef NO_IDENT
static char *Id = "$Id: xabproui.c,v 1.2 1985/06/16 02:24:32 tom Exp $";
#endif

/*
 * Title:	xabprouic.c
 * Author:	Thomas E. Dickey
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

#include	<rms.h>

void
xabprouic (pro_, grp_, mbm_)
struct	XABPRO	*pro_;
short	*grp_, *mbm_;
{
	*grp_	= pro_->xab$l_uic >> 16;
	*mbm_	= pro_->xab$l_uic & 0xffff;
}
