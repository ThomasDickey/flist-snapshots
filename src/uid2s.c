#ifndef NO_IDENT
static char *Id = "$Id: uid2s.c,v 1.1 1995/10/24 10:03:28 tom Exp $";
#endif

/*
 * Title:	uid2s.c
 * Author:	T.E.Dickey
 * Created:	15 Dec 1988 (for TD_LIB)
 * Modified:
 *		23 Oct 1995, standalone module for use in FLIST distribution
 *
 * Function:	Given a unix-style uid, finds the corresponding username string
 *		and returns a pointer to it.
 *
 *		The corresponding inverse translation is bundled with this
 *		module on VMS since no password support is provided.
 *
 *		The corresponding functions for group-id are bundled here also
 *		because the VMS system call which returns user-name does not
 *		distinguish (except by use of "-1" for group) between these
 *		and group-names.
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#include	<starlet.h>
#include	<ssdef.h>
#include	<descrip.h>

#include	"sysutils.h"

#define	ID_MASK		0xffff
#define	GID_SHIFT	16

typedef	struct	my_list {
	struct	my_list	*next;
	unsigned id;
	char	*name;
	} MY_LIST;

static	MY_LIST	*identifiers;

/*
 * Lookup an identifier in the system rights database, and append it to the
 * list we've cached in memory.
 */
static
char *	lookup_id (unsigned id)
{
	static	unsigned contxt	= 0;

	char	*result = 0;
	short	namlen	= 0;
	unsigned resid	= 0;
	unsigned attrib	= 0;
	static	char	buffer[80];
	$DESCRIPTOR(nambuf,buffer);

	if (sys$idtoasc(
			id,
			&namlen,
			&nambuf,
			&resid,
			&attrib,
			&contxt) == SS$_NORMAL) {
		MY_LIST *p = (MY_LIST *)malloc(sizeof(MY_LIST));
		p->next = identifiers;
		p->id   = id;
		p->name = strncpy(calloc(namlen+1,1), buffer, namlen);
		result  = p->name;
		identifiers = p;
	}
#if 0
	if (st != SS$_NOSUCHID)
		sys$finish_rdb(contxt);
#endif
	return (result);
}

/*
 * Translate a uid to a string, returning a pointer to text-constant.
 * Note that on VAX/VMS we may want to lookup the ordered pair [gid,uid].
 */
static
char *	uid_to_string(unsigned uid, unsigned gid)
{
	char	*result = 0;
	MY_LIST *p;

	if (uid != ID_MASK) {
		unsigned id0 = uid;
		unsigned id1 = (uid | (gid << GID_SHIFT));
		for (p = identifiers; p != 0; p = p->next) {
			if (p->id == id0
			 || p->id == id1) {
				result = p->name;
				break;
			}
		}
		if (result == 0)
			result = lookup_id(id0);
		if (result == 0)
			result = lookup_id(id1);
	}
	if (result == 0) {
		static char temp[10];
		sprintf(result = temp, "%u", uid);
	}
	return (result);
}

/*
 * Translate a gid to a string, returning a pointer to text-constant
 */
static
char *	gid_to_string(unsigned gid)
{
	char	*result = 0;
	MY_LIST *p;

	if (gid != ID_MASK) {
		unsigned id = (gid << GID_SHIFT) | ID_MASK;
		for (p = identifiers; p != 0; p = p->next) {
			if (id == p->id) {
				result = p->name;
				break;
			}
		}
		if (result == 0)
			result = lookup_id(id);
	}
	if (result == 0) {
		static char temp[10];
		sprintf(result = temp, "%u", gid);
	}
	return (result);
}

/*
 * Special VMS-only entrypoint to translate id to string
 */
char *	vms_uid2s(char *result, unsigned member, unsigned group)
{
	int	bracket = ((group & 0100000) == 0);

	*result = '\0';
	if (bracket) {
		strcat(result, "[");
		if (group != 1) {
			strcat(result, gid_to_string(group));
			strcat(result, ",");
		}
	}
	strcat(result, uid_to_string(member, group));
	if (bracket)
		strcat(result, "]");
	return (result);
}
