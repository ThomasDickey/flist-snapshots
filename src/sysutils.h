/* $Id: sysutils.h,v 1.3 1995/06/06 13:42:44 tom Exp $ */

#ifndef SYSUTILS_H
#define SYSUTILS_H

#include "datent.h"

/* syasctim.c */
void	sysasctim (char *buf, DATENT *q_, int ilen);

/* sybintim.c */
int	sysbintim (char *ci_, DATENT *obfr);

/* sydelete.c */
long	sysdelete (char *dspec);

/* syfom.c */
void	sysfom (char *co_);

/* sygetmsg.c */
void	sysgetmsg (long status, char *msg, int size_msg);

/* sygetsym.c */
int	sysgetsym (char *co_, char *ci_, int len);

/* syhour.c */
unsigned syshour (DATENT *q_);
void	syshours (char *co_, unsigned q, int len);

/* syrename.c */
long	sysrename (char *newspec, char *oldspec);

/* syrights.c */
int	sysrights (int mask, int word_num);

/* sytrnlog.c */
void	systrnlog (char *result, char *tofind);

#endif /* SYSUTILS_H */
