/*
 * File: errcolInternalRefreshHMIDisplay.c
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of ErrorLib, licensed under the MIT License.
 * 
 */

#include <bur/plctypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

	#include "ErrorLib.h"

#ifdef __cplusplus
};
#endif


#include <string.h>


/********************************************************************/
/* Refresh the HMI display array 									*/
/********************************************************************/


/* Check for null pointers			DONE and TESTED DFB 20111220 */

/* Generate arrays					DONE and TESTED DFB 20121206 */
	
	/* Clear arrays					DONE and TESTED DFB 20121206 */
	
	/* SearchString Empty			DONE and TESTED DFB 20121206 */
		/* Internal ErrorIndex		DONE and TESTED DFB 20121206 */
		/* Error List				DONE and TESTED DFB 20121206 */

	/* SearchString Found			DONE and TESTED DFB 20121206 */
		/* Internal ErrorIndex		DONE and TESTED DFB 20121206 */
		/* Error List				DONE and TESTED DFB 20121206 */

	/* SearchString not Found		DONE and TESTED DFB 20121206 */
		/* Internal ErrorIndex		DONE and TESTED DFB 20121206 */
		/* Error List				DONE and TESTED DFB 20121206 */
		
/* Set Listbox.MaxDP				DONE and TESTED DFB 20111220 */


unsigned short errcolInternalRefreshHMIDisplay(struct ErrorCollector_HMI_typ* HMI, struct ErrorCollector_typ* t)
{


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( 	(HMI == 0)
	||	(t == 0)
	){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointers //


/************************************************/
/* Populate display arrays						*/
/************************************************/

UDINT	iError;
STRING	DisplayString[ERRCOL_STRLEN_DISPLAYSTRING + 1];


/* Clear display arrays */

memset( &(HMI->ErrorList),				0, sizeof(HMI->ErrorList) );
memset( &(HMI->Internal.ErrorIndex),	0, sizeof(HMI->Internal.ErrorIndex) );

HMI->Internal.NumDisplayErrors=	0;


/* Populate errors into display arrays */

for(iError=0; iError < t->Internal.NumErrors; iError++){


	if( HMI->Internal.NumDisplayErrors <= ERRCOL_MAI_ERRORINFO ){


		errcolIntGenerateDisplayString(	(UDINT)DisplayString, 
										ERRCOL_STRLEN_DISPLAYSTRING,
										(UDINT)&(t->OUT.ErrorInfo[iError].Timestamp),
										(UDINT)&(t->OUT.ErrorInfo[iError].SourceName),
										t->OUT.ErrorInfo[iError].ErrorID,
										(UDINT)&(t->OUT.ErrorInfo[iError].ErrorString) );

		if( 	(strcmp(HMI->SearchString, "") == 0)
			||	(strstr(DisplayString, HMI->SearchString) != 0)
			){
		
			HMI->Internal.ErrorIndex[HMI->Internal.NumDisplayErrors]=	iError;

			strncpy( HMI->ErrorList[HMI->Internal.NumDisplayErrors], DisplayString, ERRCOL_STRLEN_DISPLAYSTRING );

			HMI->Internal.NumDisplayErrors++;
			
		} // if( needs to be displayed ) //
					

	} // if( display is not full ) //

		
} // loop through errors //


/************************************************/
/* Set Listbox.MaxDP 							*/
/************************************************/

if( HMI->Internal.NumDisplayErrors == 0 ){
	HMI->ErrorListbox.MaxDP=	0;
}
else{
	HMI->ErrorListbox.MaxDP=	HMI->Internal.NumDisplayErrors - 1;
}


return 0;

	
} // End Fn //
