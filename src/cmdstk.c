#ifndef NO_IDENT
static char *Id = "$Id: cmdstk.c,v 1.3 1985/05/14 10:16:56 tom Exp $";
#endif

/*
 * Title:	cmdstk.c
 * Author:	Thomas E. Dickey
 * Created:	17 Oct 1984 (broke out of 'dircmd')
 * Last update:	14 May 1985, was testing wrong variable in entry to '_put'.
 *		30 Apr 1985, always store commands in lower-case.
 *		27 Apr 1985, don't concat ' ' on end of stored-string!!
 *		22 Dec 1984, permit bidirectional movement in 'cmdstk_get'.
 *		18 Dec 1984, restrict stack to a page of memory.  Re-coded
 *			     from a linked-list to a ring buffer.
 *
 * Function:	This module maintains a buffer of the most-recently-used
 *		command strings of FLIST, permitting the user to retrieve
 *		commands for re-use or alteration.
 */

#include	"bool.h"
#include	"crt.h"

/*
 * External procedures:
 */
char	*calloc();	/* allocate a block of dynamic memory		*/

/*
 * Local (static) data:
 *
 * Save FLIST "visible commands" in a stack-list in memory, to provide
 * last-command retrieval.
 */
#define	PAGESIZE	4096
#define	MAXSTK		((PAGESIZE-4)/(1+CRT_COLS))
#define	byte		char

typedef	struct	{
	byte	head,	/* index of queue-head	*/
		stored,	/* number of items actually in queue		*/
		depth;	/* current depth back from head (0..(stored-1))	*/
	char	text[MAXSTK][CRT_COLS+1];
	} CMDSTK;

static
CMDSTK	*cmdstk_ = nullC;

#define	HEAD	cmdstk_->head
#define	STORED	cmdstk_->stored
#define	DEPTH	cmdstk_->depth
#define	TEXT(j)	cmdstk_->text[j]

#define	INDEX(j) cmdstk_index(HEAD-(j))

/*
 * Allocate a page-buffer for the command-stack.  We provide a hierarchy
 * for FLIST by copying the stack from a higher level to this level.  Thus,
 * there is no loss of continuity on entering a new level; but on exit we
 * resume with the set of stacked commands which were present on nesting.
 */
CMDSTK	*cmdstk_init ()
{
CMDSTK	*new_ = calloc (1, PAGESIZE),
	*old_ = cmdstk_;

	if (cmdstk_)	*new_ = *cmdstk_;
	cmdstk_ = new_;
	return (old_);
}

cmdstk_free (old_)
CMDSTK	*old_;
{
	if (cmdstk_)		cfree (cmdstk_);
	cmdstk_ = old_;
}

cmdstk_tos ()
{
	DEPTH = -1;		/* Provide index to most-recent	*/
}

/*
 * Retrieve the (next) most recent item on the command stack.  If we are at
 * the end, sound an alarm.  Return TRUE iff there is text to process.
 * Note that if no commands have been entered, we do not alter the output
 * string from whatever the caller set it to.
 */
int	cmdstk_get (string, dir)
char	*string;
int	dir;
{
int	deep	= DEPTH + dir;

	if ((deep < STORED) && (deep >= 0))
	{
		strcpy (string, TEXT(INDEX(deep)));
		DEPTH = deep;
		return (TRUE);
	}
	alarm ();
	return (*string);
}

/*
 * If the current command is the same as one of the last 'RING' commands,
 * do not save it.  This permits the user to toggle between a couple
 * of commands in the retrieval state.
 *
 * A command which duplicates one in the last 'RING' levels causes this
 * item to be "popped" to the top-level of the ring.  The entire stack
 * is pushed only when no match is found in the ring.
 */
cmdstk_put (s_)
char	*s_;
{
register
int	j, k;
char	string[CRT_COLS+1];
#define	RING	3

	if (*s_)		/* Save all "visible" commands	*/
	{
		strlcpy (string, s_);
		if (STORED)
		{
			for (j = 0; j < RING; j++)
			{
				if (!strcmp (string, TEXT(INDEX(j))))
				{
					for (k = j; k > 0; k--)
						strcpy (TEXT(INDEX(k)),
							TEXT(INDEX(k-1)));
					strcpy (TEXT(HEAD), string);
					return;
				}
			}
		}
		HEAD = INDEX(-1);
		if (STORED < MAXSTK)	STORED += 1;
		strcpy (TEXT(HEAD), string);
	}
}

/*
 * This procedure is called by a "visible" command to alter to extend its
 * saved-text, for command retrieval.  In particular, it is called by the
 * protection-editor.
 */
cmdstk_chg (string)
char	*string;
{
	if (STORED > 0)		/* Only "change" if there is something */
	{
		HEAD  = INDEX(1);		/* Redo this entry	*/
		cmdstk_tos ();
		STORED--;
		cmdstk_put (string);
	}
	else
		alarm ();
}

/*
 * Compute an index in the queue, accounting for wraparound.
 */
cmdstk_index (n)
int	n;
{
	if (n < 0)		n = MAXSTK - n;
	else if (n >= MAXSTK)	n = n - MAXSTK;
	return (n);
}
