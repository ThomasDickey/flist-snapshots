#ifndef NO_IDENT
static char *Id = "$Id: acpcopy.c,v 1.5 1995/03/19 22:32:47 tom Exp $";
#endif

/*
 * Title:	ACPcopy.c
 * Author:	Thomas E. Dickey
 * Created:	23 Feb 1985, from code in 'pipefunc' written 16 Nov 1984
 * Last update:
 *		18 Mar 1995, prototypes
 *		23 Feb 1985, to make a general-access routine
 *
 * Function:	Use ACP to copy attributes from one file to another.
 *
 * Arguments:	code	Determines the actual attributes to be copied:
 *			<0:0>	Copy file protection
 *			<1:1>	Copy file creation date
 *			<2:2>	Make resulting file writeable (overwrites input protection)
 *		iname	Full name of input file
 *		oname	Full name of output file
 */

#include	"rmsio.h"
#include	<rms.h>
#include	<descrip.h>
#include	<iodef.h>
#include	<stsdef.h>

#include	"bool.h"

#include	"acp.h"

/*
 * The FIB-data is static, because it is copied (by two calls on 'pipefunc2')
 * from the input to the output file.
 */
static	FIB	fib;
static	ATR	atr[3];			/* Size: 1 more than max attributes */
static	short	short_fpro;		/* 1: File-protection		    */
static	long	quad_credate[2];	/* 2: File-creation-date	    */

static	int	acpcopy2 (int code, char *filespec);

void	acpcopy (int code, char *iname, char *oname)
{
	if (code > 0)
	{
		if (acpcopy2 (code, iname))
			acpcopy2 (0, oname);
	}
}

/*
 * Lookup/Modify attributes using ACP:
 */
static
int	acpcopy2 (int code, char *filespec)
{
	RMS_STUFF;
	long	iosb[2];
	short	chnl;
	int	j	= 0;
	int	func;
	$DESCRIPTOR(DSC_name,rsa);
	struct	dsc$descriptor	fibDSC;

	rmsinit_fab (&fab, &nam, nullC, filespec);
	rmsinit_nam (&nam, &esa, &rsa);

	sys(sys$parse(&fab))				return(FALSE);
	sys(sys$search(&fab))				return(FALSE);

	DSC_name.dsc$w_length = nam.nam$b_rsl;
	sys(sys$assign (&DSC_name, &chnl, 0, 0))	return(FALSE);

	fibDSC.dsc$w_length = sizeof(FIB);
	fibDSC.dsc$a_pointer = &fib;
	memset (&fib, 0, sizeof(fib));
	memcpy (fib.fib$w_fid, nam.nam$w_fid, 6);

#define	SET(type,size,addr) {\
	atr[j].atr$w_type = type;\
	atr[j].atr$w_size = size;\
	atr[j++].atr$l_addr = addr;}

	if (!code)
	{
		func = IO$_MODIFY;
		fib.fib$l_acctl = FIB$M_WRITECK;
	}
	else
	{
		func = IO$_ACCESS;
		short_fpro = 0xfd00;	/* (S:RWED,O:RWED,G:RE,W)	*/
		if (code & 1)	SET(ATR$C_FPRO,ATR$S_FPRO,&short_fpro)
		if (code & 2)	SET(ATR$C_CREDATE,ATR$S_CREDATE,&quad_credate)

		atr[j].atr$w_size = atr[j].atr$w_type = 0;
	}

	sys(sys$qiow (0, chnl, func, iosb, 0, 0,
			&fibDSC, 0,0,0, &atr[0],0))	return (FALSE);
	if (code & 4)	short_fpro &= ~ 0xf0;	/* Give owner full rights */
	status = sys$dassgn (chnl);
	return (TRUE);
}
