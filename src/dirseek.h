/* $Id: dirseek.h,v 1.1 1995/06/04 23:58:56 tom Exp $
 *
 * interface of dirseek.c
 */

#ifndef DIRSEEK_H
#define DIRSEEK_H

#define	tDIRSEEK \
	int	(*for_each)(char *buf, int len, long status)

extern	int	dirseek ( char *cmd_, DCLARG *d_, int mfld, int need);
extern	int	dirseek_spec (DCLARG *spec, int implicit, tDIRSEEK);
extern	int	dirseek_spec2 (char *spec, tDIRSEEK);

#endif /* DIRSEEK_H */
