#include "p33Fxxxx.h"
#include "timer.h"
#include "display.h"
#include "delay.h"
void delay(int time)
{
Timer1=time;
while(Timer1){}

}
