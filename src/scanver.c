#ifndef NO_IDENT
static char *Id = "$Id: scanver.c,v 1.2 1985/06/23 23:21:06 tom Exp $";
#endif

/*
 * Title:	scanver.c
 * Author:	Thomas E. Dickey
 * Created:	23 Jun 1985
 * Last update:	23 Jun 1985
 *
 * Function:	Scan an input string for a VMS file-version number.  This code
 *		was in-line in several places, but with CC2.0, stopped working.
 *		(Could not determine the nature of the bug, save that it seems
 *		to be something wrong with 'sscanf'.)
 *
 * Arguments:	vers_	=> string to decode
 *		len	= length (string may not be null-terminated)
 *
 * Returns:	The version number.  If an '*' is found, we return the most-
 *		negative (16-bit) value.
 */

#define	WILD_VER	-32768

int	scanver (vers_, len)
char	*vers_;
int	len;
{
register
int	value	= 0,
	sflg	= 0;

	if (*vers_ == ';')	vers_++, len--;

	if (*vers_ == '*')
		value = WILD_VER;
	else while (len-- > 0)
	{
		if (*vers_ == '-')
			sflg++;
		else if (*vers_ == '+')
			len = value = 0;
		else
			value = (value * 10) + (*vers_ - '0');
		vers_++;
	}
	return (sflg ? -value : value);
}
