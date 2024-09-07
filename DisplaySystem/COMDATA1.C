#include <stdio.h>
#include <string.h>
#include "genlit.h"
#include "displit.h"

#include "genfont.h"
#include "fontconv.h"
#include "filelogs.h"
#include "gendisp.h"



UINT8 szControl_S[]= {CNTRL_S,'\0'};

const ComdConvTbl CONSTcomdConvTbl[] =

					{
						 "STOP",			STOP_PROGRAM,
						 "stop",			STOP_PROGRAM,
						 "move",			MOVE_TEXT,
						 "right",			ROTATE_STRING_RIGHT,
						 "left",			ROTATE_STRING_LEFT,
						 "blink",			BLINK_DISPLAY,
						 "test1",			TEST1,
						 szControl_S,	STOP_REPETITION,
						 0,						0
					};

