#ifndef NO_IDENT
static char *Id = "$Id: cmpblk.c,v 1.2 1984/10/24 10:41:28 tom Exp $";
#endif

/*
 * Title:	cmpblk.c
 * Author:	Thomas E. Dickey
 * Created:	19 Jun 1984
 * Last update:	24 Oct 1984	re-code to make it more compact.
 *
 * Function:	Compare two blocks of characters, where the block length is
 *		given by a parameter.
 *
 * Parameters:	co_, ci_ are blocks to compare
 *		ci_	=> input buffer (may be null pointer, in which case the
 *		len	= # of bytes to copy
 *
 * Returns:	-n, 0 or +n, according to whether the first argument is less,
 *		equal or greater than the second.
 */

cmpblk (co_, ci_, len)
unsigned char	*co_, *ci_;
int	len;
{
register
int	diff	= 0,
	count	= len;
register
char	*i_	= ci_,
	*o_	= co_;

	while (count-- > 0)
		if (diff = (*o_++) - (*i_++))	break;
	return (diff);
}
