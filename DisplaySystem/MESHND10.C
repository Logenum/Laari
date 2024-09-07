#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <stdio.h>
#include <bios.h>
#include <string.h>
#include "types.h"
#include "genlit.h"
#include "displit.h"
#include "fontconv.h"
#include "filelogs.h"
#include "gencomd.h"
#include "gendisp.h"
#include "genfont.h"
#include "geninout.h"
#include "comdproc.h"
#include "proc.h"
#include "userif.h"

UINT8 sDisplayMemoryArea[DISP_MEMORY_AREA_SIZE];
UINT8 cTmpDisplayMemoryArea[DISP_MEMORY_AREA_SIZE];

UINT8 szRawInString[LINE_LEN]; /* unmanipulated user input */
UINT8 szInString[LINE_LEN];    /* user input with NULL:s removed */
UINT8 szDataString[LINE_LEN];  /* final ascii data to be converted */
UINT8 bStopProgram    = FALSE;
UINT8 bRepetitionRunning =  FALSE;
UINT8 cOperation;
UINT  wDataLenInBitsRet;
UINT  wInCharNbr;
UINT  wLocation=ONE;

UINT  RemovePreviousData(UINT8 *);


/***************************************************************************

    FUNCTION NAME:  See below

    ABSTRACT:
              Handles received display message.

    INPUT PARAMETERS:

              - pointer to received message data
              - message data area length

    OUTPUT PARAMETERS:

              - none

    USE OF COMMON DATA:

              - some literals

    NOTES:
****************************************************************************/

void UserMesSec(int iSec, int iLength, unsigned char cMes[])
{
		/* finally this function shall operate according to MESSAGE TYPE !! ### */

      LogLoc(__FILE__,__LINE__);
      strncpy(szRawInString,cMes,iLength);

      RemovePreviousData(szInString);


      CheckForCommands( szRawInString,
                        CONSTcomdConvTbl,
                        &cOperation);

      strcpy(szInString,szRawInString);


      ReplaceEndChars(szInString);

      switch (cOperation)
        {
          case STOP_PROGRAM:
            bStopProgram = TRUE;
            LogLoc(__FILE__,__LINE__);
          break;

          case STOP_REPETITION:
            bRepetitionRunning = FALSE;
            wLocation = ONE;
            LodLoc(__FILE__,__LINE__);
          break;

          case ROTATE_STRING_RIGHT:
            /* manipulate data string */
            RotateStringRight(szDataString,ONE);
            bRepetitionRunning = TRUE;
            wLocation++;
            LodLoc(__FILE__,__LINE__);
          break;

          default:
            /* take new input string as a data string */
            RemovePreviousData(szDataString);
            strcpy(szDataString,szInString);
            LogLoc(__FILE__,__LINE__);
          break;

        }


      if (bStopProgram == FALSE)
        {

          ConvStringToDispl( szDataString,
                             sDisplayMemoryArea,
                             &wDataLenInBitsRet,
                             CONSTfontTablesList);

          OutputDisplayData(sDisplayMemoryArea, wDataLenInBitsRet);

          LogLoc(__FILE__,__LINE__);

        }

}



/***************************/

UINT RemovePreviousData(UINT8 *psInDataBuffer)
  {

    /* remove previous data */

    for (wInCharNbr=ZERO; wInCharNbr < LINE_LEN; wInCharNbr++)
      {
        psInDataBuffer[wInCharNbr] = SPACE;
      }

    return TRUE;

  }
