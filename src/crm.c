/*static char *sccsid = "@(#)crypt.c	4.1 (Berkeley) 10/1/80";*/
/*
 *	A one-rotor machine designed along the lines of Enigma
 *	but considerably trivialized.
 *
 * Modified: 12 Nov 1984, adapted to run on VAX/VMS, using 'pipefunc'.
 */

#define ECHO 010
#include <stdio.h>
#include	<ctype.h>
#define ROTORSZ 256
#define MASK 0377
char	t1[ROTORSZ];
char	t2[ROTORSZ];
char	t3[ROTORSZ];
char	*getpass();

/*
 * You send it 10 bytes.
 * It sends you 13 bytes.
 * The transformation is expensive to perform
 * (a significant part of a second).
 */

char	*SortInit();

makekey (buf)
char *buf;
{
    int  j;
	char *c_,
         key[8],
         salt[2];

    for (j = 0; j < 8; j++)  key[j]  = buf[j];
    for (j = 0; j < 2; j++)  salt[j] = buf[j+8];
    c_ = SortInit (key, salt);
    for (j = 0; j < 13; j++) buf[j]  = *c_++;
}

setup(pw)
char *pw;
{
	int ic, i, k, temp;
	unsigned random;
	char buf[13];
	long seed;

	strncpy(buf, pw, 8);
	while (*pw)
		*pw++ = '\0';
	buf[8] = buf[0];
	buf[9] = buf[1];

	makekey(buf);

	seed = 123;
	for (i=0; i<13; i++)
		seed = seed*buf[i] + i;
	for(i=0;i<ROTORSZ;i++)
		t1[i] = i;
	for(i=0;i<ROTORSZ;i++) {
		seed = 5*seed + buf[i%13];
		random = seed % 65521;
		k = ROTORSZ-1 - i;
		ic = (random&MASK)%(k+1);
		random >>= 8;
		temp = t1[k];
		t1[k] = t1[ic];
		t1[ic] = temp;
		if(t3[k]!=0) continue;
		ic = (random&MASK) % k;
		while(t3[ic]!=0) ic = (ic+1) % k;
		t3[k] = ic;
		t3[ic] = k;
	}
	for(i=0;i<ROTORSZ;i++)
		t2[t1[i]&MASK] = i;
}

/*
 * Patch: This translation function should be re-done to do block I/O.
 */
static
int	_TRUE	= 1, _FALSE = 0,
	blocked,	/* Use blocked I/O (default: /NOB = old stuff)	*/
	M_mark,		/* seed value: tabs and spaces		*/
	P_flag,		/* TRUE if we propagate protection-code	*/
	D_flag;		/* TRUE if we propagate creation-date	*/
static
char	C_mark[80];	/* contents of marker-comment		*/

CryptFunc (ifile, ofile)
char	*ifile, *ofile;
{
register i, n1, n2;
int	j, numgot, mark;
char	buffer[1024];

	n1 = 0;
	n2 = 0;

	while ((numgot = rgetr(ifile, buffer, sizeof(buffer), &mark)) >= 0)
	{
		if (*C_mark && mark == 0)	CryptMark(ofile);
		for (j = 0; j < numgot; j++)
		{
			i = buffer[j];
			buffer[j] = t2[(t3[(t1[(i+n1)&MASK]+n2)&MASK]-n2)&MASK]-n1;
			n1++;
			if(n1==ROTORSZ) {
				n1 = 0;
				n2++;
				if(n2==ROTORSZ) n2 = 0;
			}
		}
		rputr (ofile, buffer, numgot);
	}
	return ( 1
		+(D_flag ? 2 : 0)	/* Propagate creation date ?	*/
		+(P_flag ? 0 : 4));	/* Propagate protection ?	*/
}

/*
 * Introduce a new first-line to avoid simple retracing to prior copies of
 * the translated file.
 */
CryptMark (ofile)
char	*ofile;
{
unsigned
char	m = (M_mark++) & 0xf;
char	bfr[132],
	*c_ = bfr, *d_ = C_mark, *e_;

	while (m)
	{
		if (m & 1)	*c_++ = '\t';
		else		*c_++ = ' ';
		m >>= 1;
		M_mark += *c_;	/* make it jump around a bit ! */
	}
	*c_++ = '/';	*c_++ = '*';	e_ = c_;
	while (*d_)
	{
		if (strncmp(d_, "_c_", 3) == 0)
		{
			*c_++ = '(';
			*c_++ = 'C';
			*c_++ = ')';
			d_ += 2;
		}
		else if (*d_ == '_')	*c_++ = ' ';
		else			*c_++ = *d_;
		if (!isalpha(*d_) && isalpha(d_[1]))
			d_[1] = _toupper(d_[1]);
		d_++;
	}
	*c_++ = *(--e_); *c_++ = *(--e_); *c_++ = '\n';	*c_ = 0;
	rputr (ofile, bfr, c_ - bfr);
	printf ("%.80s", bfr);
}

#include	"main.h"
#include	"dclarg.h"
#include	"dclopt.h"

static
char	keybuf[10];

#define	P	(char *) &
static
DCLOPT	opts[] = {
	{"key",		"",	0,	keybuf,	sizeof(keybuf),	1,	001},
	{"protect", P _TRUE,	0,    P P_flag,	sizeof(P_flag),	1,	002},
	{"date",    P _TRUE,	0,    P D_flag,	sizeof(D_flag),	1,	004},
	{"mark",    P _FALSE,	0,    P M_mark, sizeof(M_mark),	1,	010},
	{"copymark",	"",	0,    P C_mark, sizeof(C_mark),	1,	020},
	{"blocked", P _TRUE,	0,    P blocked,sizeof(blocked),1,	040}
	};

main(argc, argv)
char *argv[];
{
DCLARG	*arg_ = argvdcl (argc, argv, "*.*;", 0);
char	*k_,
	msg[132];

	if (dclchk (arg_, msg))				error(0,msg);
	if (dclopt (msg, arg_, &opts, sizeof(opts)))	error(0,msg);
	if (!dclinx (arg_, 1, 0))			error(0,"Must give arg");

	if (!keybuf[0])
	{
		strcpy (keybuf, k_ = getpass("Enter key:"));
		cpyblk (k_, 0, 8);	/* destroy 'getpass's copy	*/
	}
	strlcpy (keybuf, keybuf);	/* convert to monocase		*/
	setup(keybuf);

	pipefunc (arg_, CryptFunc, blocked);
}

warn(msg)
char *msg;
{
	printf("?? %s\n", msg);
	exit(0);
}
