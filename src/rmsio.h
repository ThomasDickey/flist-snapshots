/*
 * Title:	rmsio.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	15 Sep 1984
 * Last update:	23 Feb 1985, added 'sys', 'RMS_STUFF' defines
 *		19 Oct 1984, added 'RMSIO' define
 *
 *	Define an intercept for 'stdio' stuff so that I can compile 'more'
 *	to point to 'rmsio', without widespread source changes.
 */

#define	RMSIO	RMSIO

#define	BUFSIZ	512
#define	_NFILE	?

#define	NULL		0
#define	FILE		char	/* patch */
#define	EOF		(-1)
#define	TRUE		1
#define	FALSE		0

#define	fopen	ropen
#define	fgetr	rgetr
#define	ftell	rtell
#define	fseek	rseek
#define	fclose	rclose
#define	perror	rerror

#define	freopen	?

FILE	*fopen();
long	ftell();

#define	sys(f)	status = f; if (!$VMS_STATUS_SUCCESS(status))

#define	RMS_STUFF\
	struct	FAB	fab;\
	struct	NAM	nam;\
	long	status;\
	char	esa[NAM$C_MAXRSS],	rsa[NAM$C_MAXRSS]
