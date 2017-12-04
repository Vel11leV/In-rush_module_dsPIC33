
#include "p33Fxxxx.h"
#include "timer.h"
#include "delay.h"
volatile unsigned Timer1;


//////////////////////////////////////////////////////////////////////////////////////////////

void TimerInit(void)
{
PR1 = (8000000 / 1000 ); // 1ms

	T1CONbits.TON = 0b1;
	IPC0bits.T1IP = 4;
	IFS0bits.T1IF = 0b0;
	IEC0bits.T1IE = 0b1;

	// инициализация переменных
	Timer1 = 0;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////

void __attribute__(( interrupt, auto_psv )) _T1Interrupt( void ) /* TMR1 Timer 1 expired */
{	
	if (Timer1) Timer1--;
	
	IFS0bits.T1IF = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////////////