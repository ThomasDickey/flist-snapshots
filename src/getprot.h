/*
 * Title:	getprot.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	03 Jul 1984
 * Last update:
 *		04 Nov 1988, enlarged p_grp, p_mbm fields
 *
 *	Define bit-layout returned by 'getprot.c'
 */

typedef	struct	{
	unsigned short	p_mask;		/* protection mask	*/
	unsigned short	p_grp,		/* group code		*/
			p_mbm;		/* member code		*/
	} GETPROT;
