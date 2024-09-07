/* this file contains APPLICATION INDEPENDENT C-language literal and
	 data type definitions */

#include "types.h"

#define FALSE 0
#define TRUE 1

#define SPACE 0x20
#define CNTRL_S 0x13

#define NOT_ZERO 1

#define BITS_IN_BYTE	8
#define MAX_BIT_NBR (BITS_IN_BYTE-1)

#define TABLE_END 0

#define RIGHT 1
#define LEFT 2
#define UP 3
#define	DOWN 4

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10



/* binary value-alikes */

#define OOOOOOOO 	0x00
#define OOOOOOOI	0x01
#define OOOOOOIO	0x02
#define OOOOOOII	0x03
#define OOOOOIOO	0x04
#define OOOOOIOI	0x05
#define OOOOOIIO	0x06
#define OOOOOIII	0x07
#define OOOOIOOO	0x08
#define OOOOIOOI	0x09
#define OOOOIOIO	0x0A
#define OOOOIOII	0x0B
#define OOOOIIOO	0x0C
#define OOOOIIOI	0x0D
#define OOOOIIIO	0x0E
#define OOOOIIII	0x0F

#define OOOIOOOO	0x10
#define OOOIOOOI	0x11
#define OOOIOOIO	0x12
#define OOOIOOII	0x13
#define OOOIOIOO	0x14
#define OOOIOIOI	0x15
#define OOOIOIIO	0x16
#define OOOIOIII	0x17
#define OOOIIOOO	0x18
#define OOOIIOOI	0x19
#define OOOIIOIO	0x1A
#define OOOIIOII	0x1B
#define OOOIIIOO	0x1C
#define OOOIIIOI	0x1D
#define OOOIIIIO	0x1E
#define OOOIIIII	0x1F

#define OOIOOOOO	0x20
#define OOIOOOOI	0x21
#define OOIOOOIO	0x22
#define OOIOOOII	0x23
#define OOIOOIOO	0x24
#define OOIOOIOI	0x25
#define OOIOOIIO	0x26
#define OOIOOIII	0x27
#define OOIOIOOO	0x28
#define OOIOIOOI	0x29
#define OOIOIOIO	0x2A
#define OOIOIOII	0x2B
#define OOIOIIOO	0x2C
#define OOIOIIOI	0x2D
#define OOIOIIIO	0x2E
#define OOIOIIII	0x2F

#define OOIIOOOO	0x30
#define OOIIOOOI	0x31
#define OOIIOOIO	0x32
#define OOIIOOII	0x33
#define OOIIOIOO	0x34
#define OOIIOIOI	0x35
#define OOIIOIIO	0x36
#define OOIIOIII	0x37
#define OOIIIOOO	0x38
#define OOIIIOOI	0x39
#define OOIIIOIO	0x3A
#define OOIIIOII	0x3B
#define OOIIIIOO	0x3C
#define OOIIIIOI	0x3D
#define OOIIIIIO	0x3E
#define OOIIIIII	0x3F

#define OIOOOOOO	0x40
#define OIOOOOOI	0x41
#define OIOOOOIO	0x42
#define OIOOOOII	0x43
#define OIOOOIOO	0x44
#define OIOOOIOI	0x45
#define OIOOOIIO	0x46
#define OIOOOIII	0x47
#define OIOOIOOO	0x48
#define OIOOIOOI	0x49
#define OIOOIOIO	0x4A
#define OIOOIOII	0x4B
#define OIOOIIOO	0x4C
#define OIOOIIOI	0x4D
#define OIOOIIIO	0x4E
#define OIOOIIII	0x4F

#define OIOIOOOO	0x50
#define OIOIOOOI	0x51
#define OIOIOOIO	0x52
#define OIOIOOII	0x53
#define OIOIOIOO	0x54
#define OIOIOIOI	0x55
#define OIOIOIIO	0x56
#define OIOIOIII	0x57
#define OIOIIOOO	0x58
#define OIOIIOOI	0x59
#define OIOIIOIO	0x5A
#define OIOIIOII	0x5B
#define OIOIIIOO	0x5C
#define OIOIIIOI	0x5D
#define OIOIIIIO	0x5E
#define OIOIIIII	0x5F

#define OIIOOOOO	0x60
#define OIIOOOOI	0x61
#define OIIOOOIO	0x62
#define OIIOOOII	0x63
#define OIIOOIOO	0x64
#define OIIOOIOI	0x65
#define OIIOOIIO	0x66
#define OIIOOIII	0x67
#define OIIOIOOO	0x68
#define OIIOIOOI	0x69
#define OIIOIOIO	0x6A
#define OIIOIOII	0x6B
#define OIIOIIOO	0x6C
#define OIIOIIOI	0x6D
#define OIIOIIIO	0x6E
#define OIIOIIII	0x6F

#define OIIIOOOO	0x70
#define OIIIOOOI	0x71
#define OIIIOOIO	0x72
#define OIIIOOII	0x73
#define OIIIOIOO	0x74
#define OIIIOIOI	0x75
#define OIIIOIIO	0x76
#define OIIIOIII	0x77
#define OIIIIOOO	0x78
#define OIIIIOOI	0x79
#define OIIIIOIO	0x7A
#define OIIIIOII	0x7B
#define OIIIIIOO	0x7C
#define OIIIIIOI	0x7D
#define OIIIIIIO	0x7E
#define OIIIIIII	0x7F

