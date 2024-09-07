#include <stdio.h>
#include <string.h>
#include "genlit.h"
#include "displit.h"
#include "fontconv.h"
#include "filelogs.h"


/***************************************************************************

    FUNCTION NAME:  See below

    ABSTRACT:
              Finds value that corresponds to
              given string.



    INPUT PARAMETERS:

              - pointer to string
              - pointer to string-to-command conversion table
              - pointer to command code

    OUTPUT PARAMETERS:

              - command code if found
              - status value (for future use)


    USE OF COMMON DATA:
              - some literals

    NOTES:
****************************************************************************/


UINT  CheckForCommands( UINT8 *pString,
                        ComdConvTbl *pConvTable,
                        UINT8 *pcCommandCode)

{

    UINT8 cStatus;
    UINT  wCompStatus;

    *pcCommandCode = DO_NOTHING; /* initial quess */

    cStatus = FALSE;

    while ((pConvTable->cComdCode != TABLE_END) && (cStatus == FALSE))
      {
        wCompStatus = strcmp(pConvTable->pszComdStr, pString);
        if (wCompStatus == ZERO)
          {
            *pcCommandCode  = pConvTable->cComdCode;
            cStatus   = TRUE;
          }
        else
          {
            pConvTable++;
          }
      }

    return cStatus;

  }


