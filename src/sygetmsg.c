  	/* Copyright 1984 (C) Thomas E. Dickey */

#include	<ssdef.h>
#include	<descrip.h>

/*
 * Title:	sysgetmsg.c
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	13 Jul 1984
 * Last update:	14 Jul 1984
 *
 * Function:	Use the VMS procedure LIB$SYS_GETMSG to convert a return
 *		status into the corresponding error message.
 *
 * Parameters:	status	= return status from a LIB$-, SYS$-, etc. function.
 *		msg[]	= buffer for return message.
 *		size_msg= size of buffer 'msg[]'
 *
 * Patch:	Because this procedure is used to translate completion codes,
 *		it cannot exploit the FAO translation, and must make special
 *		tests, e.g., for "'!AS'" => "parms".
 */

#define	MAXBFR	256
#define	MINBFR	(size_msg-1)

static	char	fao_fix[] = "'!AS'";

sysgetmsg (status, msg, size_msg)
long	status;
char	msg[];
int	size_msg;
{
char	bigbfr	[MAXBFR];
$DESCRIPTOR(DSCx,bigbfr);
short	retlen	= 0;
int	j,
	flags	= 9;	/* Show component + text only	*/

	lib$sys_getmsg (&status, &retlen, &DSCx, &flags);
	if (retlen > MINBFR)	retlen = MINBFR;
	bigbfr[retlen] = '\0';
	for (j = 0; j < retlen; j++)
	{
		if (strncmp (fao_fix, &bigbfr[j], sizeof(fao_fix)) == 0)
			strncpy (&bigbfr[j], "parms", sizeof(fao_fix));
	}
	strcpy (msg, bigbfr);
}