#define IOOOOOOO	0x80
#define IOOOOOOI	0x81
#define IOOOOOIO	0x82
#define IOOOOOII	0x83
#define IOOOOIOO	0x84
#define IOOOOIOI	0x85
#define IOOOOIIO	0x86
#define IOOOOIII	0x87
#define IOOOIOOO	0x88
#define IOOOIOOI	0x89
#define IOOOIOIO	0x8A
#define IOOOIOII	0x8B
#define IOOOIIOO	0x8C
#define IOOOIIOI	0x8D
#define IOOOIIIO	0x8E
#define IOOOIIII	0x8F

#define IOOIOOOO	0x90
#define IOOIOOOI	0x91
#define IOOIOOIO	0x92
#define IOOIOOII	0x93
#define IOOIOIOO	0x94
#define IOOIOIOI	0x95
#define IOOIOIIO	0x96
#define IOOIOIII	0x97
#define IOOIIOOO	0x98
#define IOOIIOOI	0x99
#define IOOIIOIO	0x9A
#define IOOIIOII	0x9B
#define IOOIIIOO	0x9C
#define IOOIIIOI	0x9D
#define IOOIIIIO	0x9E
#define IOOIIIII	0x9F

#define IOIOOOOO	0xA0
#define IOIOOOOI	0xA1
#define IOIOOOIO	0xA2
#define IOIOOOII	0xA3
#define IOIOOIOO	0xA4
#define IOIOOIOI	0xA5
#define IOIOOIIO	0xA6
#define IOIOOIII	0xA7
#define IOIOIOOO	0xA8
#define IOIOIOOI	0xA9
#define IOIOIOIO	0xAA
#define IOIOIOII	0xAB
#define IOIOIIOO	0xAC
#define IOIOIIOI	0xAD
#define IOIOIIIO	0xAE
#define IOIOIIII	0xAF

#define IOIIOOOO	0xB0
#define IOIIOOOI	0xB1
#define IOIIOOIO	0xB2
#define IOIIOOII	0xB3
#define IOIIOIOO	0xB4
#define IOIIOIOI	0xB5
#define IOIIOIIO	0xB6
#define IOIIOIII	0xB7
#define IOIIIOOO	0xB8
#define IOIIIOOI	0xB9
#define IOIIIOIO	0xBA
#define IOIIIOII	0xBB
#define IOIIIIOO	0xBC
#define IOIIIIOI	0xBD
#define IOIIIIIO	0xBE
#define IOIIIIII	0xBF

#define IIOOOOOO	0xC0
#define IIOOOOOI	0xC1
#define IIOOOOIO	0xC2
#define IIOOOOII	0xC3
#define IIOOOIOO	0xC4
#define IIOOOIOI	0xC5
#define IIOOOIIO	0xC6
#define IIOOOIII	0xC7
#define IIOOIOOO	0xC8
#define IIOOIOOI	0xC9
#define IIOOIOIO	0xCA
#define IIOOIOII	0xCB
#define IIOOIIOO	0xCC
#define IIOOIIOI	0xCD
#define IIOOIIIO	0xCE
#define IIOOIIII	0xCF

#define IIOIOOOO	0xD0
#define IIOIOOOI	0xD1
#define IIOIOOIO	0xD2
#define IIOIOOII	0xD3
#define IIOIOIOO	0xD4
#define IIOIOIOI	0xD5
#define IIOIOIIO	0xD6
#define IIOIOIII	0xD7
#define IIOIIOOO	0xD8
#define IIOIIOOI	0xD9
#define IIOIIOIO	0xDA
#define IIOIIOII	0xDB
#define IIOIIIOO	0xDC
#define IIOIIIOI	0xDD
#define IIOIIIIO	0xDE
#define IIOIIIII	0xDF

#define IIIOOOOO	0xE0
#define IIIOOOOI	0xE1
#define IIIOOOIO	0xE2
#define IIIOOOII	0xE3
#define IIIOOIOO	0xE4
#define IIIOOIOI	0xE5
#define IIIOOIIO	0xE6
#define IIIOOIII	0xE7
#define IIIOIOOO	0xE8
#define IIIOIOOI	0xE9
#define IIIOIOIO	0xEA
#define IIIOIOII	0xEB
#define IIIOIIOO	0xEC
#define IIIOIIOI	0xED
#define IIIOIIIO	0xEE
#define IIIOIIII	0xEF

#define IIIIOOOO	0xF0
#define IIIIOOOI	0xF1
#define IIIIOOIO	0xF2
#define IIIIOOII	0xF3
#define IIIIOIOO	0xF4
#define IIIIOIOI	0xF5
#define IIIIOIIO	0xF6
#define IIIIOIII	0xF7
#define IIIIIOOO	0xF8
#define IIIIIOOI	0xF9
#define IIIIIOIO	0xFA
#define IIIIIOII	0xFB
#define IIIIIIOO	0xFC
#define IIIIIIOI	0xFD
#define IIIIIIIO	0xFE
#define IIIIIIII	0xFF


#define LOWEST_BIT 	b00000001
#define HIGHEST_BIT	b10000000
#define FORWARDS 1
#define BACKWARDS 0xFF

