#include	<descrip.h>

#include	"lbrdef.h"

/*
 * Title:	help.c
 * Author:	T.Dickey (ITT/ATC)
 * Created:	20 Mar 1985
 * Last update:	20 Mar 1985
 *
 * Function:	This code is an interface between a C-program and the
 *		help-library manager.  The librarian-routine acts almost
 *		the same as VMS-HELP, save that it does no paging, and
 *		that it does not respond to single-character input (until
 *		a carriage-return is given).
 *
 *		We intend that this routine will be called to get specific
 *		help on the caller-program.  If the user types a return,
 *		then the librarian-routine will drop down by a level to
 *		display the index of the library-file.  Thus, he may explore
 *		the help-library before exiting.
 *
 * Arguments:	lib	=> the HELP-library to use.  If null, we default to
 *			   the system-help library.
 *		prg	=> the name of the program to request help on.  This
 *			   is only the *initial* entry to the help-dialog.
 *		maxcol	=  the number of columns-wide that the screen may use.
 *			   This value is used in the librarian-routine to
 *			   format the index listing (default: 0 => 80).
 */
int	lib$get_input(),
	lib$put_output();

#define	DSC(f)	static	$DESCRIPTOR(f," ")
#define	LBR(f)	status = f
#define	describe(f,arg)	if (arg)\
			{f.dsc$a_pointer = arg; f.dsc$w_length = strlen(arg);}
#define	USE(d,s)	((s != 0) ? &d : 0)

help (lib, prg, maxcol)
char	*lib, *prg;
{
long	status,
	help_index,
	func_read = LBR$C_READ,
	type_help = LBR$C_TYP_HLP,
	width = maxcol;	/* default: 80 columns */
DSC(DSC_libname);
DSC(DSC_program);

	if (!lib)	lib = "SYS$HELP:HELPLIB.HLB";
	describe(DSC_libname,lib);
	describe(DSC_program,prg);

	LBR(lbr$output_help (lib$put_output, &width, &DSC_program,
		&DSC_libname, 0, lib$get_input));
}
