 			/* Copyright 1984 (C) Thomas E. Dickey */

#include	<rms.h>
#include	<stsdef.h>
#include	<descrip.h>

/*
 * Title:	sysgetsym.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	02 Aug 1984
 * Last update:	25 Aug 1984, assume longest filename is length of symbol
 *
 * Function:	Given a character-string, this procedure performs a run-time
 *		call (LIB$GET_SYMBOL) to obtain the expansion of the string.
 *		If the input string corresponds to a user- or system symbol,
 *		the output string is loaded with the expansion.  Otherwise,
 *		the output string is loaded with the input string.
 *
 * Parameters:	co_	=> output buffer
 *		ci_	=> input buffer (symbol to lookup)
 *		len	=  maximum length of 'co_'
 *
 * Returns:	TRUE iff a symbol was found.
 */

sysgetsym (co_, ci_, len)
char	*co_, *ci_;
int	len;
{
char	ret_bfr[NAM$C_MAXRSS];
$DESCRIPTOR(sym_desc,"");
$DESCRIPTOR(ret_desc,"");
static	short	ret_len_w;
long	status;
int	found;

	sym_desc.dsc$a_pointer = ci_;
	sym_desc.dsc$w_length  = strlen(sym_desc.dsc$a_pointer);

	ret_desc.dsc$a_pointer = ret_bfr;
	ret_desc.dsc$w_length  = sizeof(ret_bfr)-1;

	status	= lib$get_symbol (&sym_desc, &ret_desc, &ret_len_w);

	if (found = $VMS_STATUS_SUCCESS(status))
	{
		ret_bfr[ret_len_w] = '\0';
		ci_ = ret_desc.dsc$a_pointer;
	}

	/*
	 * Copy the result (or unresolved) string into the output buffer:
	 */
	if (len > strlen(ci_))	len = strlen(ci_);
	strncpy (co_, ci_, len);
	co_[len] = '\0';

	return (found);
}
