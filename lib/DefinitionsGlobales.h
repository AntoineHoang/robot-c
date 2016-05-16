
#define setOCR1A 0b00100000
#define setOCR1B 0b00010000
#define nOCR1A 0b11011111
#define nOCR1B 0b11101111


#define setBitM(port, n) ((port) |= (1<<(n)))
#define unsetBitM(port, n) ((port) &= (0xff<<(n))+(0xff>>((n)+1)))

#define cBits(port,n,val) ((port) &= (unsigned char)~(val<<(n)))
#define sBits(port,n,val) ((port) |= (val<<(n)))


#define IntEn sBits(SREG,7,1)
#define IntDis cBits(SREG,7,1)


#define PINS12 0
#define PINS34 1
#define PINS56 2
#define PINS78 3	

#define DELPORT PORTB
#define DELDDR DDRB

#define ETEINT 0
#define ROUGE 1
#define VERT 2