      		/* Copyright 1984, 1985 (C), Thomas E. Dickey */
/*
 * Title:	dired.c - Release history
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	28 Aug 1984
 * Last update:			In-progress: restructure 'dircmd', 'getraw'.
 *
 *	x2149	22 Apr 1993	Rebuilt at Software Productivity Consortium
 *
 *	x2062	08 Oct 1985	Added code in CRT-module to detect change of
 *				terminal-size (especially after spawned commands).
 *				Used this to support /WIDTH command which lets
 *				one toggle 80/132 column mode.  Added arguments
 *				to HELP-command (from PROTECT, we go directly
 *				to the PROTECTION help-entry).
 *
 *	x2051	24 Sep 1985	Decode SET, SHOW as '/', '?' command-prefixes.
 *				Added VMS-style aliases /PROTECTION and ?DAYTIME
 *				to exploit this.  Added code in command-parser
 *				to generate message listing range of close-match
 *				keywords if no match was found.
 *
 *	x1998	14 Sep 1985	Amended READ command so that explicit update
 *				is done via UPDATE command.  If user types
 *				READ, existing database entries are not reopened.
 *
 *				Corrected collating order: VMS apparently sorts
 *				filenames counting trailing '.'
 *
 *				Enhanced wildcard comparison to recognize "..."
 *				in pathnames (fixes merge-problem with readlist).
 *
 *	x1957	26 Aug 1985	Amended /CWIDTH code so that we recompute on
 *				exit from a directory, and so that most operations
 *				which alter 'ccolumns' can result in a screen
 *				refresh (except indirect RENAME-path).
 *
 *				/CWIDTH without arguments recomputes 'ccolumns'
 *
 *				Link the release-copy /NOTRACEBACK since this is
 *				necessary to install-with-privilege (needed in
 *				turn for the SHELL command).
 *
 *	x1946	17 Aug 1985	Corrected (compiler hole) bug in '?FIND', made
 *				it stacked/hierarchical.
 *
 *				Make '.LOG' file receive everything that '.LIS'
 *				file does (i.e., results of '?READ').
 *
 *				Some enhancements to BROWSE program.
 *
 *	x1924	31 Jul 1985	Completed recoding to "structured heap" for all
 *				data objects.
 *
 *				Permit EDIT-directory command to accept options
 *				(except /COMMAND, /LOG and /FAST).
 *
 *				Permit wildcard-RENAME operation.
 *
 *				Added code to pack display when exiting from a
 *				level.
 *
 *				Added keyword 'UPDATE' for next-release work.
 *				Added '?READ' command.
 *
 *	x1835	06 Jul 1985	Corrected multi-quit screen refresh in 'dircmd'.
 *				Added "true" type-ahead test in 'getraw'.
 *
 *				Added "SHELL" and "?FIND" commands.  Altered
 *				/HOLD-operation so that we skip some before
 *				prompt if there is an error.  Reset keypad
 *				mode before calling librarian-help-facility.
 *
 *				Added /BEFORE, /SINCE options to do date-select.
 *				Also options /AFTER, /BACKUP, /CREATED and
 *				/MODIFIED as synonyms (to make it look more like
 *				VMS).
 *
 *				Upgrade to CC2.0; minor (but frustrating) fixes.
 *
 *				Revised 'nameheap' so that we use a single
 *				tagged heap (provides unique strings among levels)
 *				Used this also to support 'pathlist' (i.e., a
 *				directory-RENAME affects all levels).
 *
 *	x1667	24 May 1985	Added '/' command, '/CWIDTH' command.  Do log
 *				entry for set/show commands which operate on
 *				the current entry.
 *
 *	x1645	18 May 1985	Restructured 'dircmd' module so that all key
 *				definitions are via a string-table.  Also, the
 *				vcmd-tables are both in the same format.  We
 *				still use separate decoding for display (/,?)
 *				and file (DCL) commands.  The string-table makes
 *				log-files all in a readable format.
 *
 *				Corrected help-interface for VMS 4.x, which
 *				returns a different pathname for system files
 *				in GETJPI (see: whoami).
 *
 *				/FORWARD and /BACKWARD now accept a line-count
 *				argument.  Use this in keypad to set direction
 *				flag (0 lines).  Added '/PAGE' command to handle
 *				scroll-in-current-direction.
 *
 *	x1537	27 Apr 1985	Changed VAX/750-sid for re-issue.  'edtcmd'
 *				module is broken out, provides command-history
 *				and editing for BROWSE.  Put spurious sid-test
 *				in 'dclarg'.
 *
 *	x1517	20 Apr 1985	Added VAX/785-sid for re-issue.  In-progress
 *				for 'edtcmd' module; not included.
 *
 *				Added '/LOG' option to FLIST (not complete)
 *
 *	x1480	11 Apr 1985	Fixed 'pathup' by making it translate logical
 *				devices (fixed sys-manager bug).
 *
 *				Added /COMMAND options to both FLIST and BROWSE.
 *				'getraw' permits nested command-files.
 *
 *				Redid BROWSE's "X" as a CTRL/X AST.
 *
 *				Added '?MEMORY' command, put it on ',' keypad.
 *
 *	x1439	26 Mar 1985	Released second-version (with ATC's 730 in the
 *				SID-list).
 *
 *				Added column-types IDENTIFIER, LENGTH, with
 *				their associated sort-commands.
 *
 *				Provided interface to VMS-help (librarian
 *				routine).  Make /DS, /DL commands a 3-state
 *				switch.
 *
 *	x1421	14 Mar 1985	Renamed this program to FLIST; released first
 *				version for local use on ATC/Shelton VMS systems.
 *
 *				Added CTRL/C-ast to do cleanup.  Also require
 *				screen-height to be at least 4 lines.
 *
 *	x1412	11 Mar 1985	Added code to 'flrnam', 'dirpath' to properly
 *				rename pathnames when a directory is renamed.
 *
 *				Permit (wildcard) file specification in PROTECT.
 *				Added 'dirent_isdir' (common).  The 'dirfind'
 *				search 'forward' argument, if negative, uses the
 *				prevailing direction-flag: used in DELETE, PURGE
 *				and PROTECT.
 *
 *				Init flcols from main only (to make it inherit
 *				properly).  Restrict 'dirent_col' to keep at
 *				least 10 columns in command-field.
 *
 *	x1360	02 Mar 1985	Revised O (/OVER) command of MORE to do 2-state
 *				toggle, or accept argument.  Also, corrected
 *				overstrike/highlighting (space by '_').
 *
 *				Added code to 'getraw' which tests the system
 *				identification register against known values,
 *				and garbages the input stream if a mismatch
 *				occurs.
 *
 *				Added "magic" (undocumented) function to copy
 *				date from one file to another: If /MARK is set,
 *				then a repeated ^D on another file will cause
 *				DIRED to copy date,protection from the marked
 *				file.
 *
 *				Added fatal-error message to 'more' ('erstat'),
 *				and truncate filename via 'more_name'.  Modified
 *				/JOIN-option in MORE to both omit binary files
 *				(by record-size) and to do joining if no trailing
 *				linefeed was found.
 *
 *	x1327	07 Feb 1985	Corrected INSPECT function (wasn't checking for
 *				at least one legal record; assumed I could always
 *				read a record).  Also, split 'dirseek_spec' into
 *				two levels so that I can support implicit
 *				wildpaths in INSPECT and VERIFY (was an error
 *				since 'dirfind' did not overlap properly with
 *				the VMS-search).  Make a 30-page stack in link,
 *				this seems to get rid of a runtime fault (?).
 *				(This seems a large stack; I tested it down to
 *				an 8-level directory.  With a 20-page stack I
 *				get a protection violation about 4-5 levels down.)
 *	x1298	02 Feb 1985	Corrected use of alarms in MORE.  Fixed ACPLOOK
 *				for (special?) case of 0-size of indexed files.
 *				Added 'crt_qsgr' entry to fix calls by SNAPSHOT.
 *				Reduce sys-search from 'dclarg'.  Revised the
 *				handling of 'readlist' (better pruning) in
 *				'dirread' module.  Added scrolling margin code
 *				to 'crt' module (making VT100 faster).  Do
 *				better cleanup/reset of terminal on exit and
 *				spawning.
 *	x1240	20 Jan 1985	Extensions to MORE (I,J, /TRIM) and rationalized
 *				its use of scale-mode and repeat-factor.
 *				Added crt-reset code to reset scrolling margins,
 *				and smooth-scroll on entries/re-entries.
 *	x1230	08 Jan 1985	Renamed BACKUP and REVISED qualifiers to
 *				DBACKUP and DREVISED.  Separate /NOO and /NOP
 *				tests in column-setup and sorting.
 *				Renamed 'FINDNXT' to 'NEXT', removed unneeded
 *				parsing from 'dirfind' module (faster).
 *	x1216	30 Dec 1984	Added "/SBACKUP", "/SCREATED", "/SREVISED" and
 *				"/SWEEK".  Added relative-number scrolling.
 *				Added "/MARK", "/NOMARK" (keypad-select), and
 *				highlight selected name, to show state.  Made
 *				this re-entrant in 'fledit'.
 *				Corrected error returns in 'chprot', 'setprot'
 *				and 'flprot'.  Added "/CLEFT", "/CRIGHT" and
 *				"NFIND".  Added "/DLONG", "/DSHORT".
 *	x1133	21 Dec 1984	Fixed bug in /SHOUR caused by flakey system
 *				code; permit system user to change protection.
 *				Re-coded 'cmdstk' so it uses a single-page
 *				buffer (instead of a linked list) to cut
 *				paging.  Reduced (by recoding 'dirent_chop'
 *				and new interface) the number of times I use
 *				SYS$PARSE; also use the same FAB for SYS$SEARCH
 *				and SYS$OPEN (reduces both CPU time, as well
 *				as paging across DECNET).  Provide ^D,^E,^F
 *				in command-line edit (a la VMS4.0).
 *	x1063	12 Dec 1984	Use ACP to speed up directory-read.  Added
 *				"?QUOTA", "/SFORMAT", and "/SATTRIBUTE".
 *				Added 'nameheap', to manage longer names for
 *				VMS 4.0, added PATH column-type ("/columns").
 *	x1012	03 Dec 1984	Added 'X' command to MORE (abort skip/search).
 *				Use 'putraw' to bypass Unix I/O bug.
 *				Added FORMAT, ATTRIBUTE column types, added
 *				INSPECT command.  Use ACP for change-protect
 *				('setprot', 'chprot' routines).
 *	x971	06 Nov 1984,	Improved crt-driver, improved MORE.
 *	x965	24 Oct 1984,	Cleanup of MORE, added 'sysfom' timer, broke
 *				out 'cmdstk'.
 *	x941	17 Oct 1984,	RMS-MORE, snapshot (^K), put locked-files at
 *				top of date-sort, put ^K, ^W into 'dircmd_GET'.
 *	x929	28 Sep 1984,	cleanup of RMS I/O (no more Unix file I/O,
 *				except via 'printf').
 *	x883	04 Sep 1984,	"/columns", multi-level quit, use "import" to
 *				reduce map-size.
 *	x854	29 Aug 1984,	"?"-prefix commands, cleanup of buffer sizes,
 *				use VAX string stuff.
 */

char
*dired_release()
{
	return ("FLIST x2149 (22 Apr 1993)");
}
