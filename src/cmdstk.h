/*
 * Title:	cmdstk.h
 * Author:	Thomas E. Dickey
 * Created:	27 May 1995
 * Last update:
 *
 * Interface of cmdstk.c
 *
 * $Id: cmdstk.h,v 1.1 1995/05/27 23:59:42 tom Exp $
 */

#ifndef CMDSTK_H
#define CMDSTK_H

#define	PAGESIZE	4096
#define	MAXSTK		((PAGESIZE-4)/(1+CRT_COLS))

typedef	struct	{
	char	head;	/* index of queue-head	*/
	char	stored;	/* number of items actually in queue		*/
	char	depth;	/* current depth back from head (0..(stored-1))	*/
	char	text[MAXSTK][CRT_COLS+1];
	} CMDSTK;

extern	void	cmdstk_chg (char *string);
extern	void	cmdstk_free (CMDSTK *old_);
extern	int	cmdstk_get (char *string, int dir);
extern	CMDSTK*	cmdstk_init (void);
extern	void	cmdstk_put (char *s_);
extern	void	cmdstk_tos (void);

#endif /* CMDSTK_H */
