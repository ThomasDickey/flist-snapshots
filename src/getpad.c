 			/* Copyright 1984 (C) Thomas E. Dickey */

#include	"getpad.h"

/*
 * Title:	getpad.c - Get keypad "character"
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	07 May 1984
 * Last Update:	18 Sep 1984, use 'alarm' instead of 'putchar'
 *		22 Jun 1984, corrections to erro handling
 *		23 May 1984, to sound alarm on illegal sequences
 *
 * Function:	Read and parse input character stream, throwing away
 *		escape sequences which do not correspond to VT52 or VT100
 *		keypad controls.  For these sequences, however, translate
 *		them into an internal code to pass back to the caller.
 *
 *		Non-escape sequences are passed back normally, without
 *		translation.
 *
 * Reference:	VAX/VMS I/O User's Guide (version: V2.2, Jan 1981)
 *
 * Escapes:
 *		ESC <int>...<int> <fin>
 *
 * where
 *		ESC is 033
 *		<int> is an "intermediate character" in the range 20-2F.
 *		<fin> is a "final character" in the range 30-7E.
 *
 * Also:	ESC <;> <20-2F>...<30-7E>
 *		ESC <?> <20-2F>...<30-7E>
 *		ESC <O> <20-2F>...<40-7E>
 *		ESC <Y> <20-7E>...<20-7E>
 *
 * Control:	ESC [ <par>...<par> <int>...<int> <fin>
 *
 * where
 *		<par> is a parameter specifier in the range 30-3F.
 *		<int> is an intermediate character, as above.
 *		<fin> is a final character in the range 40-7E.
 */

typedef	struct	{
	char	*s;
	int	c;
	} PAD_TABLE;

static
PAD_TABLE pad_table[] = {
		"[A",	padUP,		"A",	padUP,
		"[B",	padDOWN,	"B",	padDOWN,
		"[C",	padRIGHT,	"C",	padRIGHT,
		"[D",	padLEFT,	"D",	padLEFT,

		"OP",	padPF1,		"P",	padPF1,
		"OQ",	padPF2,		"Q",	padPF2,
		"OR",	padPF3,		"R",	padPF3,
		"OS",	padPF4,		/* ESC-S unused on VT52 */

		"Op",	pad0,		"?p",	pad0,
		"Oq",	pad1,		"?q",	pad1,
		"Or",	pad2,		"?r",	pad2,
		"Os",	pad3,		"?s",	pad3,
		"Ot",	pad4,		"?t",	pad4,
		"Ou",	pad5,		"?u",	pad5,
		"Ov",	pad6,		"?v",	pad6,
		"Ow",	pad7,		"?w",	pad7,
		"Ox",	pad8,		"?x",	pad8,
		"Oy",	pad9,		"?y",	pad9,

		"Om",	padMINUS,	/* VT52 hasn't this key */
		"Ol",	padCOMMA,	/* VT52 hasn't this key */
		"On",	padDOT,		"?n",	padDOT,
		"OM",	padENTER,	"?M",	padENTER
		};

static
int	max_table	= sizeof (pad_table) / sizeof(pad_table[0]),
	raw;
static
char	bfr[80], *c_;

#define	ESC	'\033'

#define	START	{if (getpad_read() == ESC) {alarm(); goto escape;}}

#define	ABSORB(min,max)	while (raw >= min && raw <= max) START

getpad ()
{
	c_ = bfr;
	if (getpad_read() == ESC)
	{
escape:		c_ = bfr;
		while (getpad_read() == ESC)	/* Ignore illegal escapes */
		{
			alarm();
			c_ = bfr;		/* (undo 'getpad_read')	  */
		}

		switch (raw)			/* Decode according to 2nd */
		{
		case ';':
			START;			/* Get 3rd (counting ESC) */
			ABSORB (0x20, 0x2f);
			return (getpad_look (0x30, 0x7e));

		case '?':
			START;			/* Get 3rd (counting ESC) */
			ABSORB (0x20, 0x2f);
			return (getpad_look (0x30, 0x7e));

		case 'O':
			START;			/* Get 3rd (counting ESC) */
			ABSORB (0x20, 0x2f);
			return (getpad_look (0x40, 0x7e));

		case 'Y':
			START;			/* Get 3rd (counting ESC) */
			ABSORB (0x20, 0x2f);
			return (getpad());

		case '[':
			START;			/* Get 3rd (counting ESC) */
			ABSORB (0x30, 0x3f);
			ABSORB (0x20, 0x2f);
			return (getpad_look (0x40, 0x7e));

		default:
			ABSORB (0x20, 0x2f);
			return (getpad_look (0x30, 0x7e));
		}
	}
	else
		return (raw);
}

getpad_look (min, max)
{
int	j;

	if (raw >= min && raw <= max)
	{
		*c_++ = '\0';
		for (j=0; j < max_table; j++)
			if (strcmp(pad_table[j].s, bfr) == 0)
				return (pad_table[j].c);
	}
	alarm();
	return (getpad());	/* Ignore if not a keypad sequence */
}

getpad_read()
{
	return (*c_++ = raw = getraw(0,1,0));
}
