$	verify = F$VERIFY(0)
$!+
$! defines foreign-commands for testing, automatically from contents of [.bin]
$!-
$	path = F$ENVIRONMENT("procedure")
$	path = "''F$EXTRACT(0,F$LOCATE("]",path),path)'.bin]"
$	name = ""
$ loop_com:
$	last = name
$	name = F$SEARCH("''path'*.com;")
$	if name .nes. "" .and. name .nes. last
$	then
$		name = F$EXTRACT(0,F$LOCATE(";",name),name)
$		'F$PARSE(name,,,"NAME","SYNTAX_ONLY") :== " @ ''name'"
$		goto loop_com
$	endif
$
$ loop_exe:
$	last = name
$	name = F$SEARCH("''path'*.exe;")
$	if name .nes. "" .and. name .nes. last
$	then
$		name = F$EXTRACT(0,F$LOCATE(";",name),name)
$		'F$PARSE(name,,,"NAME","SYNTAX_ONLY") :== "$ ''name'"
$		goto loop_exe
$	endif
$
$	verify = F$VERIFY(verify)
