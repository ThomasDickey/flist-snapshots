/*
 * Title:	dclopt.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	11 Jul 1984
 * Last update:	14 Jan 1985, to add 'opt_ini2'
 *
 *	Define structures which support the DCL-option decoder 'dclopt.c'
 */

typedef	struct	{
	char	*opt_name,	/* => full option name			*/
		*opt_init,	/* => initial value for area		*/
		*opt_ini2,	/* => default, if no value given	*/
		*opt_area;	/* => buffer area for value		*/
	unsigned
	short	opt_size,	/* 1=flag, 2=value, 3+=string		*/
		opt_abbr,	/* minimum length of abbreviation	*/
		opt_flag;	/* bit-vector for disjoint option test	*/
	} DCLOPT;
