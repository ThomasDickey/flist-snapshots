/*
 * Title:	getpad.h
 * Author:	T.E.Dickey (ITT/ATC)
 * Created:	07 May 1984
 * Last update:	16 Apr 1985, moved secondary-def's here
 *
 *	Define integer codes for VT52/VT100 keypad sequences
 */

#define	pad(x)		(256+x)

#define	padUP		pad('A')
#define	padDOWN		pad('B')
#define	padRIGHT	pad('C')
#define	padLEFT		pad('D')

#define	padPF1		pad('P')
#define	padPF2		pad('Q')
#define	padPF3		pad('R')
#define	padPF4		pad('S')

#define	pad0		pad('0')
#define	pad1		pad('1')
#define	pad2		pad('2')
#define	pad3		pad('3')
#define	pad4		pad('4')
#define	pad5		pad('5')
#define	pad6		pad('6')
#define	pad7		pad('7')
#define	pad8		pad('8')
#define	pad9		pad('9')

#define	padMINUS	pad('-')
#define	padCOMMA	pad(',')
#define	padDOT		pad('.')
#define	padENTER	pad('\n')

/* Keys assigned permanently: */
#define	GOLDKEY		padPF1
#define	HELPKEY		padPF2
#define	RETRIEVE	padMINUS
