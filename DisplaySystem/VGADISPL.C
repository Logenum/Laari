#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include "types.h"
#include "genlit.h"
#include "displit.h"
#include "gencomd.h"
#include "gendisp.h"
#include "genfont.h"
#include "fontconv.h"
#include "comdproc.h"
#include "filelogs.h"
#include "genvga.h"

/* local functions */

UINT8	GetBitValue(UINT8, UINT8);
UINT 	PutSegment(UINT8, UINT8);
UINT 	CursorToSegmentRel(UINT8, UINT, UINT8);
UINT 	CursorToSegmentAbs(UINT, UINT, UINT8);

UINT	SimulateMatrixDisplay ( UINT8 *, UINT, MatrixDispLayout *);


UINT8 szGraphText[TWO] = {'\0','\0'};



#define SEGMENT_OFF 0
#define SEGMENT_ON 1



UINT wCursorPixelX = 0; /* global variable for X-cursor coordinate */
UINT wCursorPixelY = 0; /* global variable for Y-cursor coordinate */
UINT wSegmentX = 0;
UINT wSegmentY = 0;


 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  Initializes VGA monitor

		INPUT PARAMETERS:
								-	none


		OUTPUT PARAMETERS:
								-	status


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/
UINT	InitializeDisplay(void)
	{

		UINT wStatus=TRUE;

		int gdriver = DETECT,gmode;
		initgraph (&gdriver,&gmode,"");

		return	wStatus;

	}


 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  stops displaying data and clears VGA monitor

		INPUT PARAMETERS:
								-	none


		OUTPUT PARAMETERS:
								-	status


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/
UINT	ShutdownDisplay(void)
	{

		UINT wStatus=TRUE;

		cleardevice(); /* clear screen, cursor to 0,0 */

		return	wStatus;

	}


 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  Writes Prompt text to VGA monitor into a specific location

		INPUT PARAMETERS:
								-	pointer text string


		OUTPUT PARAMETERS:
								-	status


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/
UINT OutputPrompt(UINT8 *pszInputString)
	{
		UINT	wStatus=TRUE;

			moveto(40,400); /* cursor to prompt location */
			outtext(pszInputString);
			moveto(40,420); /* cursor to keyed text location */

		return wStatus;

	}


 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  Reads user input, stores it and echoes characters to
									screen

		INPUT PARAMETERS:
								-	pointer to text string


		OUTPUT PARAMETERS:
								-	status


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT	ReadUserInput(UINT8 *pszUserInput)

	{

		UINT	wStatus=TRUE;
		UINT	wI1;
		UINT8	cInChar;

		szGraphText[ZERO] = ZERO;



		for (wI1=ZERO;	wI1 < LINE_LEN; wI1++)
			{
				cInChar = getch(); /* single character from keyboard to memory */

				if (cInChar == '\r')
					{
						if (wI1 == ZERO)
							{
								/* <CR> is only character */
								cleardevice(); /* clear screen, cursor to 0,0 */

							}
						pszUserInput[wI1] = ZERO;

						wI1 = LINE_LEN;
					}
				else
					{
						pszUserInput[wI1] = cInChar;
						szGraphText[ZERO] 	= cInChar; /* second char is always '\0' */
					}

				outtext(szGraphText); /* puts text to current cursor position */
			}

		return wStatus;
	}




 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  Writes graphics to PC monitor

		INPUT PARAMETERS:
								-	pointer to display data memory
								-	the length of display data area


		OUTPUT PARAMETERS:
								-	none


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/


UINT OutputDisplayData(UINT8 *psDisplayData, UINT wDispDataLen)
	{
		SimulateMatrixDisplay (psDisplayData, wDispDataLen, &DispLayout);

		return TRUE;

	}

 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  moves cursor to a new, absolute segment-oriented location


		INPUT PARAMETERS:
								-	coordinates as segment values



		OUTPUT PARAMETERS:
								-	none


		USE OF COMMON DATA:
								-	various literals
								-	cursor position is updated

		NOTES:

****************************************************************************/

UINT	CursorToSegmentAbs(UINT wSegX, UINT wSegY, UINT8 cResol)
	{

		wSegmentX = wSegX;
		wSegmentY = wSegY;

		wCursorPixelX = wSegmentX * cResol;
		wCursorPixelY = wSegmentY * cResol;

		moveto(wCursorPixelX, wCursorPixelY);

		return TRUE;

	}



 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  moves cursor to a new, relative segment-oriented location


		INPUT PARAMETERS:
								-	direction value
								-	count of segments


		OUTPUT PARAMETERS:
								-	none


		USE OF COMMON DATA:
								-	various literals
								-	cursor position is updated

		NOTES:

****************************************************************************/

