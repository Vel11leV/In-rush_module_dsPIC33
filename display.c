#include "p33Fxxxx.h"
#include "display.h"
#include "delay.h"
#include "n5x8.h"
#include "words.h"

#define X_Offset 28

#define Ind_Data_Port 	LATE

#define Ind_D_WR(i) \
	{ \
		Ind_Data_Port = i; \
		_NOP; \
	}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void port_conf(void)
{
TRISGbits.TRISG15=0; //ports have been configurated as OUT-ports
TRISGbits.TRISG14=0;
TRISGbits.TRISG13=0;
TRISGbits.TRISG12=0;

TRISCbits.TRISC1=0;

TRISAbits.TRISA0=0;

TRISE=0;



}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void comm_out(unsigned char i)
{
DC=0;
_NOP;
CS=0;
_NOP;

WR=0;

Ind_Data_Port=i;
_NOP;

WR=1;
_NOP;
CS=1;
_NOP;
DC=1;
_NOP;
};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void data_out(unsigned char i)
{
DC=1;
_NOP;
CS=0;
_NOP;
WR=0;

Ind_Data_Port=i;
_NOP;

WR=1;
_NOP;
CS=1;
_NOP;
DC=1;
_NOP;
};

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void reset(void)
{
	ISDN=0;
	_NOP;

	CS=1;
	_NOP;

	WR=1;
	_NOP;

	RD = 1;
	_NOP;

	RES = 1;
	_NOP;

	delay(4);
	RES = 0;	// Reset Driver IC
	_NOP;
	delay(4);

	RES = 1;
	_NOP;
	delay(4);

	
}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
unsigned char	data_read(void)
{
	static unsigned char (Temp_in);
	// Port E as input
	TRISE = 0xFFFF;
	_NOP;

	DC = 1;		// DC SET HIGH FOR DATA
	_NOP;
	CS = 0;	// CHIP SELECT SET TO LOW
	_NOP;
	
	RD = 0;	// LOW FOR READ
	_NOP;
	_NOP;
	_NOP;
	_NOP;
	_NOP;
	_NOP;

	Temp_in = data_bus;
	_NOP;

	RD = 1;	// NO READ
	_NOP;
	CS = 1;	// CHIP SELECT SET TO HIGH
	_NOP;
	DC = 1;		// DC SET HIGH TO DATA
	_NOP;
	// Port E as output
	TRISE = 0;
	_NOP;

	return (Temp_in);
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void IND_Lock(void)
{
comm_out(0xFD);
data_out(0x12);
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void IND_Unlock(void)
{
comm_out(0xFD);
data_out(0x16);
//Refresh_Regs();
};

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void Refresh_Regs (void)
{
	comm_out(0xB3); // SCLK CLOCK DIVIDER RATIO SELECT
	data_out(0x91); 

	comm_out(0xCA); // MUX RATIO
	data_out(0x3F); 

	comm_out(0xA2); // Set dispay offset
	data_out(0x00); 

	comm_out(0xA1); // Set display Start Line
	data_out(0x00);

	comm_out(0xA0); //Set horisontal adress increment,disable column addres remap,
	data_out(0x10); //disable nibble remap,scan from com 0 to (N-1),disable com split;
	data_out(0x1);  

	comm_out(0xB5); // Set GPIO
	data_out(0x00); 

	comm_out(0xAB); // Function Selection (Internal VDD)
	data_out(0x01); 

	comm_out(0xB4); // Enable Exteral VSL
	data_out(0xA0); 
	data_out(0xFD); 

	comm_out(0xC1); // Set Contrast Current
	data_out(0x9F); 

	comm_out(0xC7); // Master Contrast Current control 
	data_out(0x0F); 

	comm_out(0x00); // Set GrayScale Table

	comm_out(0xB8); // Set GrayScale Table
	data_out(0); 
	data_out(0); 
	data_out(8); 
	data_out(16); 
	data_out(24); 
	data_out(32); 
	data_out(40); 
	data_out(48); 
	data_out(56); 
	data_out(64); 
	data_out(72); 
	data_out(80); 
	data_out(88); 
	data_out(96); 
	data_out(104); 
	data_out(112); 

	comm_out(0xB9); // Set Default Linear Gray Scale Table

	comm_out(0xB1); // Set Phase Length
	data_out(0xE2);

	comm_out(0xD1); // Enhance Driving Scheme Capability
	data_out(0x82); 
	data_out(0x20); 

	comm_out(0xBB); // Set Precharge Voltage
	data_out(0x1F); 

	comm_out(0xB6); // Set Second Precharge Voltage
	data_out(0x08); 

	comm_out(0xBE); // Set VCOMH deselect level
	data_out(0x07); 

	comm_out(0xA9); // Exit from Partial Display

ISDN=1;
	_NOP;
	
delay(120);

	comm_out(0xA6); // Set Display Mode
};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void init_OLED_GS_DC (void)
{
	              /////COMMAND SETTING//////

	comm_out(0xFD); // Command lock
	data_out(0x12); 

	comm_out(0xAE); // Sleep In

	comm_out(0xB3); // SCLK CLOCK DIVIDER RATIO SELECT
	data_out(0x91); 

	comm_out(0xCA); // MUX RATIO
	data_out(0x3F); 

	comm_out(0xA2); // Set dispay offset
	data_out(0x00); 

	comm_out(0xA1); // Set display Start Line
	data_out(0x00);

	comm_out(0xA0);  // Set horisontal adress increment,disable column addres remap,  
	data_out(0x14); // disable nibble remap,scan from com 0 to (N-1),disable com split;
	data_out(0x11); 

	comm_out(0xB5); // Set GPIO
	data_out(0x00); 

	comm_out(0xAB); // Function Selection (Internal VDD)
	data_out(0x01); 

	comm_out(0xB4); // Enable Exteral VSL
	data_out(0xA0); 
	data_out(0xFD); 

	comm_out(0xC1); // Set Contrast Current
	data_out(0x9F); 

	comm_out(0xC7); // Master Contrast Current control 
	data_out(0x0F); 

	comm_out(0xB9); // Set Default Linear Gray Scale Table

	comm_out(0xB1); // Set Phase Length
	data_out(0xE2);

	comm_out(0xD1); // Enhance Driving Scheme Capability
	data_out(0x82); 
	data_out(0x20); 

	comm_out(0xBB); // Set Precharge Voltage
	data_out(0x1F); 

	comm_out(0xB6); // Set Second Precharge Voltage
	data_out(0x08); 

	comm_out(0xBE); // Set VCOMH deselect level
	data_out(0x07); 


	ISDN = 1;
	_NOP;
	
	delay(120);

	comm_out(0xA6); // Set Display Mode
	// Clear Screen

	
comm_out(0xAF); // Sleep Out
write_RAM();



};

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void write_RAM (void)
{

	
	unsigned int i, j;
	
	//IND_Unlock();

//	sub_comm();
	Pos(0,0);
	comm_out(0x5C); // Enable write to RAM
	
	for (i = 0; i < 64; i++)
	{
		for (j = 0; j < 256; j++)
		{
			data_out(0x0);

		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void disp_init (void)
{
port_conf();
reset();
init_OLED_GS_DC();


}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void collumn_start_end(unsigned char start, unsigned end)   //column start and end point in RAM range:0....63!!!offset 28!!!
{
comm_out(0x15);
data_out(start);
data_out(end);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void row_start_end(unsigned char start, unsigned end)       //row start and end point in RAM range:0....63
{
comm_out(0x75);                                               
data_out(start);
data_out(end);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void frame_out(void)

{
unsigned int i,j;

/*---------------------------------*/


Pos(0,0);

comm_out(0x5C); // Enable write to RAM


for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0xFF);
		}
	}

/////////////////////////////////////////////////////////
Pos(0,63);

comm_out(0x5C); // Enable write to RAM

for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0xFF);
		}
	}
/////////////////////////////////////////////////////////
collumn_start_end(28,28);
row_start_end(1,62);

comm_out(0x5C);
for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0xF0);
			data_out(0x0);
		}
	}
