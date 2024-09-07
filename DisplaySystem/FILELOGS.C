#include <stdarg.h>
#include <stdio.h>
#include <bios.h>
#include <io.h>
#include <string.h>
#include "genlit.h"
#include "types.h"


#define LOGFILE_BUFFER_LEN 70

#define LOGFILE "D:logfile.txt"

UINT8 buffer[LOGFILE_BUFFER_LEN];

FILE *File1;
UINT8 szDelimiter1[] = "\n-----------------------------------------------\n";
UINT8 szBlockStartDelimiter[] = "\n--start---\n";
UINT8 szBlockEndDelimiter[] 	= "\n--end-----\n";


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							1. opens certain file
							2. writes given text into that file
							3. closes that file

		INPUT PARAMETERS:

							-	pointer to C-language "printf" format string
							-	list of parameters

		OUTPUT PARAMETERS:
							-	status value (for future use)

		USE OF COMMON DATA:
							-	some literals
		NOTES:
****************************************************************************/



int Logprintf(const char *format, ...)
	{
	 va_list ArgumentPointer;
	 UINT wNrOfChars;

	 File1=fopen (LOGFILE,"a");

	 va_start (ArgumentPointer, format);	/* Variable argument begin */
	 wNrOfChars = vsprintf(buffer, format, ArgumentPointer);
	 va_end (ArgumentPointer);						/* Variable argument end */

	 fputs(buffer,File1);
	 fclose(File1);
	 return (wNrOfChars);									/* According to ANSI */
	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							1. opens certain file
							2. writes date and time of latest COMPILATION into the file
							3. closes that file

		INPUT PARAMETERS:
							-	none

		OUTPUT PARAMETERS:
							-	status value (for future use)

		USE OF COMMON DATA:
							-	some literals
		NOTES:
****************************************************************************/

UINT LogDate(void)
	{

	 File1=fopen (LOGFILE,"a");

	 fprintf(File1,"%s",szDelimiter1);
	 fprintf(File1,"Latest compilation: %s - %s \n",__DATE__,__TIME__);
	 fprintf(File1,"%s",szDelimiter1);
	 fputs(buffer,File1);
	 fclose(File1);
	 return TRUE;									/* According to ANSI */
	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							1. opens certain file
							2. writes the name and line number of current source file
							3. closes that file

		INPUT PARAMETERS:

							-	file name
							-	line number
							-	pointer to C-language "printf" format string
							-	list of parameters

		OUTPUT PARAMETERS:
							-	status value (for future use)

		USE OF COMMON DATA:
							-	some literals
		NOTES:
****************************************************************************/

UINT LogLoc(char *pszFileName, UINT wLineNumber)

	{

	 File1=fopen (LOGFILE,"a");

	 fprintf(File1,"\n %s, line=%d", pszFileName, wLineNumber);


	 fclose(File1);
	 return TRUE;

	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							Dummy version of log routine. Does nothing.
		INPUT PARAMETERS:

							-	file name
							-	line number

		OUTPUT PARAMETERS:
							-	status value (for future use)

		USE OF COMMON DATA:
							-	some literals
		NOTES:
****************************************************************************/

UINT LodLoc(char *pszFileName, UINT wLineNumber)

	{
		pszFileName = pszFileName;
		wLineNumber = wLineNumber;	 
		
		return TRUE;

	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							1. opens certain file
							2. writes the name and line number of current source file
							3. writes given text into that file
							4. closes that file

		INPUT PARAMETERS:

							-	file name
							-	line number

		OUTPUT PARAMETERS:
							-	status value (for future use)

		USE OF COMMON DATA:
							-	some literals
		NOTES:
****************************************************************************/


int LogVars(char *pszFileName,UINT wLineNumber, const char *format, ...)
	{
	 va_list ArgumentPointer;
	 UINT wNrOfChars;

	 File1=fopen (LOGFILE,"a");
	 fprintf(File1,"%s",szBlockStartDelimiter);
	 fprintf(File1," %s, line=%d \n", pszFileName, wLineNumber);

	 va_start (ArgumentPointer, format);	/* Variable argument begin */
	 wNrOfChars = vsprintf(buffer, format, ArgumentPointer);
	 va_end (ArgumentPointer);						/* Variable argument end */

	 fputs(buffer,File1);
	 fprintf(File1,"%s",szBlockEndDelimiter);
	 fclose(File1);
	 return (wNrOfChars);									/* According to ANSI */
	}


/***************************************************************************

		FUNCTION NAME:  See below

		ABSTRACT:
							Dummy version of log routine. Does nothing.
		INPUT PARAMETERS:

							-	file name
							-	line number

		OUTPUT PARAMETERS:
							-	status value (for future use)

		USE OF COMMON DATA:
							-	some literals
		NOTES:
****************************************************************************/


int LodVars(char *pszFileName,UINT wLineNumber, const char *format, ...)
	{
		pszFileName = pszFileName;
		wLineNumber = wLineNumber;
		format = format;

	 return (TRUE);
	}





