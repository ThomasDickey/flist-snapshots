#ifndef NO_IDENT
static char *Id = "$Id: dirpath.c,v 1.4 1995/02/19 18:24:39 tom Exp $";
#endif

/*
 * Title:	dirpath.c
 * Author:	Thomas E. Dickey
 * Created:	27 Jul 1984
 * Last update:
 *		19 Feb 1995, prototyped
 *		12 Sep 1985, also account for implied trailing '.' in pathname
 *			     collating.
 *		10 Sep 1985, account for trailing '.' in filename-field.
 *		22 Jul 1985, added 'dirpath_add'
 *		20 Jul 1985, moved some debug-code to 'fldump'
 *		13 Jul 1985, added 'filelink' init/release
 *		06 Jul 1985, corrected references to 'namelist' as 'nameheap'-
 *			     argument.  Added calls on 'nameheap_set' and
 *			     'nameheap_clr'.  Make 'pathlist' a pointer to a
 *			     similar, structured heap.
 *		11 Mar 1985
 *		09 Mar 1985, added 'dirpath_rename' code'
 *		01 Feb 1985, move read-list support to 'dirread' module.
 *		06 Dec 1984, add "namelist"
 *		02 Sep 1984, use "import()"
 *
 * Function:	This module maintains for 'dirent' (FLIST entries) the
 *		linked list 'pathlist':
 *
 *		pathlist is a sorted list of all (full) pathnames for the
 *			entries in 'filelist[]', obtained as a by-product of
 *			the SYS$SEARCH process.  Pathnames are stored in this
 *			list to provide faster sorting (by key, rather than
 *			string), and to reduce the amount of storage used.
 *		readlist is an unsorted list of all (full) filespecs which are
 *			used to drive the SYS$SEARCH process.  It is used
 *			mainly to provide a re-read facility (the READ command,
 *			with no arguments).  (See: 'dirread').
 *		namelist is a sorted list of all filename and filetype strings.
 *			It is used because VMS 4.0 provides for long filenames
 *			(up to 39 characters in name and/or type).  By using
 *			the dictionary approach we can also compare the FILENT
 *			data for path+name+type+version easily since the string
 *			pointers are unique.
 *		filelink is a sorted list of all FILENT blocks (file data)
 *			known to FLIST.  We keep it sorted so that when we do a
 *			SYS$SEARCH, we keep the list-search time down; we need
 *			only search from the last insert/update position.  We
 *			init/release the list contents here because the other,
 *			related (pathlist, namelist) linked lists are.
 *
 *		The string-storage allocation for 'readlist' and for 'namelist'
 *		is performed in 'nameheap', since their use requires only a
 *		character string.  The 'pathlist' requires a sorting-key, and
 *		is maintained in this module.
 *
 * Entry:	dirpath_add:	augment reference mask for given 'pathlist' entry.
 *		dirpath_init:	Initialize the linked-lists
 *		dirpath_free:	De-allocate the linked-lists
 *		dirpath_rename:	Rename a path
 *		dirpath_sort:	Append a new pathspec to 'pathlist'.
 */

#include	<stdlib.h>
#include	<string.h>

#include	"flist.h"
#include	"dirent.h"
#include	"strutils.h"

import(filelink);
import(namelist);
import(pathlist);

char	*nameheap();		/* => allocated string storage	*/

#define	SORT(P,key) for (P=pathlist, key=0; P;\
			P->path_sort = key++, P = P->path_next)

/* <dirpath_add>:
 * Augment the given 'pathlist' entry, ensuring that it will be referenced at
 * other levels than the current one, given an appropriate refs-mask.
 */
dirpath_add (refs, p)
int	refs;
PATHNT	*p;
{
	p->path_refs |= refs;
	nameheap_add (refs, p->path_trim);
	nameheap_add (refs, p->path_text);
}

/* <dirpath_init>:
 */
dirpath_init (level)
int	level;
{
	if (level <= 1)
	{
		pathlist = nullC; 	/* (no paths in list yet)	*/
		namelist = nullC;	/* (no items in name-list)	*/
		filelink = nullC;	/* (no items in file-linked-list)*/
	}
	nameheap_set (level);
}

/* <dirpath_free>:
 * Release storage used only by the level from which we are exiting, recompact
 * the pathname sorting keys.
 */
dirpath_free (level)
int	level;
{
PATHNT	*P;
int	key;

	nameheap_clr (level, &pathlist);
	nameheap_clr (level, &namelist);
	nameheap_clr (level, &filelink);
	SORT(P,key);
}

/* <dirpath_sort>:
 * See if the current path is found in the list.  If not, put it in.
 * Keep the list sorted, so that pathname-sorting can be done by index.
 *
 * Sorting VMS pathnames is complicated by their syntax.  The collating order
 * of "]" and "." is the reverse of a "normal" directory listing.  To get
 * around this, change the last character of each pathname entry to a space.
 *
 * Returns:	A pointer to the PATHNT structure which holds the pathspec
 *		for the new entry.
 */
