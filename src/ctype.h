/*
 * Title:	ctype.h - Intercept
 * Author:	Thomas E. Dickey
 * Created:	29 Aug 1984
 * Last update:	15 May 1985, prefer upper/lower macros, rather than routine
 *		29 Aug 1984
 *
 *	This include-file is used in VMS-based string routines which are
 *	intended to be portable, based on my 'ctype.c' imitation of the
 *	VAX/VMS string package.  These routines (used in SPASM, for example)
 *	include this file, which in turn (on VMS only) includes the system's
 *	version of 'ctype.h'.
 */
#include	<sys:ctype.h>

#ifndef	toupper
#define	toupper	_toupper
#endif

#ifndef	tolower
#define	tolower	_tolower
#endif
