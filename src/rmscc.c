#ifndef NO_IDENT
static char *Id = "$Id: rmscc.c,v 1.3 1985/02/20 10:58:40 tom Exp $";
#endif

/*
 * Title:	rmscc.c
 * Author:	Thomas E. Dickey
 * Created:	02 Jan 1985
 * Last update:	20 Feb 1985, return "-1" if file has undefined format
 *		18 Feb 1985, return "-1" if file is not in sequential format
 *		15 Feb 1985, return "-1" if 512-byte record (OBJ, EXE types)
 *
 * Function:	RMSCC is designed be used in conjunction with the 'rmsio'
 *		module.  It tests the format+attributes of an open file to see
 *		if its format implies carriage control.  RMSCC is used by the
 *		BROWSE program to determine if the input file contains carriage
 *		control, or if each record should be interpreted as a newline,
 *		or if the file contains neither explicit or implied carriage
 *		control.
 *
 * Arguments:	rab_	=> RAB which in turn points to a FAB which contains
 *			   codes defining the format+attributes
 *
 * Returns:	0	if the file uses no carriage-control,
 *		1	if the file uses implicit or explicit carriage control,
 *		-1	if the file is formatted FIX-512 or VAR-512 (ordinary
 *			binary files on VMS).
 */

#include	<rms.h>

#include	"bool.h"

bool	rmscc (rab_)
struct	RAB	*rab_;
{
register
struct	FAB	*fab_	= rab_->rab$l_fab;
register
int	rfm	= fab_->fab$b_rfm,
	rat	= fab_->fab$b_rat,
	code	= 0;

	if ((rfm == FAB$C_STMLF)
	||  (rfm == FAB$C_STMCR)
	||  (rat &  FAB$M_FTN)
	||  (rat &  FAB$M_CR)
	||  (rat &  FAB$M_PRN))
		code = 1;
	else if ((rfm == FAB$C_FIX || rfm == FAB$C_VAR)
	&&	 (fab_->fab$w_mrs == 512))
		code = -1;
	else if ((fab_->fab$b_org != FAB$C_SEQ)
	||	 (rfm == FAB$C_UDF) )
		code = -1;
	return (code);
}
