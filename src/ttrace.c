#ifndef NO_IDENT
static char *Id = "$Id: ttrace.c,v 1.2 1985/01/29 01:03:42 tom Exp $";
#endif

#define	VARARGS	a1,a2,a3,a4,a5,a6,a7,a8,a9
ttrace (VARARGS)
{
char	msg[132];
	sysfom (msg);
	trace(VARARGS);
	trace (">%s\n", msg);
	sysfom(0);
}
