/*
 * Title:	main.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	29 Nov 1984
 * Last update:	28 Mar 1985, added 'status' argument to 'error'
 *		01 Dec 1984
 *
 * Function:	Define miscellaneous functions which may differ when
 *		implemented for a standalone main program from that used
 *		in a program linked to DIRED.
 */

#ifndef	main_incl
error (status, s_)
char	*s_;
{
char	msg[80];

	whoami (msg, 3);
	strcat (msg, "-f-");
	if (s_)
		printf ("%s%.60s\n", msg, s_);
	else
		perror (msg);
	exit (status);
}
#endif
