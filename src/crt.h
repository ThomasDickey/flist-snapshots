/*
 * Title:	crt.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	24 Aug 1984, broke out of 'flist.h'
 * Last update:	24 Aug 1984
 *
 *	Buffer limits and other special things needed to interface with the
 *	'crt.c' screen-handling module.
 */

#define	ishigh(c)	(0x80 & c)	/* Test highlighting flag	*/
#define	tohigh(c)	(0x80 | c)	/* Set highlighting flag	*/

#define	max(a,b)	(((a) > (b)) ? (a) : (b))
#define	min(a,b)	(((a) < (b)) ? (a) : (b))

/*
 * Buffer limits:
 */
#define	CRT_COLS	133	/* Length of screen line-buffers	*/
#define	CRT_LINES	256	/* Allow a lot of lines			*/
