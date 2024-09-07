#include <stdio.h>
#include <string.h>
#include "genlit.h"
#include "displit.h"
#include "genfont.h"
#include "fontconv.h"
#include "filelogs.h"
#include "gendisp.h"


unsigned char **ppsFont;
UINT8 szTmpString[LINE_LEN];

UINT8 szZeroSubFont[]={ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO};



/***** this file contains routines, that execute font conversions *****/


UINT InitializeFontData(void)
	{

		UINT wI1;


		for (wI1 = 0; wI1 < wDIGITS_IN_SYSTEM; wI1++)
			{
				sSpaceString[wI1] = ' ';
			}


		for (wI1 = 0; wI1 < LINE_LEN; wI1++)
			{
				szTmpString[wI1] = ' ';
			}

		return TRUE;

	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							Updates data area according to given string.



		INPUT PARAMETERS:

							-	pointer to given string
							-	pointer to memory area, which will be updated
							-	pointer to the number of updated bytes
							-	pointer to table, which contain:
								-	special character + font conv table -pairs

		OUTPUT PARAMETERS:

							-	updated memory area
							-	the number of updated bytes
							-	status value (for future use)


		USE OF COMMON DATA:
							-	some literals

		NOTES:
****************************************************************************/

UINT	ConvStringToDispl(	UINT8 *psKeyedString,
													UINT8 *psDisplayMem,
													UINT	*pwDataLenInBitsRet,
													FontTablesList *pFontTables)


	{


		UINT	wI1;

		UINT8	cFontTableListEnd;
		UINT8 cInChar;
		UINT8 wStatus=TRUE;
		UINT wFontWidthInBits;
		UINT wFontHeight;
		UINT8 cI1;
		UINT8 bCharFound;
		FontConvTable *pFontConversionTable;
		FontTablesList *pTableStart;

		*pwDataLenInBitsRet = 0;

		pTableStart = pFontTables;

		for (wI1 = ZERO; wI1 < wDIGITS_IN_SYSTEM; wI1++)
			{
				cInChar = *psKeyedString;

				if (cInChar == ZERO)
					{
						cInChar = ' '; 	/*	add space -characters for unused
																display elements */
					}

				cFontTableListEnd = FALSE;

				pFontTables = pTableStart;

				while (cFontTableListEnd == FALSE)
					{
						if (cInChar == pFontTables->cSelectorChar)
							{
								/* special char found */
								pFontConversionTable 		= pFontTables->pFontConvTable;
								cFontTableListEnd = TRUE;

								/* point char just after special char */
								psKeyedString++;
								cInChar = *psKeyedString;
							}
						else
							{
								pFontTables++;
								if (pFontTables->cSelectorChar == ZERO)
									{
										/* not special character, use default font table */
										pFontConversionTable = pTableStart->pFontConvTable;
										cFontTableListEnd = TRUE;
									}
							}
					}

				for (cI1 = ZERO; cI1 < TWO; cI1++)
					{
						bCharFound =	ConvertCharToArrayPtr(cInChar, 		/* IN */
																			pFontConversionTable,	/* IN */
																			ppsFont,  						/* OUT */
																			&wFontWidthInBits,  	/* OUT */
																			&wFontHeight);				/* OUT */



						if (bCharFound == TRUE)
							{
								cI1 = TWO;
							}
						else
							{
								cInChar = SPACE;
							}
					}

				Fonts[wI1].psFontBytes 	= *ppsFont;
				Fonts[wI1].wHeight			= wFontHeight;
				Fonts[wI1].wWidthInBits	= wFontWidthInBits;


				psKeyedString++;

			}

		AdjustIntoELmatrixOrder  (&Fonts[ZERO],					/* IN */
															psDisplayMem,         /* OUT */
															pwDataLenInBitsRet);  /* OUT */





		return wStatus;
	}






/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							Finds pointer to such data array, that corresponds to
							given databyte.


		INPUT PARAMETERS:

							-	one databyte to be converted.
							-	pointer to conversion table
							-	pointer to pointer which will point to data array
							-	pointer to width of font
							-	pointer to height of font


		OUTPUT PARAMETERS:

							-	pointer which points to data array
							-	width of font
							-	height of font
							-	count of font bytes
							-	result status of the search


		USE OF COMMON DATA:
							-	some literals

		NOTES:
****************************************************************************/

unsigned char ConvertCharToArrayPtr	(UINT8 cChar,
																		FontConvTable *pConvTable,
																		UINT8 **psFont,
																		UINT *pwWidth,
																		UINT *pwHeight
																		)
	{

		UINT8 bCharFound = FALSE;


		while ((pConvTable->byChar != TABLE_END) &&	(bCharFound == FALSE))
			{
				if (pConvTable->byChar == cChar)
					{
						*pwWidth	=	pConvTable->wFontWidthInBits;
						*pwHeight	=	pConvTable->wFontHeight;
						*psFont		=	pConvTable->psFontData;

						bCharFound = TRUE;

					}
				else
					{
						pConvTable++;
					}
			}



		return bCharFound;

	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:

							Updates display memory to a sequence, which can be utilized
							straight by EL matrix display system. Each module has fixed
							bit length, where the slices are adjusted either cutting the
							overflow or adding zeros.



		INPUT PARAMETERS:
							-	pointer to table of font pointers
							-	pointer to display memory start
							-	pointer to amount of copied bits

		OUTPUT PARAMETERS:
							-	amount of copied bits

		USE OF COMMON DATA:
							-	display system parameters (constants)
							-	some literals

		NOTES:
****************************************************************************/

UINT	AdjustIntoELmatrixOrder(FontStruc *pFonts,
														UINT8 *psDispMem,
														UINT	*pwCopiedBits)
	{
		UINT wModuleNbr;
		UINT wSliceNbr;
		UINT wDigitNbr;
		UINT wTargetSlice;
		UINT wStatus=TRUE;
		UINT wSourceFontNbr;
		UINT wSourceFontSliceNbr;
		UINT wNextTargetBitPos;
		UINT wSliceBitOldCount;
		UINT wSliceBitNewCount;
		UINT wCopyBitsCount;
		UINT8	*psSubFont;
		UINT8	wSourceBitPos;
		UINT8 cFontWidthInBytes;
		UINT8 cAddValue;

		wSourceBitPos  		= ZERO;
		wNextTargetBitPos = ZERO; 	/* initial: first bit in buffer */

		for (wModuleNbr=ZERO; wModuleNbr < wMODULES_IN_SYSTEM; wModuleNbr++)
			{
				for (wSliceNbr=ZERO;wSliceNbr < wBLOCKS_IN_DIGIT; wSliceNbr++)
					{
						wSliceBitOldCount = ZERO;
						wSliceBitNewCount	= ZERO;

						for (wDigitNbr=ZERO; wDigitNbr < wDIGITS_IN_MODULE; wDigitNbr++)
							{

								wTargetSlice = 	wDigitNbr
															+ wSliceNbr  * wDIGITS_IN_MODULE
															+ wModuleNbr * wBLOCKS_IN_MODULE;

								GetSubFontLocELmatrix1(	wTargetSlice,
																				&wSourceFontNbr,
																				&wSourceFontSliceNbr);

								wCopyBitsCount = pFonts[wSourceFontNbr].wWidthInBits;

								if (wCopyBitsCount % BITS_IN_BYTE != ZERO)
									{
										cAddValue = ONE;

									}
								else
									{
										cAddValue = ZERO;
									}

								cFontWidthInBytes = wCopyBitsCount/BITS_IN_BYTE + cAddValue;

								psSubFont =	(&pFonts[wSourceFontNbr])->psFontBytes +
														(wSourceFontSliceNbr * cFontWidthInBytes);



								wSliceBitNewCount += wCopyBitsCount;

								if (wSliceBitNewCount > wMODULE_HW_WIDTH)
									{

										LodVars	(__FILE__,__LINE__,
															"%d, %d, %d, %d, %d, %d, %d, %d",
															wModuleNbr,
															wSliceNbr,
															wDigitNbr,
															wCopyBitsCount,
															wSliceBitNewCount,
															wMODULE_HW_WIDTH,
															*pwCopiedBits,
															wNextTargetBitPos
														);

										/* slice owerflow, copy less than char width */
										wCopyBitsCount = wMODULE_HW_WIDTH - wSliceBitOldCount;

										/* assure skip to next slice */
										wDigitNbr = wDIGITS_IN_MODULE;

									}

									LodVars	(__FILE__,__LINE__,
															"%d, %d, %d, %d, %d, %d, %d, %d",
															wModuleNbr,
															wSliceNbr,
															wDigitNbr,
															wCopyBitsCount,
															wMODULE_HW_WIDTH,
															*pwCopiedBits,
															wNextTargetBitPos,
															wTargetSlice
														);


								CopyBitArrayRel(wNextTargetBitPos,
												psDispMem, 	 			/* point same byte all the time */
												wSourceBitPos,		/* point to subfont's starts */
												psSubFont,		 		/* point each subfont in turn */
												wCopyBitsCount);  /* bit amount of each subfont */

								wNextTargetBitPos += wCopyBitsCount;
								*pwCopiedBits			+=  wCopyBitsCount;

								if ((wSliceBitNewCount < wMODULE_HW_WIDTH - ONE) &&
									 (wDigitNbr == wDIGITS_IN_MODULE-ONE))
									{
										/* slice data shortage */

										wCopyBitsCount = wMODULE_HW_WIDTH - wSliceBitNewCount;

										/* fill slice end with zeros */

										CopyBitArrayRel(wNextTargetBitPos,
												psDispMem, 	 			/* point same byte all the time */
												wSourceBitPos,
												szZeroSubFont,
												wCopyBitsCount);

										wNextTargetBitPos += wCopyBitsCount;
										*pwCopiedBits			+=  wCopyBitsCount;

										LodVars	(__FILE__,__LINE__,
															"%d, %d, %d, %d, %d, %d, %d, %d",
															wModuleNbr,
															wSliceNbr,
															wDigitNbr,
															wCopyBitsCount,
															wMODULE_HW_WIDTH,
															*pwCopiedBits,
															wNextTargetBitPos,
															wTargetSlice
														);

									}

								wSliceBitOldCount	 = 	wSliceBitNewCount;



							}
					}
			}


		LodVars(__FILE__,__LINE__,
						"%d",
						*pwCopiedBits);
		return wStatus;

}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
									Finds the order number of font and slice in font
									which are correspondent to given order number
									of target slice.

					example:
					========

							-	two modules
							-	three digits in module
							-	four blocks in digit

						------------------
							A00		B00		C00
							A01		B01		C01
							A02		B02		C02
							A03		B03		C03
						------------------
							A10		B10		C10
							A11		B11		C11
							A12		B12		C12
							A13		B13		C13
						------------------

					source order (= sequence of pointers to fonts):

								A00(A01,A02,A03)B00(B01,B02,B03)C00(C01,C02,C03)
								A10(A11,A12,A13)B10(B11,B12,B13)C10(C11,C12,C13)

					target order (= for display updating):

								A00,B00,C00,A01,B01,C01,A02,B02,C02,A03,B03,C03
								A10,B10,C10,A11,B11,C11,A12,B12,C12,A13,B13,C13



		INPUT PARAMETERS
								-	order number of target slice to be updated
								-	pointer to font order number
								-	pointer to font slice order number

		OUTPUT PARAMETERS:
								-	font order number updated
								-	font slice order number updated
								-	status (for future use)

		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/
UINT GetSubFontLocELmatrix1 (	UINT wTargetNbr,
															UINT *pwFontNbr,
															UINT *pwFontSliceNbr)
	{
		UINT	wReducedTargetNbr;

		*pwFontNbr =	(wTargetNbr/wBLOCKS_IN_MODULE) * wDIGITS_IN_MODULE
									+	wTargetNbr % wDIGITS_IN_MODULE;

		wReducedTargetNbr =
			wTargetNbr-(wTargetNbr/wBLOCKS_IN_MODULE) * wBLOCKS_IN_MODULE;

		*pwFontSliceNbr = wReducedTargetNbr / wDIGITS_IN_MODULE;

		return TRUE;

	}




/*******************/

UINT8	cBitValOne[BITS_IN_BYTE] =
		{
			OOOOOOOI,
			OOOOOOIO,
			OOOOOIOO,
			OOOOIOOO,
			OOOIOOOO,
			OOIOOOOO,
			OIOOOOOO,
			IOOOOOOO
		};

UINT8	cBitValZero[BITS_IN_BYTE] =
		{
			IIIIIIIO,
			IIIIIIOI,
			IIIIIOII,
			IIIIOIII,
			IIIOIIII,
			IIOIIIII,
			IOIIIIII,
			OIIIIIII
		};


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  		Copies contents started from given bit location of
									given byte to another byte to given bit location

		INPUT PARAMETERS:
								-	pointer to input byte
								-	pointer to input byte bit location
								-	pointer to output byte
								-	pointer to output byte bit location
								-	pointer to maximum value of bits to be copied
									-	Output: actual number of copied bits

		OUTPUT PARAMETERS:
								-	input byte updated
								-	output byte updated
								-	number of first not-used input bit
									-	"zero" means: byte end reached
								-	number of first not-copied output bit
									-	"zero" means: byte end reached
								-	amount of copied bits
								-	status (for future use)

		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/


UINT	CopyByteBitsToByteBits	(	UINT8 **ppcInputByte,
																signed char *pcInputPos,
																UINT8 **ppcOutputByte,
																signed char *pcOutputPos,
																UINT8 *pcBitCount
															)



	{
		UINT8 cI1;
		UINT8 cInputByteTmp;
		UINT8 cBitPosDiff;
		UINT8	cCopyLen;
		UINT8 cOutPos;
		UINT8 cSourceLeads;




		if (*pcInputPos >= BITS_IN_BYTE)
			{
				return FALSE;
			}

		if (*pcInputPos < ZERO)
			{
				return FALSE;
			}

		if (*pcOutputPos >= BITS_IN_BYTE)
			{
				return FALSE;
			}

		if (*pcOutputPos < ZERO)
			{
				return FALSE;
			}



		cInputByteTmp = **ppcInputByte;


		if ( (*pcInputPos - *pcOutputPos) > ZERO)
			{
				cSourceLeads = TRUE;
				cBitPosDiff = *pcInputPos - *pcOutputPos;
			}
		else
			{
				cSourceLeads = FALSE;
				cBitPosDiff = *pcOutputPos - *pcInputPos;

			}


		if (cSourceLeads == TRUE)
			{

				/*  input byte:		7-xx---0 	*/
				/*	output byte:	7---xx-0	*/

				cCopyLen = *pcOutputPos+1; /* smaller walue determines */
				/* shift copy-bits parallel to target byte bit locations */
				cInputByteTmp = (**ppcInputByte >> cBitPosDiff);
			}
		else
			{
				/*  input byte:		7---xx-0 	*/
				/*	output byte:	7-xx---0	*/

				/*** OR: ***/

				/*  input byte:		7--xx--0 	*/
				/*	output byte:	7--xx--0	*/

				cCopyLen = *pcInputPos+1;
				cInputByteTmp = (**ppcInputByte << cBitPosDiff);
			}

		if (cCopyLen >= *pcBitCount)
			{
				cCopyLen = *pcBitCount;
			}


		for (cI1 = ZERO; cI1 <= cCopyLen-1; cI1++)
			{
				cOutPos =  *pcOutputPos-cI1;

				if ((cInputByteTmp & cBitValOne[cOutPos]) != ZERO)
					{
						**ppcOutputByte |= cBitValOne[cOutPos];
					}
				else
					{
						**ppcOutputByte &= cBitValZero[cOutPos];
					}
			}
			LodVars (__FILE__,__LINE__,
						 "%X",
						 **ppcOutputByte
						);

		/* BIT number order is decremental !!! (7...0) */

		*pcInputPos 	-=	cCopyLen;
		*pcOutputPos	-=	cCopyLen;

		if (*pcInputPos < ZERO)
			{
				*pcInputPos = BITS_IN_BYTE-1;

					/* BYTE number order is incremental (0...N) */
				(*ppcInputByte)++;
			}

		if (*pcOutputPos < ZERO)
			{
				*pcOutputPos = BITS_IN_BYTE-1;
				(*ppcOutputByte)++;
			}

		*pcBitCount = cCopyLen;



		return TRUE;
	}

/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	Copies given amount of bits from one location to another
								from source to target array


		INPUT PARAMETERS:
								-	bit position value within the first target byte
								-	pointer to the first target byte
								-	bit position value within the first source byte
								-	pointer to the first source byte
								-	number of bits to be copied

		OUTPUT PARAMETERS:
								-	target array updated
								-	status (for future use)

		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT CopyBitArrayAbs (
										signed char	cOutBitPos,
										UINT8	*psOutArray,
										signed char cInBitPos,
										UINT8	*psInArray,
										UINT	wCopyBitCount
									)
	{

		UINT	wI1;
		UINT	wBitsLeft;

		UINT8	cBits;



		if (cOutBitPos >= BITS_IN_BYTE)
			{
				return FALSE;
			}

		if (cInBitPos >= BITS_IN_BYTE)
			{
				return FALSE;
			}




		wI1 = ZERO;

		while (wI1 < wCopyBitCount)

			{
				wBitsLeft = wCopyBitCount - wI1;

				if (wBitsLeft >= BITS_IN_BYTE)
					{
						cBits = BITS_IN_BYTE; /* quess maximum copy length */
					}
				else
					{
						cBits = wBitsLeft;
					}

				CopyByteBitsToByteBits(	&psInArray,
																&cInBitPos,
																&psOutArray,
																&cOutBitPos,
																&cBits);

				wI1 += cBits;


			}
		return TRUE;
	}

/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  	Copies given amount of bits from one location to another
								relatively to source and target array start bytes

		INPUT PARAMETERS:
								-	target array bit position value
								-	pointer to the very first byte of the target array
								-	source array bit position value
								-	pointer to the very first byte of the source array
								-	number of bits to be copied

		OUTPUT PARAMETERS:
								-	target array updated
								-	status (for future use)

		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT CopyBitArrayRel (
										UINT	wOutBitPos,
										UINT8	*psOutArray,
										UINT	wInBitPos,
										UINT8	*psInArray,
										UINT	wCopyBitLen
									)
	{


		UINT8	cInBitCnt;
		signed char	cInBitLoc;
		UINT8	cOutBitCnt;
		signed char	cOutBitLoc;

		UINT8	*psSourceByte;
		UINT8	*psTargetByte;

		UINT	wInByteSeqNbr;
		UINT	wOutByteSeqNbr;

		UINT	wAnyLargeValue = 30000;



		ConvertBitsToBytesAndBits(wInBitPos,
															wAnyLargeValue,
															&wInByteSeqNbr,
															&cInBitCnt);

		cInBitLoc = SEVEN - cInBitCnt;

		ConvertBitsToBytesAndBits(wOutBitPos,
															wAnyLargeValue,
															&wOutByteSeqNbr,
															&cOutBitCnt);

		cOutBitLoc = SEVEN - cOutBitCnt;

		psSourceByte 	= psInArray  + wInByteSeqNbr;
		psTargetByte 	= psOutArray + wOutByteSeqNbr;


		CopyBitArrayAbs(cOutBitLoc,
										psTargetByte,
										cInBitLoc,
										psSourceByte,
										wCopyBitLen);


		return TRUE;
	}

/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  		transforms given bit value location (0....0xFFFF)
									into whole bytes amount and left-over bits amount.
									The bit LOCATION is not the bit amount

		INPUT PARAMETERS:
								-	bit left-to-right location value
								-	length of ring in bits
								-	pointer to byte number of given bit
								-	pointer to number of bit in byte

		OUTPUT PARAMETERS:
								-	pointer-accessible values updated
								-	status (for future use)

		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT	ConvertBitsToBytesAndBits	(	UINT wBitStraightLoc,
																	UINT wRingLenAsBits,
																	UINT *pwByteNbrOfBit,
																	UINT8 *pcBitLocOfBit
																)


	{

		UINT	wWholeBytesCnt;
		UINT8	cBitsRemained;


		/* reduce to ring area */

		wBitStraightLoc =	wBitStraightLoc % (wRingLenAsBits-1);


		wWholeBytesCnt 	= wBitStraightLoc / BITS_IN_BYTE;
		cBitsRemained 	= wBitStraightLoc - (wWholeBytesCnt * BITS_IN_BYTE);


		*pwByteNbrOfBit = wWholeBytesCnt; /* 0 ... N */
		*pcBitLocOfBit 	= cBitsRemained;


		return TRUE;
	}



/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  		replaces text string special end characters, which
									are unnecessary in further operations, with space
									characters

		INPUT PARAMETERS:
								-	pointer to input string


		OUTPUT PARAMETERS:
								-	text string updated


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT ReplaceEndChars(char *pInString)
	{
		UINT wStatus;
		UINT wI1;
		UINT8 cChar;

		for (wI1 = ONE; wI1 < wDIGITS_IN_TEXT; wI1++) /* '\n' as first char OK */
			{
				cChar = *(pInString + wI1);
				switch (cChar)
					{
						case 0x00:
								*(pInString + wI1) = ' ';
							break;

						case '\n':
								*(pInString + wI1) = ' ';
							break;

						default:
							break;
					}
			}

		wStatus = TRUE;
		return wStatus;

	}



/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  		Sets given text to given location in virtual buffer

		INPUT PARAMETERS:
								-	pointer to input string
								-	pointer to output string
								-	length of virtual rotation ring buffer
								-	string start position in virtual buffer

		OUTPUT PARAMETERS:
								-	located string
								-	status (for future use)


		USE OF COMMON DATA:
								-	various literals

		NOTES:
****************************************************************************/

UINT LocateStringInRing(	char *pInString,
													char *pOutString,
													UINT wRingLen,
													UINT wFirstOfStringInRing)

	{
		UINT wStatus;

		char *psStringLoc1;
		char *psDispLoc1;
		UINT wCopyLen1=0;

		char *psStringLoc2;
		char *psDispLoc2;
		UINT wCopyLen2=0;

		UINT8 cOnePart = FALSE;
		UINT8 cTwoParts = FALSE;

		UINT	wFirstOfDisplay;
		UINT	wLastOfDisplay;
		UINT	wFirstOfRing;
		UINT 	wLastOfRing;

		UINT	wLastOfStringInRing;


		UINT	wLeftOverlapLen;
		UINT	wRightOverlapLen;


		if (wRingLen < wDIGITS_IN_SYSTEM)
			{
				return wRingLen;
			}

		wFirstOfRing 		= 0;
		wLastOfRing 		= wRingLen - 1;

		wFirstOfDisplay = 0;
		wLastOfDisplay 	= wDIGITS_IN_SYSTEM - 1;

		wLastOfStringInRing		=  wFirstOfStringInRing + wDIGITS_IN_SYSTEM - 1;

		if (wFirstOfStringInRing >= wRingLen)
			{
				wFirstOfStringInRing = wFirstOfStringInRing % wRingLen;  /* reduce into ring area */
			}
		wLastOfStringInRing	= wFirstOfStringInRing + wDIGITS_IN_SYSTEM - 1;
		wLeftOverlapLen			=	wLastOfStringInRing - wLastOfRing;
		wRightOverlapLen		=	wLastOfDisplay - wFirstOfStringInRing + 1;

		strcpy(pOutString, sSpaceString);   		 /* make string clean */


		if (wFirstOfStringInRing > wLastOfDisplay)
			{
				if (wLastOfStringInRing <= wLastOfRing)
					{
						/* no text */

						psStringLoc1 	= &sSpaceString[ZERO];
						psDispLoc1 		= &pOutString[wFirstOfRing];
						wCopyLen1 		= wDIGITS_IN_SYSTEM;
						cOnePart			= TRUE;
					}
				else
					{
						/* end of text at display start */

						psStringLoc1 	= &pInString[wLastOfDisplay-wLeftOverlapLen+1];
						psDispLoc1 		= &pOutString[0];
						wCopyLen1 		= wLeftOverlapLen;
						cOnePart			= TRUE;
					}
			}


		if (wFirstOfStringInRing <= wLastOfDisplay)
			{
				if (wLastOfStringInRing <= wLastOfRing)
					{
						/* start of text at display end */

						psStringLoc1 	= &pInString[ZERO];
						psDispLoc1 		= &pOutString[wFirstOfStringInRing];
						wCopyLen1 		= wRightOverlapLen;
						cOnePart			= TRUE;
					}
				else
					{
						/* end of text at display start */

						psStringLoc1 	= &pInString[wLastOfDisplay-wLeftOverlapLen+1];
						psDispLoc1 		= &pOutString[wFirstOfDisplay];
						wCopyLen1 		= wLeftOverlapLen;
						cOnePart			= TRUE;

						/* start of text at display end */

						psStringLoc2 	= &pInString[ZERO];
						psDispLoc2 		= &pOutString[wFirstOfStringInRing];
						wCopyLen2 		= wRightOverlapLen;
						cTwoParts 		= TRUE;

					}
			}



		if (cOnePart == TRUE)
			{
				strncpy(psDispLoc1, psStringLoc1, wCopyLen1);
			}

		if (cTwoParts == TRUE)
			{
				strncpy(psDispLoc2, psStringLoc2, wCopyLen2);
			}

		LodVars(__FILE__,__LINE__,
						"%d, %d, %d",
						wDIGITS_IN_SYSTEM,
						wCopyLen1,
						wCopyLen2);

		wStatus = TRUE;
		return wStatus;
	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  		Rotates given string rightwards

		INPUT PARAMETERS:
								-	pointer to input string


		OUTPUT PARAMETERS:
								-	status (for future use)
								-	rotated string

		USE OF COMMON DATA:
								-	various literals
								-	temporary buffer

		NOTES:
****************************************************************************/
UINT RotateStringRight(UINT8 *pszInString, UINT wLoc)
	{
		UINT wStatus=TRUE;
			
			LocateStringInRing(	pszInString,
													szTmpString,
													wDIGITS_IN_SYSTEM,
													wLoc);
			
			strcpy(pszInString, szTmpString);


		return wStatus;
	}
