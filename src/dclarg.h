/*
 * Title:	dclarg.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	28 May 1984
 * Last update:	05 Feb 1985, added 'dclinx2'
 *		26 Dec 1984, added '.dcl$l_fnb' to reduce re-parsing, and other
 *			     '.dcl$b_???' stuff from NAM-block.
 *		14 Oct 1984, added 'isopt2'
 *		26 Jun 1984, added '_from', '_size' components
 *
 *	Define structure returned by DCL/argument parser 'dclarg'
 */

typedef	struct	{
	struct	DCLARG	*dcl_next;	/* => next item in list		*/
	char	*dcl_text;		/* => string contents		*/
	unsigned dcl_stat,		/* Status of entry		*/
		dcl$l_fnb;		/* (NAM) filename status bits	*/
	char	dcl_mfld,		/* Main-field index (by ' ')	*/
		dcl_sfld,		/* Sub-field index (by ',')	*/
		dcl_from,		/* Beginning index in string	*/
		dcl_size,		/* ...number of characters	*/
		dcl$b_node,		/* node-name string length	*/
		dcl$b_dev,		/* device string length		*/
		dcl$b_dir,		/* directory string length	*/
		dcl$b_name,		/* file name string length	*/
		dcl$b_type,		/* file type string length	*/
		dcl$b_ver;		/* file version string length	*/
	}	DCLARG;

DCLARG	*dclarg(),
	*argvdcl(),
	*dclinx2();
char	*dclinx();			/* => name in DCLARG-list	*/

#define	isopt(c) ((c == '/') || (c == '='))	/* Begins an option?	*/
#define	isopt2(c) ((c == '=') || (c == ':'))	/* Begins option-value?	*/
