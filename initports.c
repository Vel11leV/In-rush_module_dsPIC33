#include "p33Fxxxx.h"

void initports(void)
{
/*MC pin's initialisation*/
/////////////////////////////////////////
AD1PCFGH=0b1111111111111111; //  All ANx pins are digital;
AD1PCFGL=0b1111111111111111;
AD2PCFGL=0b1111111111111111;
/////////////////////////////////////////
TRISDbits.TRISD15=1;
TRISAbits.TRISA7=1;

TRISDbits.TRISD6=1;
TRISDbits.TRISD4=1;

TRISDbits.TRISD15=1;
TRISAbits.TRISA7=1;

TRISGbits.TRISG6=1;
TRISAbits.TRISA6=1;

TRISBbits.TRISB1=1;
TRISGbits.TRISG8=1;

TRISDbits.TRISD13=1;
TRISBbits.TRISB0=1;
//////////////////////////////////////////
TRISBbits.TRISB8=0;		//L1
/*TRISFbits.TRISF12=0;	//L16
TRISDbits.TRISD8=0;		//L10
TRISAbits.TRISA4=0;		//L8
TRISGbits.TRISG0=0;*/		//L4
TRISDbits.TRISD12=0;	//L2
/*TRISDbits.TRISD3=0;		//L3
TRISGbits.TRISG1=0;*/		//L5
//////////////////////////////////////////
	/*PORTBbits.RB8=
	PORTFbits.RF12
	PORTDbits.RD4
	PORTGbits.RG0
	PORTGbits.RG1
	PORTAbits.RA4
	PORTDbits.RD8
	PORTFbits.RF12*/


}
