#ifndef NO_IDENT
static char *Id = "$Id: trace.c,v 1.2 1984/11/05 11:22:34 tom Exp $";
#endif

#include	<stdio.h>

static	FILE	*fd;

#define	VARARGS	a1,a2,a3,a4,a5,a6,a7,a8,a9

trace(VARARGS)
int	VARARGS;
{
	if (!fd)
		fd = fopen ("sys$login:trace", "w");
	if (fd) fprintf (fd, VARARGS);
}
