/*
 * Title:	bool.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	08-Aug-83
 * Last update:	11 Dec 1984, added SIZEOF, EOS
 *		11 Apr 84, removed 'struct' from nullS
 *		05 Apr-84, to added null-pointer def's
 */
#define	TRUE	1
#define	FALSE	0
#define	NOT	FALSE ==

typedef	int	bool;

#define	nullP(t)	((t *)0)
#define	nullS(t)	((t *)0)	/* K&R says 'struct', Unix not	*/

/* The most common null pointers: */
#define	nullC		nullP(char)
#define	nullINT		nullP(int)

#define	SIZEOF(array)	(sizeof(array)/sizeof(array[0]))

#define	EOS	'\0'
