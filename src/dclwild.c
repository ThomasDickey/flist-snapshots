	  	/* Copyright 1984 (C), Thomas E. Dickey */
#include	<rms>
#include	<stsdef.h>

#include	"dclarg.h"

/*
 * Title:	dclwild.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	30 Jun 1984
 * Last update:	26 Dec 1984, use result of 'dclarg' parsing, rather than a
 *			     re-parse here.
 *		10 Sep 1984, use "rmsinit"
 *
 * Function:	This procedure tests a VMS filename for the presence of wildcard
 *		indicators.  Its primary use is in command parsing, to ensure
 *		that no wildcards are used.
 *
 * Parameters:	dcl_	=> DCLARG structure (defining filename to test).
 *
 * Returns:	The logical 'AND' of all wildcard bits returned by SYS$PARSE
 *		in the NAM-block.  While the bit NAM$M_WILDCARD tests all of
 *		these, the actual bits are returned to test particular types
 *		of illegal wildcard use.
 */

dclwild (dcl_)
DCLARG	*dcl_;
{
	if (dcl_->dcl_stat && ! $VMS_STATUS_SUCCESS(dcl_->dcl_stat))
		return (-1);
	else
		return (dcl_->dcl$l_fnb
				& (	NAM$M_WILD_VER
				+	NAM$M_WILD_TYPE
				+	NAM$M_WILD_NAME
				+	NAM$M_WILDCARD	/* inclusive test */
				+	NAM$M_WILD_DIR
				+	NAM$M_WILD_UFD
				+	NAM$M_WILD_GRP
				+	NAM$M_WILD_MBR
				+	NAM$M_WILD_SFD1
				+	NAM$M_WILD_SFD2
				+	NAM$M_WILD_SFD3
				+	NAM$M_WILD_SFD4
				+	NAM$M_WILD_SFD5
				+	NAM$M_WILD_SFD6
				+	NAM$M_WILD_SFD7));
}
