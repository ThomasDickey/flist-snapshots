/* $Id: nameheap.h,v 1.2 1995/03/18 21:57:48 tom Exp $
 *
 * public interface of nameheap.c
 */

#ifndef	NAMEHEAP_H
#define	NAMEHEAP_H

extern	char *	nameheap (char *s_, int len, char **heap);
extern	void	nameheap_set (int new_refs);
extern	int	nameheap_ref (void);
extern	void	nameheap_clr (int old_refs, char **heap);
extern	void	nameheap_add (int refs, char *text);

#ifdef	DEBUG1
extern	void	nameheap_dump (char *tag, char **heap);
#endif

#endif	/* NAMEHEAP_H */
