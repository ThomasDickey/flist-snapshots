/* $Id: dircmd.h,v 1.1 1995/03/18 23:31:50 tom Exp $
 *
 * public interface of dircmd.c (and functions tabulated there)
 */

#ifndef	DIRCMD_H
#define	DIRCMD_H

#include "dircmd2.h"
#include "dclarg.h"

extern	tDIRCMD(flcols),	/* Alter the display format		*/
extern	tDIRCMD(flcols_left),
extern	tDIRCMD(flcols_right),
extern	tDIRCMD(flcols_width),
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
extern	tDIRCMD(flset_date),	/* Set date-display flags		*/
extern	tDIRCMD(flset_hold),	/* Set HOLD-flag			*/
extern	tDIRCMD(flset_mark);	/* Set mark (selection) flag		*/
extern	tDIRCMD(flshow);	/* Process "SHOW"/"?" commands		*/
extern	tDIRCMD(flsort);	/* Process sort-commands		*/
extern	tDIRCMD(not_impl);	/* patch				*/

#endif	/* DIRCMD_H */