PATHNT	*dirpath_sort (esa, len)
char	esa[];		/* (expanded string from sys$parse)	*/
int	len;
{
PATHNT	*newP, *oldP, *nxtP;
int	cmp;
char	text	[MAX_PATH],
	trim	[MAX_PATH];

	if (len < 1)		len = 1;
	if (len >= MAX_PATH)	len = MAX_PATH-1;

	strncpy (text, esa, len);	text[len] = '\0';
	strcpy  (trim, text);		strcpy  (&trim[len-1], ".");

	for (newP = pathlist, oldP = 0;
		newP;
			oldP = newP, newP = newP->path_next)
	{
		cmp = strcmp (trim, newP->path_trim);
		if (cmp == 0)		goto path;
		else if (cmp < 0)	break;
	}

	nxtP = calloc (1, sizeof(PATHNT));
	if (oldP)
		oldP->path_next = nxtP;
	else
		pathlist  = nxtP;
	nxtP->path_next = newP;
	nxtP->path_text = nameheap(text, len, &namelist);
	nxtP->path_trim = nameheap(trim, len, &namelist);
	newP = nxtP;

	/* Update sort-key after each insertion: */
	SORT(nxtP,cmp);
path:	newP->path_refs |= nameheap_ref();
	return (newP);
}

/* <dirpath_rename>:
 * We are given the FILENT definitions for a new- and old-name of a renamed
 * directory.  Determine if there are any entries which used the old-name
 * in their path.  If so, determine the new path-text component, and move
 * the PATHNT data to the new position in the linked-list.  Finally, make
 * a new set of sort-keys.
 */
dirpath_rename (znew, zold)
FILENT	*znew, *zold;
{
PATHNT	*P, *P0, *Q, *Q0, *R, *R0, *t;
int	changed	= FALSE,
	oldlen,
	newlen,
	len;
char	c,
	bfr	[MAX_PATH],
	newpath	[MAX_PATH],
	oldpath	[MAX_PATH];

	/* Compute the beginning of paths through the old/new directory-names,
	   up to (but not including) the "." or "]": */
	oldlen = dirpath_make (oldpath, zold);
	newlen = dirpath_make (newpath, znew);

	/* Search the path-list for things to change: */
	for (P = pathlist; P; P = P->path_next)
	{
		if (strlen(P->path_text) <= oldlen)		continue;
		c = P->path_text[oldlen];
		if (c != '.' && c != ']')			continue;
		if (strncmp (oldpath, P->path_text, oldlen))	continue;

		strcpy (bfr, newpath);
		strcpy (&bfr[newlen], &P->path_text[oldlen]);
		len = strlen(bfr);
#define	ADJ(p)	nameheap_add(P->path_refs,\
			P->p = nameheap(bfr,len,&namelist));
		ADJ(path_text);
		bfr[len-1] = ' ';
		ADJ(path_trim);
		changed = TRUE;
	}

	/*
	 * If we altered any paths, we must now go back and resort the
	 * list of paths.  The links themselves must remain in the same
	 * memory-address, so we alter the linkages:
	 */
	if (changed)
	{
#define	loop(p1,p0,x1,x0) for (p1=x1,p0=x0; p1; p0=p1, p1 = p1->path_next)
#define	xch(p,q)	{t=p; p=q; q=t;}

	    loop (P,P0, pathlist, 0)
	    {
		R = P;		/* Assume current position is min */
		R0 = P0;
		loop (Q,Q0, P->path_next, P)
		{
		    if (strcmp(R->path_trim, Q->path_trim) > 0)
		    {
			R = Q;
			R0 = Q0;
		    }
		}
		if (R != P)	/* Do exchange */
		{
		    if (R0 == P)
		    {
			P0->path_next = R;
			P->path_next = R->path_next;
			R->path_next = P;
		    }
		    else
		    {
			xch(R->path_next, P->path_next)
			if (P0)
			    xch(R0->path_next, P0->path_next)
			else
			    xch(R0->path_next, pathlist)
		    }
		    P = R;
		}
	    }
	    SORT(P,len);
	}
}

/* dirpath_make>:
 * Given the name of a directory-file, form a path-name from it, without a
 * trailing ']', e.g.,
 *
 *	DBC4:[DICKEY]C.DIR	=>	DBC4:[DICKEY.C
 */
int	dirpath_make (s, z)
char	*s;
FILENT	*z;
{
	strcpy (s, zPATHOF(z));
	strcpy (&s[strlen(s)-1], ".");	/* Trim trailing ']'		*/
	dirent_cat_n (s, z);		/* Copy w/o trailing '.'	*/
	return (strlen(s));
}
