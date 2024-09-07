/* common header file part all display types */

#include "types.h"
#include "genlit.h"

#define DISP_MEMORY_AREA_SIZE 2000
#define LINE_LEN 100

#define CONV_TABLE_END 0
#define MAX_BYTE_TYPES 64
#define MAX_COMMAND_TYPES 20
#define STRINGS_ARE_EQUAL 0
#define STRINGS_ARE_DIFFERENT 0xFF
#define IEC_IN_MAX_LEN 0xFF

/* display operations */


#define DO_NOTHING				 		0
#define BLANK 						 		1
#define BLINK_DISPLAY 		 		2
#define ROTATE_STRING_RIGHT 	3
#define ROTATE_STRING_LEFT 		4
#define	MOVE_TEXT					 		5
#define	TEST1							 		6
#define BIT_SHIFT					 		7

#define STOP_REPETITION 		 98
#define STOP_PROGRAM				 99


typedef struct
	{
		UINT	wHeight; 							/* font height in rows of bytes */
		UINT	wWidthInBits;					/* character width in bits */
		UINT8	*psFontBytes;					/* pointer to first byte of font */

	} FontStruc;

typedef struct
	{
		UINT8 byChar;								/* character to be converted */
		UINT	wFontWidthInBits;			/* font width */
		UINT	wFontHeight;					/* font height */
		UINT8 *psFontData;					/* pointer to actual contents of the font */

	}	FontConvTable;							/* characters and corresponding font data */

typedef struct
	{
		UINT8	cSelectorChar;  					/* to select certain font conv. table */
		FontConvTable *pFontConvTable;	/* pointer to font conversion table */

	}	FontTablesList;


typedef struct
	{
		UINT8	*pszComdStr;					/* pointer to command string */
		UINT8	cComdCode;						/* command code */

	}	ComdConvTbl;								/* 	command strings and corresponding */
																/*	operation codes */

typedef	struct
	{
		UINT	wSegmentX;							/* horizontal coordinate */
		UINT	wSegmentY;							/* vertical coordinate */
		
	}	MatrixDispOrigins;						/* matrix display pixel coordinates */ 

typedef struct
	{
		MatrixDispOrigins *pModuleOrigin;	/* start points of each text line */ 
		UINT8	cVerUpdDir;									/* "line feed" direction */ 
		UINT8	cHorUpdDir;									/* next segment stepping direction */
		UINT8	cSegmentSize;								/* single segment side size in pixels */

	}	MatrixDispLayout;									/* matrix display updating parameters */
