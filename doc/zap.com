$! $Id: zap.com,v 1.2 1985/01/03 00:39:20 tom Exp $
$! DELETE all RUNOFF output files, leaving only the inputs.
$!
$ LOOP:
$	file = f$search("''p1'")
$ if file .eqs. "" then					EXIT
$	type = f$parse("''file'",,,"TYPE")
$
$!	if type .eqs. ".BLB" then			goto DOIT
$	if type .eqs. ".BRN" then			goto DOIT
$!	if type .eqs. ".CCO" then			goto DOIT
$!	if type .eqs. ".DOC" then			goto DOIT
$!	if type .eqs. ".ERR" then			goto DOIT
$!	if type .eqs. ".HLP" then			goto DOIT
$!	if type .eqs. ".PLM" then			goto DOIT
$!	if type .eqs. ".MAN" then			goto DOIT
$!	if type .eqs. ".OPR" then			goto DOIT
$!	if type .eqs. ".STD" then			goto DOIT
$	if type .eqs. ".MEC" then			goto DOIT
$!	if type .eqs. ".MEX" then			goto DOIT
$	if type .eqs. ".MEM" then			goto DOIT
$	if type .eqs. ".RNT" then			goto DOIT
$	if type .eqs. ".RNX" then			goto DOIT
$	goto LOOP
$ DOIT:
$	write sys$output "file ''file'"
$	NOPROT 'file
$	DELETE 'file
$	goto LOOP
$
$ DONE:	exit
