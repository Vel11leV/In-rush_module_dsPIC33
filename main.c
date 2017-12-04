
#include "p33Fxxxx.h"
#include "display.h"
#include "delay.h"
#include "n5x8.h"
#include "words.h"
#include "initports.h"
#include "buttons.h"
#include "ecan.h"
#include "dma.h"

void main(void)
{

/*---------Initialisation of the hardware and initial image on displey ---------*/
initports();

HL1=1;    
HL2=1;	


TimerInit();
disp_init();
bit_timing();
ecan_init();
frame_out();
displey_mask();
	



/*-------------------------------Initial setting--------------------------------*/

unsigned int Phase1=0,Phase2=0,Phase3=0,Time=0,MODE=0xF0;
unsigned char i=1,j=0,k=0,n;
unsigned char start=0;

HL1=1;    
HL2=1;	


number_p_out(15,25,Phase1);
number_p_out(15,35,Phase2);
number_p_out(15,45,Phase3);
number_out(46,15,Time);
if(MODE==0xF0)
{stroka_out(15,15,4,a_uto);}

n=5;

/*--------------------------------program---------------------------------------*/
while(1)
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(SW5)
{start=1;}
if(SW6)
{start=0;}


/*---------------------------------------------*/
if(!start)
{
if(SW6)
{
delay(20);
HL1=1;    
HL2=1;

stroka_out(35,35,5, NOTH);
delay(200);
}
/*---------------------------------------------*/
if(SW10)
	{
	delay(20);
	if(i<6)
		{i++;}
	if(i==n+1)
	{i=1;}
	delay(75);
	}
if(SW7)
	{
	delay(20);
	if(i>0)
		{i--;}
	if(i==0)
	{i=n;}
	delay(75);
	}
/*----------------------------------------------*/
if(i==1)
{	
		symbol_out(60,15,59);
		symbol_out(28,15,72);
		symbol_out(28,25,59);
		symbol_out(28,45,59);

	if(SW19)
	{
	delay(20);
	j^=1;	

	if(j==1)
	{
	MODE=0x0F;
	stroka_out(15,15,4,manual);
	n=4;
	stroka_out(46,15,4,noth);
	}
	if(j==0)
	{
	MODE=0xF0;
	stroka_out(15,15,4,a_uto);
	n=5;
	delay(5);
	number_out(46,15,Time);
	}
	delay(200);
	}
}

if(i==2)
{

		symbol_out(28,15,59);
		symbol_out(28,25,72);
		symbol_out(28,35,59);	
	
numb_ch_p(15,25,&Phase1);}

if(i==3)
{
		symbol_out(28,25,59);
		symbol_out(28,35,72);
		symbol_out(28,45,59);

numb_ch_p(15,35,&Phase2);}

if(i==4)
{
		symbol_out(28,35,59);
		symbol_out(28,45,72);
		symbol_out(60,15,59);
		symbol_out(28,15,59);
numb_ch_p(15,45,&Phase3);}

if(i==5)
{
		symbol_out(28,45,59);
		symbol_out(60,15,72);
		symbol_out(28,15,59);
		numb_ch(46,15,&Time);}
}
////////////////////////////////////////////////////////////////////
/*------------------------------------*/
if(start==1)
{

if(SW5)
{
delay(20);
HL1=0;    
HL2=1;


		symbol_out(60,15,59);
		symbol_out(28,15,59);
		symbol_out(28,25,59);
		symbol_out(28,35,59);
		symbol_out(28,45,59);

stroka_out(35,35,5,START);
/*if(!C1TR01CONbits.TXREQ0)
{transmition_times( 0 , 0 , 0 , 0 , 0 );};
delay(200);*/
}
//////////////////////////////////////////////////////////////////////
if(SW1)
{
delay(20);
if(!C1TR01CONbits.TXREQ0)
{transmition_command(0x00);}
HL1=1;    
HL2=1;
//while(C1TR01CONbits.TXREQ0);
delay(500);
	if(MODE)
		{
		HL1=1;    
		HL2=0;
		}
	else{
		HL1=0;    
		HL2=1;
		}
//}

}

///////////////////////////////////////////////////////////////////////
if(SW2&&(MODE==0xF0))
{
delay(20);
/*if(!C1TR01CONbits.TXREQ0)
{transmition_command(0x00);}*/
C1TR01CONbits.TXREQ0 = 0;
HL1=1;    
HL2=1;
//while(C1TR01CONbits.TXREQ0);
delay(500);
HL1=0;    
HL2=1;


}
////////////////////////////////////////////////////////////////////////
}
/*-------------------------------------*/
////////////////////////////////////////////////////////////////////////
}
}
///////////////////////////////////////////////////////////







