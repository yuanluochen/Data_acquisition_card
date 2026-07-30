#ifndef __TYPEDEF_H_
#define __TYPEDEF_H_

#define SWAP16(c) ((((c)&0xff00)>>8)+(((c)&0x00ff)<<8))
#define SWAP32(c) (( ( (c) & 0xff000000UL ) >> 24)\
    +( ( (c) & 0x00ff0000UL ) >> 8 )\
    +( ( (c) & 0x0000ff00UL ) << 8 )\
    +( ( (c) & 0x000000ffUL ) << 24 ) )
#define SWAP_WORD(c) (( ( (c) & 0xff000000UL ) >> 16)\
    +( ( (c) & 0x00ff0000UL ) >> 16 )\
    +( ( (c) & 0x0000ff00UL ) << 16 )\
    +( ( (c) & 0x000000ffUL ) << 16 ) )
		
/*Data type definations*/
typedef  unsigned char              BOOL ;
typedef  unsigned char              byte ;
typedef  unsigned short int         word ;                       
typedef  unsigned long  int         lword ;

typedef   unsigned char             INT8U;
typedef   signed   char             INT8S;
typedef   unsigned int              INT16U;
typedef   signed   int              INT16S;
typedef   unsigned long             INT32U;
typedef   signed   long             INT32S;

typedef  unsigned char              u_char;
typedef  unsigned short             u_short;
typedef  unsigned int               u_int;
typedef  unsigned long              u_long;
typedef  unsigned long              ulong;
typedef  unsigned short             ushort;         /* System V compatibility */
typedef  unsigned int               uint;           /* System V compatibility */
typedef  unsigned char              uchar;          /* System V compatibility */

#ifndef    u8
#define    u8                uint8
#endif
#ifndef    u16
#define    u16                uint16
#endif
#ifndef    s16
#define    s16                int16_t
#endif
#ifndef    u32
#define    u32                uint32
#endif
#ifndef    s32
#define    s32                int32_t
#endif
#ifndef    uint8
#define    uint8                unsigned char 
#endif
#ifndef    int8
#define    int8                 signed char 
#endif
#ifndef    uint16
#define    uint16               unsigned short 
#endif
#ifndef    int16
#define    int16                signed short 
#endif
#ifndef    int32
#define    int32                signed   long 
#endif
#ifndef    uint32
#define    uint32               unsigned   long 
#endif

#ifndef     vu32
#define     vu32       volatile INT32U 
#endif
#ifndef     vu16
#define     vu16       volatile INT16U 
#endif
#ifndef     vu8
#define     vu8        volatile INT8U             
#endif

typedef uint8 			SOCKET;

typedef enum
{
	BOOL_FALSE = 0,
	BOOL_TRUE  = 1
}BOOLEAN;

/*Bit field operations*/
//#define SetBit( Byte, Bit )  ( Byte ) |= ( 1<<( Bit ) )
//#define ClrBit( Byte, Bit )  ( Byte ) &= ~( 1<<( Bit ) )

#define GetBit( Byte, Bit )  ( ( Byte ) & ( 1<<( Bit ) ) )
#define ComBit( Byte, Bit )  ( Byte ) ^= ( 1<<( Bit ) )
#define SetBits( Byte, Bits ) ( Byte ) |= ( Bits )
#define ClrBits( Byte, Bits ) ( Byte ) &= ~( Bits )
#define GetBits( Byte, Bits ) ( ( Byte ) & ( Bits ) )
#define ComBits( Byte, Bits ) ( Byte ) ^= ( Bits )

/*Bit map for fast calculation*/
#define BitMap( x )   ( 1<<( x ) )
/*Get MAX or MIN value*/
#define GetMax( x1, x2 ) ( ( x1 ) > ( x2 ) ? ( x1 ) : ( x2 ) )
#define GetMin( x1, x2 ) ( ( x1 ) > ( x2 ) ? ( x2 ) : ( x1 ) )

#endif//_TYPEDEF_H_
/*
================================================================================
====================================End of file=================================
================================================================================
*/
