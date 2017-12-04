#include "p33Fxxxx.h"
#include "ecan.h"
unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));
/* ECAN message buffer length */


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void dma_conf(void)
{
/*---------------------------DMA initialisation---------------------------*/

/* Initialize the DMA channel 0 for ECAN TX and clear the colission flags */
DMACS0 = 0;
/* Set up Channel 0 for peripheral indirect addressing mode normal operation, word operation */
/* and select TX to peripheral */
DMA0CON = 0x2020;
/* Set up the address of the peripheral ECAN1 (C1TXD) */
DMA0PAD = 0x0442;
/* Set the data block transfer size of 8 */
DMA0CNT = 7;
/* Automatic DMA TX initiation by DMA request */
DMA0REQ = 0x0046;
/* DPSRAM atart address offset value */
DMA0STA = __builtin_dmaoffset(&ecan1MsgBuf);
/* Enable the channel */
DMA0CONbits.CHEN = 1;
/* Initialize DMA Channel 2 for ECAN RX and clear the collision flags */
DMACS0 = 0;
/* Set up Channel 2 for Peripheral Indirect addressing mode (normal operation, word operation */
/* and select as RX to peripheral */
DMA2CON = 0x0020;
/* Set up the address of the peripheral ECAN1 (C1RXD) */
DMA2PAD = 0x0440;
/* Set the data block transfer size of 8 */
DMA2CNT = 7;
/* Automatic DMA Rx initiation by DMA request */
DMA2REQ = 0x0022;
/* DPSRAM atart address offset value */
DMA2STA = __builtin_dmaoffset(&ecan1MsgBuf);
/* Enable the channel */
DMA2CONbits.CHEN = 1;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void bit_timing(void)
{
/* Set the Operating Frequency of the device to be 8MHz */
#define FCY 4000000
/* Set the ECAN module for Configuration Mode before writing into the Baud
Rate Control Registers*/
C1CTRL1bits.REQOP =4;
/* Wait for the ECAN module to enter into Configuration Mode */
while(C1CTRL1bits.OPMODE!= 4);
/* FCAN is selected to be Fosc by setting the CANCKS bit
 FCAN  = 8MHz */
C1CTRL1bits.CANCKS =0b1;

/* Baud Rate Prescaler bits set to 1:1, i.e., TQ = (2*1*1)/ FCAN */
C1CFG1bits.BRP =2;


/* Phase Segment 1 time is 10 TQ */
C1CFG2bits.SEG1PH =3;

/* Phase Segment 2 time is set to be programmable */
C1CFG2bits.SEG2PHTS = 3;

/* Phase Segment 2 time is 2 TQ */
C1CFG2bits.SEG2PH = 2;

/* Propagation Segment time is 2 TQ */
C1CFG2bits.PRSEG = 2;

/* Bus line is sampled 1 time at the sample point */
C1CFG2bits.SAM = 0;

/* Synchronization Jump Width set to 1 TQ */
C1CFG1bits.SJW = 0;



/* Put the ECAN Module into Normal Mode Operating Mode*/
C1CTRL1bits.REQOP = 0;

/* Wait for the ECAN module to enter into Normal Operating Mode */
while(C1CTRL1bits.OPMODE!= 0);
}


///////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////

void ecan_init(void)
{
TRISFbits.TRISF1=0;
TRISFbits.TRISF0=1;
dma_conf();
bit_timing();
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


///-------------------------------------------------------------------------------------
void __attribute__(( interrupt, auto_psv )) _C1Interrupt( void ) /* CAN1 Event Interrupt */
{
	//Повторная инициализация CAN в случае ошибки
	if(C1INTFbits.ERRIF == 1)
	{
		ecan_init();
		C1INTFbits.ERRIF = 0;
	}

	IFS2bits.C1IF = 0;
}


//-------------------------------------------------------------------------------------
/// 							ECAN (DMA2) Transmiter Interrupt
//-------------------------------------------------------------------------------------
void __attribute__(( interrupt, auto_psv )) _DMA2Interrupt( void ) /* DMA2 Transmiter Interrupt */
{
	IFS1bits.DMA2IF = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------transmiting of initial settings on ECAN bus --------------------------------*/

void transmition_times(unsigned char Phase1 , unsigned char Phase2, unsigned char Phase3, unsigned char Time, unsigned char MODE   ) 
{
unsigned int Ph2Ph1,TimePh3; //для преобразования типов

Ph2Ph1=Phase2;
TimePh3=Time;

Ph2Ph1=(Ph2Ph1<<8);
TimePh3=(TimePh3<<8);

Ph2Ph1=Ph2Ph1+Phase1;
TimePh3=TimePh3+Phase3;

/* Assign 32x8word Message Buffers for ECAN1 in DMA RAM */

//unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));
DMA1STA= __builtin_dmaoffset(ecan1MsgBuf);

/* Configure Message Buffer 0 for Transmission and assign priority*/

C1TR01CONbits.TXEN0 = 0x1;				//Buffer 0 is a transmit buffer
C1TR01CONbits.TX0PRI = 0x3; 			//priority is intermidiate

/* WRITE TO MESSAGE BUFFER 0 */
/*CiTRBnSID = 0bxxx1 0010 0011 1100
IDE = 0b0
SRR = 0b0
SID<10:0>= 0b00011011000*/

ecan1MsgBuf[0][0] =0b1111111111100 ;

/* CiTRBnEID = 0bxxxx 0000 0000 0000
EID<17:6> = 0b0000 0000 0000 */

ecan1MsgBuf[0][1] = 0b0;

/*CiTRBnDLC = 0b0000 0000 xxx0 0110
EID<17:6> = 0b000000;
RTR = 0b0;
RB1 = 0b0;
RB0 = 0b0;
DLC = 0b101 ;*/

ecan1MsgBuf[0][2] = 5;

/* WRITE MESSAGE DATA BYTES */
ecan1MsgBuf[0][3] = Ph2Ph1;
ecan1MsgBuf[0][4] = TimePh3;
ecan1MsgBuf[0][5] = MODE;


/* REQUEST MESSAGE BUFFER 0 TRANSMISSION */
C1TR01CONbits.TXREQ0 = 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/*-------------------------transmiting of commands data on ECAN bus --------------------------------*/

void transmition_command(unsigned char comm) 
{

/* Assign 32x8word Message Buffers for ECAN1 in DMA RAM */

//unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));r
DMA1STA= __builtin_dmaoffset(ecan1MsgBuf);

/* Configure Message Buffer 0 for Transmission and assign priority*/

C1TR01CONbits.TXEN0 = 0x1;				//Buffer 0 is a transmit buffer
C1TR01CONbits.TX0PRI = 0x3; 			//priority is intermidiate

/* WRITE TO MESSAGE BUFFER 0 */
/*CiTRBnSID = 0bxxx1 0010 0011 1100
IDE = 0b0
SRR = 0b0
SID<10:0>= 0b00000011000*/

ecan1MsgBuf[0][0] = 0b0;

/* CiTRBnEID = 0bxxxx 0000 0000 0000
EID<17:6> = 0b0000 0000 0000 */

ecan1MsgBuf[0][1] = 0b0;

/*CiTRBnDLC = 0b0000 0000 xxx0 0001
EID<17:6> = 0b000000;
RTR = 0b0;
RB1 = 0b0;
RB0 = 0b0;
DLC = 0b1111 ;*/

ecan1MsgBuf[0][2] = 0b0000000000001000;

/* WRITE MESSAGE DATA BYTES */
ecan1MsgBuf[0][3] = 0;

/* REQUEST MESSAGE BUFFER 0 TRANSMISSION */
C1TR01CONbits.TXREQ0 = 1;

}
