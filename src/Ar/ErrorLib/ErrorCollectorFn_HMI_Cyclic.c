/*
 * File: ErrorCollectorFn_HMI_Cyclic.c
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
/* Cyclic HMI handling for ErrorCollector 							*/
/********************************************************************/


/* Check for null pointers				DONE and TESTED DFB 20111214 */

/* Refresh error arrays					DONE and TESTED DFB 20121206 */
	/* If NumErrors changes				DONE and TESTED DFB 20111220 */
	/* If SearchString changes			DONE and TESTED DFB 20121206 */
	/* If errors are inconsistent		DONE and TESTED DFB 20111220 */
	
/* Acknowledge errors					DONE and TESTED DFB 20111214 */
	/* One								DONE and TESTED DFB 20111214 */
	/* All								DONE and TESTED DFB 20111214 */


unsigned short ErrorCollectorFn_HMI_Cyclic(struct ErrorCollector_HMI_typ* HMI, struct ErrorCollector_typ* t)
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
/* Populate display array						*/
/************************************************/

UINT iError;


/* If NumErrors changes, refresh */

if( t->Internal.NumErrors != HMI->Internal.OldNumErrors ){
	
	HMI->Internal.OldNumErrors=	t->Internal.NumErrors;
	
	errcolInternalRefreshHMIDisplay( HMI, t );
	
} // NumErrors changed //


/* If SearchString changes, refresh */

else if( strcmp(HMI->SearchString, HMI->Internal.OldSearchString) != 0 ){
	
	strcpy(HMI->Internal.OldSearchString, HMI->SearchString);
	
	errcolInternalRefreshHMIDisplay( HMI, t );
	
} // SearchString changed //


/* If any error is inconsistent (timestamp only), refresh */

else{

	

	for( iError=0; iError<HMI->Internal.NumDisplayErrors; iError++ ){
	
		if( strncmp(	HMI->ErrorList[iError], 
						t->OUT.ErrorInfo[HMI->Internal.ErrorIndex[iError]].Timestamp, 
						ERRCOL_STRLEN_TIMESTAMP ) != 0 ){
						
			errcolInternalRefreshHMIDisplay( HMI, t );
		
		} // strncmp Timestamp //
	
	} // consistency check //


} // check consistency //


/************************************************/
/* Copy string into text box 					*/
/************************************************/

if( HMI->ErrorListbox.IndexDP <= ERRCOL_MAI_ERRORINFO ){
	
	strncpy( HMI->ErrorText, HMI->ErrorList[HMI->ErrorListbox.IndexDP], ERRCOL_STRLEN_DISPLAYSTRING );
	
}


/************************************************/
/* Acknowledge errors							*/
/************************************************/


if( HMI->Acknowledge.CMD ){
	
	HMI->Acknowledge.CMD=	0;
	
	if( HMI->ErrorListbox.IndexDP < HMI->Internal.NumDisplayErrors ){
		
		errcolAcknowledge( HMI->Internal.ErrorIndex[HMI->ErrorListbox.IndexDP], t );
		
	}
		
} // Acknowledge //


if( HMI->AcknowledgeAll.CMD ){
	
	HMI->AcknowledgeAll.CMD=	0;
	
	for( iError=0; iError<HMI->Internal.NumDisplayErrors; iError++){
		
		errcolAcknowledge( HMI->Internal.ErrorIndex[iError], t );
		
	}
	
} // AcknowledgeAll //


return 0;


} // End Fn //