/////////////////////////////////////////////////////////
collumn_start_end(28+63,28+63);
row_start_end(1,62);

comm_out(0x5C);
for (i = 0; i <2 ; i++)
{
	for (j = 0; j < 64; j++)
		{
			data_out(0x00);
			data_out(0x0F);
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void number_out(unsigned char x, unsigned char y,unsigned int N)
{
unsigned int p;
unsigned char mass[4],i;
for(p=0;p<5;p++)
{
mass[3-p]=N%10;
N=N/10;
}
 	for(i=0;i<4;i++)
	{
	symbol_numb_out(x+i*2,y,mass[i]);
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void number_p_out(unsigned char x, unsigned char y,unsigned int N)
{
unsigned int p;
unsigned char mass[4];
for(p=0;p<4;p++)
{
	if(p!=1)
	{
	mass[3-p]=N%10;
	N=N/10;
	};
	if(p==1)
	{mass[3-p]=10;}
}
unsigned char i;
 	for(i=0;i<4;i++)
	{
	symbol_numb_out(x+i*2,y,mass[i]);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void symbol_out(unsigned char x, unsigned char y,unsigned char N) //letter is out
{
unsigned char a,i,j;
unsigned char line_1, line_2;
unsigned char bit_1, bit_2;
unsigned char mass[8];
//IND_Unlock();

for (a=0;a<8;a++)
{
if (a<5)
{mass[a]=letters[N][a];};
if (a>=5)
{mass[a]=0x00;};
}


collumn_start_end(x+X_Offset+1,x+X_Offset+2);
row_start_end(y+4,y+4+7);
comm_out(0x5C);


for(i=0;i<8;i++)
{

for(j=0;j<8;j=j+2)
	{
			
		line_1=mass[j];
		line_2=mass[j+1];

		bit_1=(line_1&1);
		bit_2=(line_2&1);
		
		if(bit_1&&bit_2)
			{data_out(0xFF);}
		
		if((!bit_1)&&(bit_2))
			{data_out(0x0F);}
		
		if(bit_1&&(!bit_2))
			{data_out(0xF0);}
		
		if((!bit_1)&&(!bit_2))
			{data_out(0x00);}
		
		mass[j]=(mass[j]>>1);
		mass[j+1]=(mass[j+1]>>1);
			
	}


}

	
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void symbol_numb_out(unsigned char x, unsigned char y,unsigned char N) //number is out
{
unsigned char a,i,j;
unsigned char line_1, line_2;
unsigned char bit_1, bit_2;
unsigned char mass[8];
//IND_Unlock();

for (a=0;a<8;a++)
{
if (a<5)
{mass[a]=numbers[N][a];};
if (a>=5)
{mass[a]=0x00;};
}

collumn_start_end(x+X_Offset+1,x+X_Offset+2);
row_start_end(y+4,y+4+7);
comm_out(0x5C);


for(i=0;i<8;i++)
{

for(j=0;j<8;j=j+2)
	{
			
		line_1=mass[j];
		line_2=mass[j+1];

		bit_1=(line_1&1);
		bit_2=(line_2&1);
		
		if(bit_1&&bit_2)
			{data_out(0xFF);}
		
		if((!bit_1)&&(bit_2))
			{data_out(0x0F);}
		
		if(bit_1&&(!bit_2))
			{data_out(0xF0);}
		
		if((!bit_1)&&(!bit_2))
			{data_out(0x00);}
		
		mass[j]=(mass[j]>>1);
		mass[j+1]=(mass[j+1]>>1);
			
	}


}

	
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void stroka_out(unsigned char x, unsigned char y,unsigned char N, unsigned char *a )
{
unsigned char i;
 	for(i=0;i<N;i++)
	{
	symbol_out(x+i*2,y,a[i]);
	}
}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void	Pos (unsigned char x, unsigned char y)
{
	unsigned char N_chr;

	// pos y
	comm_out(0x75); // Column adress command
	data_out(y); 
	data_out(0x3F); 

	// pos x
	comm_out(0x15); // Column adress command
	data_out((x>>1)+X_Offset); 
	data_out(0x7F); 

	if (x&1)
	{
		comm_out(0x5D); // Read enable command
		data_read(); // Dummy read
		N_chr = data_read();
		data_read();
	
		// pos x
		comm_out(0x15); // Column adress command
		data_out((x>>1)+X_Offset); 
		data_out(0x7F); 
	
		comm_out(0x5C); // Write enable command
		data_out(N_chr); 
		
	}
	else 
		comm_out(0x5C); // Write enable command

}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void	displey_mask(void)
{
stroka_out(17,0,14, heading);
stroka_out(0,15,7, Mode);
stroka_out(0,25,7, Phase1);
stroka_out(0,35,7, Phase2);
stroka_out(0,45,7, Phase3);
//stroka_out(15,15,4, a_uto);
//stroka_out(15,25,4, zero);
//stroka_out(15,35,4, zero);
//stroka_out(15,45,4, zero);
stroka_out(24,25,2, ms);
stroka_out(24,35,2, ms);
stroka_out(24,45,2, ms);
stroka_out(35,15,5, Time);
//stroka_out(46,15,4, zero);
stroka_out(56,15,2, ms);
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////