
#include "types.h"
#include "genlit.h"
#include "displit.h"
#include "genfont.h"
#include "gendisp.h"


#define L_MODULE_X 1
#define R_MODULE_X 80
/****

MatrixDispOrigins ModuleOrigins[]=	{

											{L_MODULE_X,   5},
											{R_MODULE_X,   5},

											{L_MODULE_X,  30},
											{R_MODULE_X,  30},

											{L_MODULE_X,  55},
											{R_MODULE_X,  55},

											{L_MODULE_X,  80},
											{R_MODULE_X,  80},

											{L_MODULE_X,  105},
											{R_MODULE_X,  105},

											{ZERO,ZERO}	// end indicator
																		};
****/

MatrixDispOrigins ModuleOrigins[]=	{

											{L_MODULE_X,   5},


											{L_MODULE_X,  30},


											{L_MODULE_X,  55},


											{L_MODULE_X,  80},


											{L_MODULE_X,  105},


											{ZERO,ZERO}	// end indicator
																			};

MatrixDispLayout DispLayout = {
																ModuleOrigins,
																DOWN,
																RIGHT,
																FOUR
															};

