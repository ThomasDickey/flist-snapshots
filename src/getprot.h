/* $Id: getprot.h,v 1.3 1995/03/18 23:02:06 tom Exp $
 * 
 * public interface of 'getprot.c', 'setprot.c'
 */

#ifndef GETPROT_H
#define GETPROT_H

typedef	struct	{
	unsigned short	p_mask;		/* protection mask	*/
	unsigned short	p_grp,		/* group code		*/
			p_mbm;		/* member code		*/
	} GETPROT;

extern	int	getprot (GETPROT *ret_, char *name_);
extern	int	setprot (char *filespec, char *prot_code);

#endif	/* GETPROT_H */
