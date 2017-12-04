#define RD   PORTGbits.RG15
#define WR   PORTGbits.RG12
#define DC   PORTGbits.RG13
#define CS   PORTGbits.RG14
#define RES  PORTCbits.RC1 
#define data_bus PORTE
#define _NOP asm("nop")
//volatile unsigned int i;
//#define _NOP {for(i=0;i<100;i++);}
#define ISDN  PORTAbits.RA0 

void port_conf(void);
void comm_out(unsigned char); 
void data_out(unsigned char i); 
void reset (void);
void IND_Lock(void);
void IND_Unlock(void);

void Refresh_Regs (void);
void init_OLED_GS_DC (void);
void write_RAM (void);
void disp_init (void);
unsigned char	data_read(void);

void frame_out(void);
void symbol_out(unsigned char x, unsigned char y, unsigned char N);


void stroka_out(unsigned char x,unsigned char y, unsigned char N, unsigned char a[N] );
void symbol_numb_out(unsigned char x, unsigned char y,unsigned char N);

void	displey_mask(void);

void number_out(unsigned char x, unsigned char y,unsigned int N);
void number_p_out(unsigned char x, unsigned char y,unsigned int N);