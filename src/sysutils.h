/* $Id: sysutils.h,v 1.1 1995/02/19 18:12:07 tom Exp $ */

#ifndef SYSUTILS_H
#define SYSUTILS_H

/* syasctim.c */
void	sysasctim (char *buf, long *q_, int ilen);

/* sybintim.c */
int	sysbintim (char *ci_, long *obfr);

/* sydelete.c */
long	sysdelete (char *dspec);

/* syfom.c */
void	sysfom (char *co_);

/* sygetmsg.c */
void	sysgetmsg (long status, char *msg, int size_msg);

/* sygetsym.c */
int	sysgetsym (char *co_, char *ci_, int len);

/* syhour.c */
unsigned syshour (long *q_);
void	syshours (char *co_, unsigned q, int len);

/* syrename.c */
long	sysrename (char *newspec, char *oldspec);

/* syrights.c */
int	sysrights (int mask, int word_num);

/* sytrnlog.c */
void	systrnlog (char *result, char *tofind);

#endif /* SYSUTILS_H */
