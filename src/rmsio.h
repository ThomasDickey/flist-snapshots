/*
 * Title:	rmsio.h
 * Author:	Thomas E. Dickey
 * Created:	15 Sep 1984
 * Last update:	23 Feb 1985, added 'sys', 'RMS_STUFF' defines
 *		19 Oct 1984, added 'RMSIO' define
 *
 *	Define an intercept for 'stdio' stuff so that I can compile 'BROWSE'
 *	to point to 'rmsio', without widespread source changes.
 */

#define	RMSIO	RMSIO

#define	BUFSIZ	512
#define	_NFILE	?

#ifndef	NULL
#define	NULL		0
#endif

#undef	FILE
#define	FILE		char	/* patch */

#ifndef	EOS
#define	EOF		(-1)
#endif

#ifndef	TRUE
#define	TRUE		1
#define	FALSE		0
#endif

#define	fopen	ropen
#define	fgetr	rgetr
#define	ftell	rtell
#define	fseek	rseek
#define	fclose	rclose
#define	perror	rerror

#define	freopen	?

extern	FILE	*fopen();
extern	long	ftell();

#define	sys(f)	status = f; if (!$VMS_STATUS_SUCCESS(status))

#define	RMS_STUFF\
	struct	FAB	fab;\
	struct	NAM	nam;\
	long	status;\
	char	esa[NAM$C_MAXRSS],	rsa[NAM$C_MAXRSS]
