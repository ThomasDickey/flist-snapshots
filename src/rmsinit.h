/* $Id: rmsinit.h,v 1.1 1995/05/28 23:40:40 tom Exp $
 *
 * interface of rmsinit.c
 */

#ifndef RMSINIT_H
#define RMSINIT_H

extern	void	rmsinit_fab( struct FAB *fab_, struct NAM *nam_, char *dna_, char *fna_);
extern	void	rmsinit_nam ( struct NAM *nam_, char *rsa_, char *esa_);

#endif /* RMSINIT_H */
