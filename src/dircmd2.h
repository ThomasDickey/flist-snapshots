/*
 * Title:	dircmd2.h
 * Author:	Thomas E. Dickey
 * Created:	28 Jun 1984
 * Last update:	18 Sep 1985, added v_NAME
 *		27 Jul 1985, permit wildcard-rename (v_1_1)
 *		07 May 1985, added support for non-DCL syntax (/columns)
 *		14 Mar 1985, no options in 'RENAME'
 *		08 Mar 1985, permit filename-argument in 'PROTECT'
 *		22 Dec 1984, added 'SET' flag.
 *		15 Dec 1984, added flag to support 'cpy_dft' argument of 'dclarg'
 *		17 Oct 1984, permit wildcard in 1-1
 *		28 Aug 1984, added '.v_func' to VCMD
 *		04 Aug 1984, added 'cmdnum' tests
 *
 *	Define command constraints for DCL-commands known to FLIST.
 */

#define	v_1_IN		0001	/* Exactly one input filespec needed	*/
#define	v_M_IN		0002	/* Multiple input filespecs permitted	*/
#define	v_W_IN		0004	/* Wildcard permitted in input specs	*/

#define	v_1_OUT		0010	/* Exactly one output filespec needed	*/
#define	v_M_OUT		0020	/* Multiple output filespecs permitted	*/
#define	v_W_OUT		0040	/* Wildcard permitted in output specs	*/

#define	v_OPTS		0100	/* Options permitted in command		*/
#define	v_OMIT		0200	/* Omit implicit use of current entry	*/
#define	v_FREE		0400	/* Permit in/out filespecs to be omitted*/

#define	v_COPY		01000	/* Don't propagate path-name to output	*/
#define	v_SET		02000	/* Permit 'SET' before this keyword	*/

#define	v_nonDCL	04000	/* non-DCL (e.g., leading '?')		*/
#define	v_ARGS		010000	/* ...permit arguments if non-DCL	*/
#define	v_NAME		020000	/* Command explicitly for current entry	*/

/*
 * The flags 'v_1_IN', 'v_M_IN' are exclusive, as are 'v_1_OUT', 'v_M_OUT'.
 * The following combinations are used in 'dircmd' to drive 'dirarg' and
 * 'dirchk' in simple parameter tests.  A typical command is noted beside:
 */
#define	v_1	(v_1_IN + v_OPTS)			/* (browse)	*/
#define	v_1_1	(v_1_IN + v_W_IN  + v_1_OUT + v_W_OUT)	/* (rename)	*/
#define	v_M_1	(v_M_IN + v_W_IN  + v_1_OUT + v_OPTS + v_COPY)
#define	v_M	(v_M_IN + v_W_IN  + v_OPTS)		/* (print)	*/
#define	v_M0	(v_M_IN + v_W_IN)			/* (delete)	*/

#define	v_1a	(v_1_IN + v_W_IN  + v_OMIT)		/* (find)	*/
#define	v_1b	(v_1_IN + v_W_IN  + v_OPTS + v_FREE)	/* (protect)	*/
#define	v_1c	(v_M_IN + v_W_IN  + v_OMIT + v_FREE)	/* (read)	*/

/*
 * Structure for 'dircmd' commands which require arguments, or permit a
 * filespec other than the current entry to be used:
 */
typedef	struct	{
	char	*v_full;	/* full text of command			*/
	int	v_len,		/* abbreviation length			*/
		(*v_func)(),	/* No passback, special			*/
		v_mode;		/* file count bits (e.g., v_1_IN)	*/
	char	*v_dfts;	/* default string			*/
	} VCMD2;

/*
 * Define tests on 'cmdnum' (the index into VCMD/VCMD2 tables) to permit
 * program to know about third-type (non-FLIST commands).
 */
#define	NOARG_CMD	(-1)
#define	EXTRN_CMD	(-2)
#define	ERROR_CMD	(-3)

#define	isDIRED_CMD(x)	((x) >= 0)
#define	isNOARG_CMD(x)	((x) == NOARG_CMD)
#define	isEXTRN_CMD(x)	((x) == EXTRN_CMD)
