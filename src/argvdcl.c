  		 /* Copyright 1984 (C), Thomas E. Dickey */
#include	"bool.h"
#include	"dclarg.h"

/*
 * Title:	argvdcl.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	28 May 1984
 * Last update:	15 Dec 1984, added 'cpy_dft' argument to DCLARG.  Corrected
 *			     use of argc-count.
 *		24 Jul 1984, added 'cmd_arg' parameter to DCLARG.
 *		26 Jun 1984
 *
 * Function:	This procedure translates C-type argc,argv module-arguments
 *		into a character string, calls 'dclarg' to process the
 *		resulting list, and returns the DCLARG-pointer to the caller.
 *
 * Parameters:	argc, argv - Passed from module via VMS call.
 *		dft_	=> string specifying defaults for file specifications.
 *		cmd_arg	=  TRUE if command-token appears (first) on the line.
 *
 * Note:	This should not be used as a general replacement for the
 *		VAX/VMS DCL interface.
 */

char	*calloc();

DCLARG	*argvdcl (argc, argv, dft_, cmd_arg)
int	argc;
char	*argv[],
	*dft_;
int	cmd_arg;
{
DCLARG	*arg_	= 0;
int	len	= 0, j;
char	*c_;

	if (argc > 1)
	{
		for (j = 1; j < argc; j++)
			len += 3 + strlen(argv[j]);
		c_ = calloc(1, len);

		for (j = 1; j < argc; j++)
			sprintf (strnull(c_), " %s", argv[j]);
		arg_ = dclarg(c_, dft_, cmd_arg, FALSE);
		cfree (c_);
	}
	return (arg_);
}
