/* $Id: dclarg.h,v 1.4 1995/03/19 01:45:04 tom Exp $
 *
 *	Define structure returned by DCL/argument parser 'dclarg'
 */

#ifndef	DCLARG_H
#define	DCLARG_H

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

extern	DCLARG	*argvdcl (int argc, char *argv[], char *dft_, int cmd_arg);
extern	DCLARG	*dclarg (char *inp_, char *dft_, int cmd_arg, int cpy_dft);
extern	DCLARG	*dclarg_text (DCLARG *this_, DCLARG *last_, char *s_, int uc);
extern	char	*dclinx (DCLARG *dcl_, int mfld, int sfld);
extern	DCLARG	*dclinx2 (DCLARG *dcl_, int mfld, int sfld);
extern	char	*dclarg_keyw (char *c_);
extern	char	*dclarg_spec (char *i_, char *also);

#define	isopt(c) ((c == '/') || (c == '='))	/* Begins an option?	*/
#define	isopt2(c) ((c == '=') || (c == ':'))	/* Begins option-value?	*/

#endif	/* DCLARG_H */
