#include "types.h"

extern UINT InitializeFontData(void);


extern UINT ConvStringToDispl(  UINT8 *,
                                UINT8 *,
                                UINT  *,
                                FontTablesList *);

extern UINT8 ConvertCharToArrayPtr(UINT8,
                                   FontConvTable *,
                                   UINT8 **,
                                   UINT *,
                                   UINT *);


extern UINT ReplaceEndChars(char *);

extern UINT LocateStringInRing( char *,
                                char *,
                                UINT,
                                UINT);

extern UINT RotateStringRight(UINT8 *, UINT);

extern UINT ConvertBitsToBytesAndBits ( UINT,
                                        UINT,
                                        UINT *,
																				UINT8 *);

extern UINT CopyBitArrayRel(  UINT,
															UINT8 *,
															UINT,
															UINT8 *,
															UINT);

extern UINT CopyBitArrayAbs(  signed char,
															UINT8 *,
															signed char,
															UINT8 *,
															UINT);

extern UINT CopyByteBitsToByteBits  ( UINT8 **,
																			signed char *,
																			UINT8 **,
																			signed char *,
																			UINT8 *
																			);

extern UINT AdjustIntoELmatrixOrder(FontStruc *,
                                    UINT8 *,
                                    UINT *);

extern UINT GetSubFontLocELmatrix1( UINT,
                                    UINT *,
                                    UINT *);


