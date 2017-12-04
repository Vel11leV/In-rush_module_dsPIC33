

/* Assign 32x8word Message Buffers for ECAN1 in DMA RAM */

// unsigned int ecan1MsgBuf[32][8] __attribute__((space(dma)));

/*-------------------------------*/

void dma_conf(void);
void bit_timing(void);
void ECAN_trans(void);
void ecan_init(void);

void transmition_times(unsigned char Phase1 , unsigned char Phase2, unsigned char Phase3, unsigned char Time, unsigned char MODE );
void transmition_command(unsigned char comm);