UINT CursorToSegmentRel(UINT8 cDirection,UINT wSegmentCount, UINT8 cResol)
	{
			switch (cDirection)
				{
					case RIGHT:
							wSegmentX += wSegmentCount;
						break;
					case LEFT:
							wSegmentX -= wSegmentCount;
						break;
					case UP:
							wSegmentY -= wSegmentCount;
						break;
					case DOWN:
							wSegmentY += wSegmentCount;
						break;
						default:
						break;
				}

			wCursorPixelX= wSegmentX * cResol;
			wCursorPixelY= wSegmentY * cResol;

			moveto(wCursorPixelX, wCursorPixelY);

		return TRUE;
	}

 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  writes a group of pixels around given location

		INPUT PARAMETERS:
								-	pointer to display data memory
								-	the length of display data area


		OUTPUT PARAMETERS:
								-	none


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT PutSegment(UINT8 cCommand, UINT8 cResol)

	{

		UINT8 cI1;
		UINT8 cI2;
		UINT8	cRes2;

		cRes2 = cResol/TWO;

		for (cI1= 0; cI1 < cResol-ONE; cI1++)
				{
					for (cI2=0; cI2 < cResol-ONE;cI2++)
						{
							if (cCommand == SEGMENT_ON)
								{
									putpixel (wCursorPixelX-cRes2+cI1,
														wCursorPixelY-cRes2+cI2,
														EGA_YELLOW);
								}
							else
								{
									putpixel (wCursorPixelX-cRes2+cI1,
														wCursorPixelY-cRes2+cI2,
														EGA_BLACK);
								}

						}

				}
		return TRUE;
	}


 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  Finds the value of certain bit in certain byte

		INPUT PARAMETERS:
								-	value of byte
								-	sequence number of bit within the byte



		OUTPUT PARAMETERS:
								-	value of the bit


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

unsigned char GetBitValue(UINT8 cByte, UINT8 cBit)
	{

	/* function generity: full */

		unsigned char cTmp1;
		unsigned char cBitValue;


		cTmp1 = cByte >> cBit;

		cBitValue = cTmp1 & ONE;

		return cBitValue;

	}


 /***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	  Outputs pixel graphics to VGA monitor. Reads data from
									display memory, where it has been stored into a matrix
									display "shift register sequence" -order

		INPUT PARAMETERS:
								-	pointer to display memory start
								-	data length in display memory
								-	pointer to simulation layout control structure

		OUTPUT PARAMETERS:
								-	VGA display memory updated


		USE OF COMMON DATA:
								-	various literals

		NOTES:
 ****************************************************************************/

UINT	SimulateMatrixDisplay ( UINT8 *psDispMem,
															UINT	wDataLenInBits,
															MatrixDispLayout *pDispLayout)
	{
		UINT	wStatus=TRUE;
		UINT	wTotalBitCnt=ZERO;
		UINT 	wSliceRow;
		UINT	wBitsInTextSlice;
		UINT	wBitsInModuleSlice;
		UINT	wBitNbr;
		UINT	wByteNbr;
		UINT	wSegmX;
		UINT	wSegmY;
		MatrixDispOrigins *pOrigin;
		UINT8	cBitCnt;
		UINT8	cBitLoc;
		UINT8	cBitValue;
		UINT8	cModuleNbr;
		UINT8 cDirX;
		UINT8 cDirY;
		UINT8	cSize;
		UINT8 *psNextSourceByte;


		UINT 	wModuleSliceBaseBitLoc;

		UINT	wRingLength = 30000; /* large value: property not used here */

		cleardevice(); /* clear screen, cursor to 0,0 */

		wBitsInModuleSlice 	= wMODULE_HW_WIDTH;
		wBitsInTextSlice		= wBitsInModuleSlice * wMODULES_IN_SYSTEM;

		wModuleSliceBaseBitLoc 	=	ZERO;

		cDirX = pDispLayout->cHorUpdDir;
		cDirY = pDispLayout->cVerUpdDir;
		cSize = pDispLayout->cSegmentSize;
		pOrigin = pDispLayout->pModuleOrigin;

		LodVars(	__FILE__,__LINE__,
							"%d, %d, %d",
							wDataLenInBits,
							wBitsInTextSlice,
							wBitsInModuleSlice
						);

		for (cModuleNbr=ZERO; cModuleNbr < wMODULES_IN_SYSTEM; cModuleNbr++)
			{
				wSegmX = pOrigin->wSegmentX;
				wSegmY = pOrigin->wSegmentY;
				pOrigin++;

				/* origin of next module */
				CursorToSegmentAbs(wSegmX, wSegmY, cSize);

				for (wSliceRow=ZERO; wSliceRow < wBLOCKS_IN_DIGIT; wSliceRow++)
					{ 				/* outputs all slices to one module of screen */

						for (wBitNbr=ZERO; wBitNbr < wBitsInModuleSlice; wBitNbr++)

							{ 		/* outputs one text slice to screen */

								if (wTotalBitCnt >= wDataLenInBits)
									{
										return TRUE;
									}

								ConvertBitsToBytesAndBits(wModuleSliceBaseBitLoc + wBitNbr,
																					wRingLength,
																					&wByteNbr,
																					&cBitCnt);
								wTotalBitCnt++;

								cBitLoc 					= SEVEN - cBitCnt;
								psNextSourceByte 	= psDispMem + wByteNbr;

								cBitValue = GetBitValue (*psNextSourceByte, cBitLoc);
								PutSegment(cBitValue, cSize); /* update single segment */

								/* point next segment of same text slice */
								CursorToSegmentRel(cDirX, ONE, cSize);

							}

						CursorToSegmentAbs(wSegmX, wSegmY, cSize); /* current module */
						CursorToSegmentRel(cDirY, wSliceRow+ONE, cSize); /* point to next slice */
						wModuleSliceBaseBitLoc += wBitsInModuleSlice;
					}


			}

		return wStatus;

	}
