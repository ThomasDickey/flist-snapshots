/*
 * Title:	flist.h - misc
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	04 May 1984
 * Last update:	04 May 1985, removed qCMD (restructuring), sCMD
 *		28 Aug 1984, added 'qCMD()'
 *		24 Aug 1984, broke out 'crt.h'
 *		14 Aug 1984, moved DELETED to 'dirent.h'
 *		20 Jun 1984, added 'is_sCMD()'
 *		21 May 1984
 */

#include	"bool.h"
#include	"crt.h"

#define	CTL(c)	(037 & 'c')
#define	is_PAD(c)	(c >= 256 && c < 512)
