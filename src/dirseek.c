  	/* Copyright 1984, 1985 (C) Thomas E. Dickey */
#include	<rms.h>

#include	"flist.h"
#include	"dclarg.h"

/*
 * Title:	dirseek.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	16 Jul 1984
 * Last update:	15 Jun 1985, typed 'dirread_path'.  Reference 'for_each' as
 *			     '(*for_each)' to make CC2.0 happy.
 *		05 Feb 1985, use DCLARG-argument in 'dirseek_spec' instead of
 *			     string, to support explicit-pathname code.
 *		09 Sep 1984, use "rmsinit"
 *		26 Aug 1984, cleanup buffer sizes
 *		31 Jul 1984, added 'dirseek_spec' entry
 *		26 Jul 1984, added 'need' option
 *		16 Jul 1984
 *
 * Function:	This procedure is used by DIRED to verify the existence of a
 *		list of files, used as arguments in an input list.  A simple
 *		search is used rather than checking (additionally) the read
 *		access due to the long time required if a wildcard is given.
 *
 *		The filenames which are tested are assumed to be syntactically
 *		correct.
 *
 * Parameters:	cmd_	=> original command text (for nicer messages).
 *		d_	=> DCLARG-list to test. (Options are ignored.)
 *		mfld	=  parameter number to test (e.g., 1=input, 2=output)
 *		need	=  TRUE if a warning message is emitted when one or
 *			   files is not found.
 *
 * Returns:	TRUE if all filespec's are found. If not, and if 'need' is set,
 *		a warning message is generated.
 */

char	*dirread_path();

#define	RMS_STUFF	struct	FAB	fab;\
			struct	NAM	nam;\
			long	status;\
			char	rsa[NAM$C_MAXRSS],	/* resultant 	*/\
				esa[NAM$C_MAXRSS]	/* expanded (search)*/

dirseek (cmd_, d_, mfld, need)
char	*cmd_;
DCLARG	*d_;
int	mfld, need;
{
static
char	sFMT1[]	= "File(s) not found: %%.%ds";
char	format	[sizeof(sFMT1)+6];

	for (; d_; d_ = d_->dcl_next)
	{
		if (isopt (d_->dcl_text[0]))	continue;
		else if (d_->dcl_mfld != mfld)	continue;

		if (! dirseek_spec (d_, FALSE, nullC))
		{
			if (need)
			{
				sprintf (format, sFMT1, d_->dcl_size);
				warn (format, &cmd_[d_->dcl_from]);
			}
			return (FALSE);
		}
	}
	return (TRUE);
}

/* <dirseek_spec>:
 * Seek all occurrences of a particular filespec.  (This is a common procedure,
 * shared with 'flscan').
 */
dirseek_spec (spec, implicit, for_each)
DCLARG	*spec;
int	implicit,
	(*for_each)();
{
RMS_STUFF;
int	inx, rcode;
char	*p_;

	/*
	 * If the 'implicit' argument is set on entry, check the pathname to
	 * see if it was explicit (i.e., if any part was given).  If no pathname
	 * was given, then any pathname from the read-list will match the
	 * pathname in this search.  Otherwise, we restrict ourselves to a
	 * (normal VMS-style) search within the specified set of directories.
	 *
	 * Note that matching against the read-list pathnames is still an
	 * approximation, but one which should be a superset of the display-
	 * list.
	 *
	 * The 'toname' index is required to kill off the current default
	 * directory (supplied by sys-parse in the dclarg-table building phase.
	 */
	if (implicit)	implicit = dirfind_notexp (spec);

	if (implicit)
	{
		for (inx = 0; p_ = dirread_path (&inx); inx++)
		{
		int	toname	= spec->dcl$b_node
				+ spec->dcl$b_dev
				+ spec->dcl$b_dir;
			rmsinit_fab (&fab, &nam, p_, &spec->dcl_text[toname]);
			rmsinit_nam (&nam, rsa, esa);
			if ((status = sys$parse(&fab)) == RMS$_NORMAL)
			{
				esa[nam.nam$b_esl] = EOS;
				if (!(rcode = dirseek_spec2 (esa, for_each)))
					break;
			}
		}
	}
	else
		rcode = dirseek_spec2 (spec->dcl_text, for_each);
	return (rcode);
}

/* <dirseek_spec2>:
 * Seek all occurrences of a particular filespec.  (This is a common procedure,
 * shared with 'flscan').
 */
dirseek_spec2 (spec, for_each)
char	*spec;
int	(*for_each)();
{
RMS_STUFF;

	rmsinit_fab (&fab, &nam, 0, spec);
	rmsinit_nam (&nam, rsa, esa);

	if ((status = sys$parse(&fab)) == RMS$_NORMAL)
	{
		for (;;)
		{
			status = sys$search(&fab);
			if (for_each)
				(*for_each) (rsa, nam.nam$b_rsl, status);
			if (status == RMS$_NMF)
				return (TRUE);
			else if (status != RMS$_NORMAL)
				break;
		}
	}
	return (FALSE);		/* Common return if any error	*/
}
