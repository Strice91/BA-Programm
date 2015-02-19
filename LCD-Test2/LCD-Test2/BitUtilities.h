// General bit utilities

#define sbi(PORT, bit) 		(PORT|=(1<<bit)) 	// set bit in PORT
#define cbi(PORT, bit) 		(PORT&=~(1<<bit))	// clear bit in PORT
#define tgl(PORT, bit) 		(PORT^=(1<<bit))	// toggle bit in PORT
