#ifndef NO_IDENT
static char *Id = "$Id: canopen.c,v 1.3 1984/09/18 10:47:34 tom Exp $";
#endif

/*
 * Title:	canopen.c
 * Author:	Thomas E. Dickey
 * Created:	18 Sep 1984
 * Last update:	18 Sep 1984
 *
 * Function:	Verify that a given file can be opened (for input).  This is
 *		a more stringent test-for-existence, which is used in FLIST to
 *		verify that a command-file is present and usable.
 *
 * Parameters:	name_	=> name-string to use
 *
 * Returns:	Zero iff we can open file.
 *
 * Patch:	Should consider extending this function to testing other types
 *		of file-open.
 */

#include	<rms.h>
#include	<stsdef.h>

#define	check(f)	status = (f);\
			if (!$VMS_STATUS_SUCCESS(status)) goto failed;

int	canopen (name_)
char	*name_;
{
struct	FAB	fab;
struct	NAM	nam;
char	esa[NAM$C_MAXRSS],	/* expanded by SYS$PARSE	*/
	rsa[NAM$C_MAXRSS];	/* result from SYS$SEARCH	*/
long	status;

	rmsinit_fab (&fab, &nam, 0, name_);
	rmsinit_nam (&nam, rsa, esa);

	fab.fab$b_fac |= FAB$M_GET;

	check(sys$parse(&fab));
	check(sys$search(&fab));
	check(sys$open(&fab));
	check(sys$close(&fab));
	status = 0;

failed:
	return (status);
}
