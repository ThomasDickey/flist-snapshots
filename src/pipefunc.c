#ifndef NO_IDENT
static char *Id = "$Id: pipefunc.c,v 1.2 1985/02/24 00:34:18 tom Exp $";
#endif

/*
 * Title:	pipe.c
 * Author:	Thomas E. Dickey
 * Created:	09 May 1984
 * Last update:	23 Feb 1985, broke out 'acpcopy' code, for other use.
 *		04 Feb 1985, provide for block-I/O
 *		17 Jan 1985, corrected call on 'dclinx'
 *		30 Dec 1984, do positive-action for protection-setting: VMS4.0
 *			     automatically propagates protection to new versions,
 *			     which is not always what I want.
 *		28 Nov 1984, to use 'dclinx' to find filenames in list
 *		16 Nov 1984, to perform attribute-propagation
 *		08 Nov 1984, to use 'rmsio' for input
 *
 * Function:	This procedure performs VAX/VMS wildcard filename processing
 *		for simple (one-input, one-output) edit-type filters.
 *		'pipefunc' is called from a main program, which passes to it
 *		the command language argument list, and the function 'func',
 *		which is called once for each file which matches the input
 *		list.
 *
 *		The return-code from 'func' is used to control the disposition
 *		of the output-file.  If greater than zero, then directory
 *		attributes (e.g., protection) are copied from the input file
 *		to the output:
 *
 *		<0:0>	Copy file protection
 *		<1:1>	Copy file creation date
 *		<2:2>	Make resulting file writeable (overwrites input protection)
 */

#include	"rmsio.h"
#include	<rms.h>
#include	<stsdef.h>

#include	"bool.h"
#include	"dclarg.h"

pipefunc (dcl_, func, blocked)
DCLARG	*dcl_;
int	(*func)();
{
RMS_STUFF;
FILE	*ifile, *ofile;

int	j,
	code,				/* Return-code from 'func'	*/
	numfiles = 0;
char	iname[NAM$C_MAXRSS],		/* Input name (trailing null)	*/
	oname[NAM$C_MAXRSS],		/* Output name (trailing ";\0")	*/
	*c_;
static
char	s_find[] = "Cannot find: %s\n",
	s_open[] = "Cannot open: %s\n",
	s_edit[] = "edit: %s\n";

	for (j = 0; c_ = dclinx(dcl_, 1, j); j++)
	{
		rmsinit_fab (&fab, &nam, "*.*;", c_);
		rmsinit_nam (&nam, &rsa, &esa);

		sys((sys$parse(&fab)))
		{
			printf (s_find, c_);
			continue;
		}

		while ((status = sys$search(&fab)) != RMS$_NMF)
		{
			if (status == RMS$_NORMAL)
			{
				cpyblk (oname, rsa, nam.nam$b_rsl);
				c_ = &oname[nam.nam$b_rsl];
				*c_-- = '\0';
				strcpy (iname, oname);
				if (!(ifile = fopen(iname, blocked ? "R" : "r")))
				{
					printf (s_open, iname);
					continue;
				}
				while (*c_ != ';' && c_ > oname)
					c_--;
				if (*c_ != ';')
					continue;
				*c_ = '\0';	/* Force default version */
				if (ofile = fopen(oname, blocked ? "W" : "w"))
				{
					printf (s_edit, iname);
					code = (*func)(ifile, ofile);
					numfiles++;
					fclose (ofile);
					acpcopy (code, iname, oname);
				}
				else
					printf (s_open, oname);
				fclose (ifile);
			}
		}
	}

	return (numfiles);
}
