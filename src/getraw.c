   	 /* Copyright 1984 (C) Thomas E. Dickey */
#include	<ctype.h>
#include	<descrip.h>
#include	<iodef.h>
#include	<ssdef.h>
#include	<string.h>
#include	<stsdef.h>

#include	"bool.h"
#include	"crt.h"

/*
 * Title:	getraw.c
 * Author:	T.E.Dickey
 * Created:	03 May 1984
 * Last update:
 *		24 Feb 1989, when reading from a command-file, suppress lines
 *			     which do not begin with '$' (with optional blanks)
 *		17 Aug 1988, use SYS$COMMAND instead of SYS$INPUT.
 *
 *		17 Jul 1985, added sid for second atc/780
 *		15 Jun 1985, reference syi-func as '(*func)', rather than by
 *			     '(func)' to make CC2.0 happy.  Also, typed calloc.
 *		13 Jun 1985, use 2 sid's for 750 !!
 *		10 Jun 1985, ensure type-ahead is killed if CTRL/X
 *		08 Jun 1985, added code for interactive type-ahead
 *		08 May 1985, corrected sid for ATC/730 for BTM-demo
 *		27 Apr 1985, changed sid for ATC/750
 *		20 Apr 1985, added ATC/785-sid
 *		10 Apr 1985, made command-files nest, some better error checks.
 *		06 Apr 1985, added file-input, CTRL/X-ast
 *		29 Mar 1985, added 'status' to 'error'.
 *		26 Mar 1985, added ATC-730's SID
 *		24 Feb 1985, added SID-test, to restrict porting, removed ^C^C.
 *		02 Dec 1984, added entry 'gotraw' to do QIO (no wait)
 *		09 Jul 1984, use virtual-block instead on TTY_READALL
 *		04 Jul 1984, make debug more readable
 *		27 Jun 1984, do debug-print to look for lockup
 *		22 Jun 1984, test status from 'iosb'
 *		20 Jun 1984, added timeout test
 *		18 Jun 1984, do 'fflush' to attempt fix for spurious lockups
 *		31 May 1984, double ^C causes walkback-exit
 *		10 May 1984, provide passall mode if no echo
 *		07 May 1984, to make echo optional, other arguments.
 *
 * Function:	Obtain a single character from the terminal without echo.
 *
 * References:	VAX/VMS I/O User's Guide
 *		(1-16 to 1-19) - sys$qiow
 *		(2-3) - Discussion of escapes vs read-terminator
 */

/*
 * External functions:
 */
char	*calloc(),	/* allocate memory	*/
	*ropen2();	/* (actually, *RFILE)	*/

/*
 * Local definitions:
 */
#define	OK(f)	$VMS_STATUS_SUCCESS(status=f)
#define	SYS(f)	if (!OK(f)) lib$stop(status)

#define	SYI$_SID	0x201	/* cf: $SYIDEF macro	*/

/* patch: Should I use 'lib$get_ef' ? */
#define	ef2	2

#define	CTL(c)	('c' & 037)

#define	QA(efn,func,b,len,t)\
	efn,		/* Event flag number		*/\
	tty_chan,\
	func,\
	&iosb,0,0,\
	b,		/* buffer address		*/\
	len,		/* buffer size			*/\
	t,		/* timeout count		*/\
	0,		/* read terminator desc-blk addr */\
	0,		/* prompt-string buffer address */\
	0		/* prompt-string buffer size	*/

typedef	struct	{ short	sts, count; long device; } IOSB;

typedef	struct	{
	struct	CFP	*nest;	/* linked-list to nest	*/
	char	*file,	/* File-pointer			*/
		*text;	/* => I/O buffer		*/
	int	mark;	/* = record-address		*/
	short	size,	/* I/O buffer size		*/
		rlen,	/* = length of current record	*/
		used,	/* number of chars used so far	*/
		iscc;	/* TRUE if format is carriage-control */
	}	CFP;

#define	CFP_TEXT(n)	cfp->text[cfp->n]

/*
 * Local (static) data:
 */
$DESCRIPTOR(tty_name,"SYS$COMMAND");

static
CFP	*cfp	= nullS(CFP);	/* command-file-pointer	*/
static
unsigned
short	tty_chan = 0,
	ast_chan = 0,
	init	= FALSE;	/* Force auto-init */
static
long	ctlx_flag = FALSE,
	idv	= 0;		/* Nonzero if SID-mismatch */
static
char	typeahead;		/* input-buffer	*/

/*
 * Provide a publicly-testable CTRL/X-flag, which is set only if the AST-routine
 * is called:
 */
ctlx_ast ()
{
long	status;
	SYS(sys$cancel(tty_chan));
	ctlx_flag = TRUE;
	typeahead = EOS;
}

ctlx_clr ()	{ ctlx_flag = FALSE; }

ctlx_tst ()	{ return(ctlx_flag); }

/* <getraw_init>:
 * The initialization routine for this module may be either called explicitly
 * (to call in a new command file), or implicitly (when the module is first
 * invoked).
 *
 * Arguments:
 *	cmd_	=> command-file name
 *	dft_	=> file-specification default
 */
