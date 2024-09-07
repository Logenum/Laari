/*********************************************************************

	File:
	Author: E.Lukkari


	Versions:

	Main program for DPR software PC-version.
	Borland-C.

***********************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <dos.h>
#include <bios.h>
#include <string.h>
#include "types.h"
#include "semmbx.h"
#include "proc.h"
#include "genlit.h"
#include "displit.h"
#include "fontconv.h"
#include "filelogs.h"
#include "gencomd.h"
#include "gendisp.h"
#include "genfont.h"
#include "geninout.h"
#include "comdproc.h"
#define STACK_LEN 5000

int iStack[STACK_LEN];

static BYTE    byMess[IEC_IN_MAX_LEN]; 	  /* Received message */

int baud_rate = 1200;
int iLine     = 0;
int iSec      = 1;


void AplInit(void);
void Empty(void);
void IECinputHandlerTask(void);

void main(void)

 {
	InitializeFontData();
	InitializeDisplay();

  init_console(-1); /* because normal PC is used, not Digiboard */


	/* Intialize kernel */
	ScInit(&iStack[0], STACK_LEN, 0, "MAIN");

	/* Create tasks */

	ScCreateTask(Empty,300,63,100,"EMPTY");
	ScCreateTask(IECinputHandlerTask,300,10,100,"IEC_INPUT_HANDLER");

	AplInit();	/* Create AplSecTask (messages out of IEC interface) */

	ScStartSched();

	/* general initializations */
	enable();
	while (1)
		{
			ScWaitDelay(WAIT_FOREVER);
		}
	ScKill();

}


/********* Empty Task (to assure SCKERNEL proper operation) **********/


void Empty(void)
	{
		unsigned long int wPrintFlag = ZERO;
		enable();
		while(1)
			{
				if (wPrintFlag >= 500000)
					{
						printf ("\n %s, %d",__FILE__,__LINE__);
						wPrintFlag = ZERO;
					}
				else
					{
						wPrintFlag++;
					}
				enable();
				ScWaitDelay(0);
				enable();
			}
	}

/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:  		Main task for message receptions.
									Waits messages to arrive in mailbox.
									

		INPUT PARAMETERS:
								-	none


		OUTPUT PARAMETERS:
								-	none

		USE OF COMMON DATA:
								-	###

		NOTES:
****************************************************************************/
void IECinputHandlerTask (void)
	{
		UINT	wRetVal;    /* Return value for message */
  	UINT	wLen;	      /* Length of the message */
  	int	 	iCnt;

		enable();

  	while (1)
			{
				/* input string initialization */
				for (iCnt = 0; iCnt < IEC_IN_MAX_LEN; iCnt++)
  				{
    				byMess[iCnt] = 0;
  				}

				wLen = IEC_IN_MAX_LEN;
				wRetVal = ScWaitMessage(MB_TO_APL, byMess, &wLen, WAIT_FOREVER);

				/* use message */
				UserMesSec(ZERO, wLen, &byMess);
			}
	}
