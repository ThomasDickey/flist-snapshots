$! $Id: build.com,v 1.2 1993/04/23 19:39:30 tom Exp $
$! VAX/VMS DCL build script for FLIST and BROWSE documentation
$!
$! Tested with:
$!	VMS system version 5.4-2
$!	Dec RUNOFF (V3.2-01)
$
$	VERIFY = F$VERIFY(0)
$	set := set
$	set symbol/scope=(nolocal,noglobal)
$	mylib := [-.lib]flist.olb
$
$ if "''p1'" .eqs. "" .or. "''p1'" .eqs. "ALL"
$ then
$	call document d0 FLIST
$	call document m0 BROWSE
$	call helpfile db FLIST
$	call helpfile ma BROWSE
$ endif
$
$ if "''p1'" .eqs. "CLEAN"
$ then
$	if f$search("*.brn") .nes. "" then delete *.brn;*
$	if f$search("*.rnt") .nes. "" then delete *.rnt;*
$	if f$search("*.rnx") .nes. "" then delete *.rnx;*
$	write sys$output "** made CLEAN"
$ endif
$
$ if "''p1'" .eqs. "CLOBBER"
$ then
$	@ 'f$environment("procedure") CLEAN
$	if f$search("*.hlp") .nes. "" then delete *.hlp;*
$	if f$search("*.mem") .nes. "" then delete *.mem;*
$	write sys$output "** made CLOBBER"
$ endif
$
$ VERIFY = F$VERIFY(VERIFY)
$ exit
$
$
$ document: subroutine
$	if f$search("*.brn;*") .nes. "" then delete *.brn;*
$	opts = "/variant=""paged""
$	part = "''p1'-parts"
$	if f$search("''p2'.mem") .eqs. ""
$	then
$		write sys$output "** compiling ''p2' document"
$		runoff'opts/nooutput/intermediate 'part
$		runoff/contents/output='p1 'part
$		runoff/index/output='p1 'part
$		runoff'opts/output='p2.mem 'p1
$		purge 'p2.mem
$		if f$search("*.brn;*") .nes. "" then delete *.brn;*
$		if f$search("''p1'.rnt;*") .nes. "" then delete 'p1.rnt;*
$		if f$search("''p1'.rnx;*") .nes. "" then delete 'p1.rnx;*
$	endif
$ endsubroutine
$
$ helpfile: subroutine
$	if f$search("''p2'.hlp") .eqs. ""
$	then
$		runoff/variant="lib"/output='p2.hlp 'p1
$	endif
$ endsubroutine