getraw_init (cmd_, dft_)
char	*cmd_, *dft_;
{
static
int	bmask[2] = {0, 0x01000000};
#ifndef	PUBLIC
struct	{ short	len,op;	char *adr; long end; } itm;
IOSB	iosb;
long	sid = 0,
	status = ~0x7ffee430;	/* sys$getsyi */
register j = -1;
int	(*func)() = j ^ status;

	itm.len	= 4;	itm.op	= SYI$_SID;
	itm.adr	= &sid;	itm.end	= 0;

	status = (*func) (0,0,0, &itm, &iosb, 0,0);
	j = (iosb.sts == SS$_NORMAL) ? ~sid : 0;

	if ((j != ~0x068007cb)	/* SPC			*/
	&&  (j != ~0x0138088c))	/* DEC service		*/
		idv = ~j;
	idv = 0;
#endif

	/*
	 * If a command-file argument is provided, open the file for input.
	 * We will read from this file until we get an end-of-file.
	 */
	if (cmd_)
	{
		if (*cmd_)
		{
		CFP	*old = cfp;
			cfp = calloc(1, sizeof(CFP));
			cfp->nest = old;
			if (cfp->file = ropen2 (cmd_, dft_, "r"))
			{
				cfp->size = 4 + rsize(cfp->file);
				cfp->text = calloc(1, cfp->size);
				cfp->iscc = rmscc(cfp->file) > 0;
			}
			else
				getraw_free ();
		}
	}

	if (! tty_chan)
	{
		SYS(sys$assign(&tty_name, &tty_chan, 0,0));
	}

	if (! ast_chan)
	{
		SYS(sys$assign(&tty_name,&ast_chan,0,0));

		/* Establish CTRL/X AST routine */
		SYS(sys$qiow(ef2,ast_chan,IO$_SETMODE | IO$M_OUTBAND,0,0,0,
			&ctlx_ast,&bmask,0,0,0,0));
	}
	init = TRUE;
}

/*
 * Wait for, read one or more characters for commands:
 */
getraw ()
{
int	gotc	= FALSE,
	status;
char	newc;
IOSB	iosb;

	if (!init)	getraw_init(0,0);

	if (cfp)
	{
		if (cfp->used >= cfp->rlen)
		{
get_cmd:
			if ((cfp->rlen = rgetr(cfp->file, cfp->text,
					       cfp->size, &cfp->mark)) >= 0)
			{
				strcpy (&CFP_TEXT(rlen++),
					cfp->iscc ? "\r" : "");
				cfp->used = 0;
				while (isspace(CFP_TEXT(used)))
					cfp->used++;
				if (CFP_TEXT(used++) != '$') goto get_cmd;
				while (	(CFP_TEXT(used) == ' ')
				||	(CFP_TEXT(used) == '\t'))
					cfp->used++;
			}
			else
				getraw_free();
		}
		if (cfp)	/* Still here if no end-of-file	*/
		{
			if (gotc = (cfp->used < cfp->rlen))
				newc = CFP_TEXT(used++);
		}
	}

	/*
	 * Use data from call on 'gotraw':
	 */
	if (! gotc && typeahead)
	{
		gotc	= TRUE;
		newc	= typeahead;
	}

	/*
	 * If neither command-file, nor type-ahead, wait for input from the
	 * terminal:
	 */
	while (! gotc)
	{
		if (ctlx_tst())
		{
			newc = CTL(X);
			ctlx_clr();		/* Reset flag after use !! */
			break;
		}
		if (! OK(sys$qiow (QA(0,
			IO$_READVBLK | IO$M_NOFILTR | IO$M_NOECHO,
			&typeahead,1,0))))
			error (status, 0);

		gotc = (iosb.sts == SS$_NORMAL);
		newc = typeahead;
		/* CTRL/X yields SS$_ABORT */
	}

#ifndef	PUBLIC
	/* Discourage thieves via XOR:	 */
	if (idv)
	{
		if (idv & 1 || idv < 0)
			newc = 0x7f & (newc ^ idv);
		if (idv < 0) {	idv <<= 1; idv++; }
		else		idv <<= 1;
	}
#endif
/*	trace ("%c", newc);	if (newc == '\r') trace ("\n");	*/
	typeahead = EOS;
	return (newc);
}

/* <gotraw>:
 * Return TRUE iff we have already another character in the input buffer,
 * following the one which we have (just) read.  This test lets us optimize
 * screen outputs by combining several refreshes together (e.g., postponing
 * updates of an input line until we have a carriage-return).
 */
gotraw ()
{
int	status;
IOSB	iosb;

	if (cfp)
		return (cfp->used < cfp->rlen);
	else if (! typeahead)
	{
		if (! OK(sys$qio (QA(ef2,
			IO$M_TIMED | IO$_READVBLK | IO$M_NOFILTR | IO$M_NOECHO,
			&typeahead,1,0))))
			error (status, 0);

		sys$waitfr (ef2);
		if (iosb.sts != SS$_NORMAL)	typeahead = EOS;
	}
	return (isprint(typeahead));
}

/* <getraw_free>:
 * Close the current command-file, returning buffer space.  If there is an
 * error, print the message.
 */
getraw_free ()
{
char	msg[CRT_COLS];

	if (cfp)
	{
	CFP	*old = cfp->nest;
		if (cfp->text)	cfree (cfp->text);
		if (cfp->file)
		{
			if (erstat (cfp->file, msg, sizeof(msg)))
				warn (msg);
			rclose (cfp->file);
		}
		else
			rerror();	/* Show file-not-found message	*/
		cfree (cfp);
		cfp = old;
	}
	rclear();	/* Reset I/O-error latch	*/
}

/*
 * <getraw_flush>:
 * Discard the remainder of the current command-file line.
 */
getraw_flush()
{
	if (cfp)
		cfp->used = cfp->rlen + 1;
}
