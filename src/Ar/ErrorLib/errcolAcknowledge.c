/*
 * File: errcolAcknowledge.c
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
/* Acknowledge an error in the error list							*/
/********************************************************************/


/* Check for null pointer		DONE and TESTED DFB 20130715 */
/* Check valid ErrorIndex		DONE and TESTED DFB 20130715 */
/* Set Acknowledged				DONE and TESTED DFB 20130715 */
/* Log acknowledgement			DONE and TESTED DFB 20130715 */
/* Set pAcknowledge				DONE and TESTED DFB 20130715 */
	

unsigned short errcolAcknowledge(unsigned short ErrorIndex, struct ErrorCollector_typ* t)
{
	
	
/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


if( ErrorIndex > (t->Internal.NumErrors - 1) ){
	
	//errcolInternalSetError( (UINT)ERRCOL_ERR_INVALIDINPUT, t );
	
	return 0;
	
} // Check for invalid ErrorIndex //


/************************************************/
/* Acknowledge error							*/
/************************************************/

/* Set ErrorInfo.Acknowledged */

t->OUT.ErrorInfo[ErrorIndex].Acknowledged=	1;


/* Log acknowledgement */

UINT LogStatus;
LogStatus=	0;
	
if( !(t->IN.CFG.DisableLogging) ){

	LogStatus=	errcolInternalLogAcknowledge(	(UDINT)&t->OUT.ErrorInfo[ErrorIndex].SourceName,
												t->OUT.ErrorInfo[ErrorIndex].ErrorID,
												(UDINT)&t->OUT.ErrorInfo[ErrorIndex].ErrorString,
												t );

}


/* Acknowledge the error at the source */
	
if( t->OUT.ErrorInfo[ErrorIndex].pAcknowledge != 0 ){
	
	*((BOOL*)t->OUT.ErrorInfo[ErrorIndex].pAcknowledge)=	1;
	
}


return LogStatus;


} // End Fn //
