  	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<jpidef.h>

/*
 * Title:	sysrights.c
 * Author:	T.E.Dickey
 * Created:	01 Aug 1984
 * Last update:	05 Dec 1989, pass mask,word_num as args rather than vshift,
 *			     to accommodate VMS 5.1
 *		30 Sep 1985, use SYS$GETJPIw in VMS 4.x
 *		01 Aug 1984
 *
 * Function:	Test for current-process privilege, returning TRUE if the
 *		specified privilege is enabled.
 *
 * Parameters:	mask	= privilege-mask (e.g., PRV$M_BYPASS) from <prvdef.h>.
 *		word_num= 0 (for the one-bit masks!)
 */

#define	ITEM(code,len)	((code<<16)+len)

typedef	int	QUAD[2];

static
QUAD	iosb,	priv_buf;

static
int	ret_len;

static
int	itmlst[] = {
		ITEM(JPI$_CURPRIV,sizeof(QUAD)),
		&priv_buf,	&ret_len,
		JPI$C_LISTEND
		};

sysrights (mask,word_num)
int	mask,word_num;
{
	sys$getjpiw (	0,	/* efn		*/
			0,	/* pidadr	*/
			0,	/* prcnam	*/
			&itmlst,
			&iosb,
			0,	/* astadr	*/
			0);	/* astprm	*/

	return ((priv_buf[word_num] & (mask)) != 0);
}
