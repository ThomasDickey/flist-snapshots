/*
 * Title:	textlink.h
 * Author:	Thomas E. Dickey
 * Created:	06 Dec 1984
 * Last update:	04 Jul 1985, added 'refs' mask
 *		06 Dec 1984
 *
 *	Define a structure of linked-lists with text.
 */

#ifndef	TEXTLINK_H
#define	TEXTLINK_H

#define	TEXTLINK	struct _textlink

TEXTLINK {
	TEXTLINK *	next;		/* => next link in list		*/
	unsigned char	refs;		/* bitmask to track reference	*/
		char	text[1];	/* string, with trailing null	*/
	};

#endif/*TEXTLINK_H*/
