#include	"atrdef.h"
#include	"dqfdef.h"
#include	"fchdef.h"
#include	"fibdef.h"

/*
 * Title:	fibdef.h
 * Reference:	(Chapter 2 -- ACP - QIO Interface)
 *
 * Patch:	The reference is not so good; this may suffice until I learn
 *		Bliss-32.
 *
 * Created:	02 Nov 1984
 * Last update:	15 Jun 1985,	typed atr-buffer address as 'char*'
 *		13 Dec 1984, 	added IOSB
 */

#define	byte	unsigned char
#define	word	short

typedef	struct	{
	union	{
		byte	u1a[4];
		long	u1b;
		}	u1;
#define	fib$l_acctl	u1.u1b		/* file-access control bits	*/
#define	fib$b_wsize	u1.u1a[3]	/* size of file window to map disk file */

	word	fib$w_fid[1];		/* 3-word file identification	*/
#define	fib$w_fid_num	fib$w_fid[0]	/* file number			*/
	word	fib$w_fid_seq;		/* file sequence number		*/
	byte	fib$b_fid_rvn;		/* relative volume number	*/
	byte	fib$b_fid_nmx;		/* file-number extension (disk)	*/

	word	fib$w_did[1];		/* 3-word directory identification */
#define	fib$w_did_num	fib$w_did[0]	/* file number			*/
	word	fib$w_did_seq;		/* file sequence number		*/
	byte	fib$b_did_rvn;		/* relative volume number	*/
	byte	fib$b_did_nmx;		/* file-number extension (disk)	*/

	long	fib$l_wcc;		/* wild-card context		*/
	word	fib$w_nmctl;		/* directory-search name-flags	*/

	word	fib$w_exctl;
	long	fib$l_exsz;
#define	fib$w_cntrlfunc	fib$w_exctl
#define	fib$l_cntrlval	fib$l_exsz

	long	fib$l_exvbn;		/* starting virtual block number, truncation */
	byte	fib$b_alopts;		/* allocation-placement options	*/
	byte	fib$b_alalign;		/* interpretation mode of 'w_alloc' */

	word	fib$w_loc_fid[1];	/* (actually, 3-words)		*/
#define	fib$w_loc_num	fib$w_loc_fid[0]
/*	word	fib$w_loc_num;		** related file number		*/
	word	fib$w_loc_seq;		/* related file sequence number	*/
	byte	fib$b_loc_rvn;		/* related file/placement RVN	*/
	byte	fib$b_loc_nmx;		/* related file number extension*/
	long	fib$l_loc_addr;		/* Placement LBN, cylinder, or VBN */
#define	fib$w_alloc	fib$w_loc_fid[0]

	word	fib$w_verlimit;		/* version limit of directory entry */
	word	unused;
	} FIB;

/*
 * Attribute Control Block.
 * --may use an array of up to 14 of these.
 */
typedef	struct	{
	word	atr$w_size;	/* size of data-area	*/
	word	atr$w_type;	/* identifies attribute to be read/written */
	char	*atr$l_addr;	/* address of data-area	*/
	}	ATR;

/*
 * ACP QIO Record Attributes Area
 */
typedef	struct	{
	byte	fat$b_rtype;
	byte	fat$b_rattrib;
	word	fat$w_rsize;
	long	fat$l_hiblk;
	long	fat$l_efblk;
	word	fat$w_ffbyte;
	byte	fat$b_bktsize;
	byte	fat$b_vfcsize;
	word	fat$w_maxrec;
	word	fat$w_defext;
	word	fat$w_gbc;
	word	reserved[3];
	word	unused;
	word	fat$w_versions;
	}	FAT;

/*
 * ACP Disk Quotas
 */
typedef	struct	{
	long	dqf$l_flags;		/* operation flags	*/
	word	dqf$w_uic[2];		/* User identification	*/
	long	dqf$l_usage;		/* current usage	*/
	long	dqf$l_permquota;	/* permanent quota	*/
	long	dqf$l_overdraft;	/* overdraft limit	*/
	}	DQF;

/*
 * I/O Status Block:
 */
typedef	struct	{
	short	stat,
		unused;
	long	jobstat;
	}	IOSB;
