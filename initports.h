#define SW1		!PORTGbits.RG7
#define SW2		!PORTDbits.RD5
#define SW3		!PORTAbits.RA7
#define SW4		!PORTAbits.RA6
#define SW5		!PORTBbits.RB1
#define SW6		!PORTGbits.RG8
#define SW7		!PORTDbits.RD13
#define SW10	!PORTBbits.RB0
#define SW11	!PORTDbits.RD15
#define SW12	!PORTGbits.RG6
#define SW19	!PORTDbits.RD6
#define SW15	!PORTDbits.RD4


#define HL1     PORTBbits.RB8
#define HL2		PORTDbits.RD12
#define HL3		PORTDbits.RD3
#define HL4		PORTGbits.RG0
//#define HL5		PORTGbits.RG1
#define HL8		PORTAbits.RA4
#define HL10	PORTDbits.RD8
#define HL16	PORTFbits.RF12

void initports(void);