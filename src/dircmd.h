/* $Id: dircmd.h,v 1.3 1995/05/28 00:24:04 tom Exp $
 *
 * public interface of dircmd.c (and functions tabulated there)
 */

#ifndef	DIRCMD_H
#define	DIRCMD_H

#include "dirent.h"
#include "dircmd2.h"

extern	tDIRCMD(flcols);	/* Alter the display format		*/
extern	tDIRCMD(flcols_left);
extern	tDIRCMD(flcols_right);
extern	tDIRCMD(flcols_width);
extern	tDIRCMD(flcols_132);
extern	tDIRCMD(flcopy);	/* Copy/append files			*/
extern	tDIRCMD(fldlet);	/* Delete or purge a file		*/
#ifdef	DEBUG
extern	tDIRCMD(fldump);	/* Dump data structures			*/
#endif
extern	tDIRCMD(fledit);	/* Edit/inspect file or directory	*/
extern	tDIRCMD(flescp);	/* Escape from FLIST temporarily	*/
extern	tDIRCMD(flfind);	/* Search for file-entry		*/
extern	tDIRCMD(flmore);	/* BROWSE a file (type it)		*/
extern	tDIRCMD(flnoid);	/* Enqueue a process, no wait		*/
extern	tDIRCMD(flpage);	/* Do scrolling /TOP, /END, etc.	*/
extern	tDIRCMD(flprot);	/* Set/clear protection code		*/
extern	tDIRCMD(flquit);	/* Process (optional) multi-level quit	*/
extern	tDIRCMD(flread);	/* Read (or re-read) entries in list	*/
extern	tDIRCMD(flrnam);	/* Rename a file			*/
extern	tDIRCMD(flscan);	/* Scan 'filelist[]' for deletions	*/
extern	tDIRCMD(flset_date);	/* Set date-display flags		*/
extern	tDIRCMD(flset_hold);	/* Set HOLD-flag			*/
extern	tDIRCMD(flset_mark);	/* Set mark (selection) flag		*/
extern	tDIRCMD(flshow);	/* Process "SHOW"/"?" commands		*/
extern	tDIRCMD(flsort);	/* Process sort-commands		*/
extern	tDIRCMD(not_impl);	/* patch				*/

extern	char	*dirarg (DCLARG **dcl__, int curfile, char *argstr, char *command, int omit);
extern	int	dircmd_dirflg (int flag);
extern	VCMD2*	dircmd_full (int cmdnum);
extern	int	dircmd_vcmd2 (char *cmd_, int len);
extern	int	dircmd_ask (int curfile, char *msg_);
extern	void	dircmd_init (void);
extern	int	dircmd_select (int val);
extern	void	dircmd (void);

#endif	/* DIRCMD_H */
