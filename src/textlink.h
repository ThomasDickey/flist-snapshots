/*
 * Title:	textlink.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	06 Dec 1984
 * Last update:	04 Jul 1985, added 'refs' mask
 *		06 Dec 1984
 *
 *	Define a structure of linked-lists with text.
 */

typedef	struct	{
	char	*next;		/* => next link in list		*/
	unsigned
	char	refs;		/* bitmask to track reference	*/
	char	text[1];	/* string, with trailing null	*/
	} TEXTLINK;
