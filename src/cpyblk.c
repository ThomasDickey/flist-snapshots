#ifndef NO_IDENT
static char *Id = "$Id: cpyblk.c,v 1.2 1983/10/12 15:30:28 tom Exp $";
#endif

/*
 * Title:	cpyblk.c
 * Author:	Thomas E. Dickey
 * Created:	17 Aug 1983
 * Last update:	12 Oct 1983
 *
 * Function:	Copy a block of characters (bytes), such as a component of
 *		an arbitrary structure.  For practical use, this assumes that
 *		the value returned by 'sizeof' is identical with the number
 *		of 'char' bytes.
 *
 * Parameters:	co_	=> output buffer
 *		ci_	=> input buffer (may be null pointer, in which case the
 *			output buffer is cleared.)
 *		len	= # of bytes to copy
 *
 * Returns:	The original 'co_' pointer, to facilitate use of this routine
 *		in nested calls.
 */

char	*cpyblk (co_, ci_, len)
char	*co_,
	*ci_;
int	len;
{
char	*c_	= co_;

	for (; len > 0; len--)
	{
		if (ci_)
			*co_++ = *ci_++;
		else
			*co_++ = 0;
	}
	return (c_);
}
