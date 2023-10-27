/*
 * File: ErrorCollectorFn_Cyclic.c
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
/* Cyclic control of the ErrorCollector 							*/
/********************************************************************/


/* Check for null pointer				DONE and TESTED DFB 20130716 */

/* Check for init						DONE and TESTED DFB 20130716 */

/* Get current timestamp				DONE and TESTED DFB 20130716 */

/* Add errors							DONE and TESTED DFB 20130716 */
	/* Handle NumSources properly		DONE and TESTED DFB 20130716 */
	/* Check pErrorActive == NULL		DONE and TESTED DFB 20130716 */
	/* Check pErrorID == NULL			DONE and TESTED DFB 20130716 */
	/* Check for new Error BOOL			DONE and TESTED DFB 20130716 */
	/* Check for new ErrorID			DONE and TESTED DFB 20130716 */
	/* Log error						DONE and TESTED DFB 20130716 */
		/* Logging enabled				DONE and TESTED DFB 20130716 */
		/* Logging disabled				DONE and TESTED DFB 20130716 */
	/* Add to ErrorInfo					DONE and TESTED DFB 20130716 */
		/* Successful add				DONE and TESTED DFB 20130716 */
		/* Unsuccessful add (full)		DONE and TESTED DFB 20130716 */

/* Acknowledge errors					DONE and TESTED DFB 20130716 */
	/* One								DONE and TESTED DFB 20130716 */
	/* All								DONE and TESTED DFB 20130716 */
	/* Local							DONE and TESTED DFB 20130716 */

/* Remove errors from the list			DONE and TESTED DFB 20130716 */
	/* Invalid SourceIndex				DONE and TESTED DFB 20130716 */
	/* No Source (0)					DONE and TESTED DFB 20130716 */
	/* Source (Nonzero, valid)			DONE and TESTED DFB 20130716 */
	/* No Error							DONE and TESTED DFB 20130716 */
		/* Ack before					DONE and TESTED DFB 20130716 */
		/* Ack after					DONE and TESTED DFB 20130716 */
	/* Different ErrorID				DONE and TESTED DFB 20130716 */
		/* Ack before					DONE and TESTED DFB 20130716 */
		/* Ack after					DONE and TESTED DFB 20130716 */


unsigned short ErrorCollectorFn_Cyclic(struct ErrorCollector_typ* t)
{


/********************************************************************************************************

Functionality:

Search for active alarms and display them in the output string array
Acknowledge any active alarm via a single input
Acknowledge all active alarms via a single input

Add any new alarm to the logger

********************************************************************************************************/


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Check for uninitialized ErrorCollector		*/
/************************************************/

if( !(t->Internal.Initialized) ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_NOTINIT, t );
	
	return (UINT)ERRCOL_ERR_NOTINIT;
	
} // ErrorCollector not initialized //


/************************************************/
/* Get the current timestamp					*/
/************************************************/

DTGetTime_typ	GetTime;

memset( &GetTime, 0, sizeof(GetTime) );


GetTime.enable=	1;

DTGetTime(&GetTime);


if( GetTime.status == 0 ){
	
	GenerateTimestamp(	GetTime.DT1,
						(UDINT)t->Internal.Timestamp, 
						sizeof(t->Internal.Timestamp)-1);
	
}


/************************************************/
/* Add new errors to the list and logger		*/
/************************************************/

BOOL	ErrorActive;
UINT	Status, ErrorID;
UINT	i;


for(i=0; i<(t->Internal.NumSources); i++){
	
	
	/* Reset temporary ErrorActive and ErrorID variables */
	
	ErrorActive=	0;
	ErrorID=		0;
	
	
	/* Check for valid item */
	
	if( t->Internal.pSource[i].pErrorActive != 0 ){
		
		
		ErrorActive=	*((BOOL*)t->Internal.pSource[i].pErrorActive);
		
		
		if( t->Internal.pSource[i].pErrorID != 0 ){
	
			ErrorID=	*((UINT*)t->Internal.pSource[i].pErrorID);
	
		}
		
		
		/* Reset OldErrorActive appropriately */

		if( !ErrorActive ){
	
			t->Internal.pSource[i].OldErrorActive=	0;
	
		} // reset OldError //


		/* Check for a new Error or ErrorID */

		if( ErrorActive ){

			if( 	!(t->Internal.pSource[i].OldErrorActive)
				||	(ErrorID != t->Internal.pSource[i].OldErrorID)
				){
			
		
				/* Save error info so that you know it is now an old error */
			
				t->Internal.pSource[i].OldErrorActive=	ErrorActive;
				t->Internal.pSource[i].OldErrorID=		ErrorID;
				
		
				/* Latch new error to log and add to list */
				
				strcpy( t->Internal.pSource[i].Timestamp, t->Internal.Timestamp );
				
				t->Internal.pSource[i].Log=			!(t->IN.CFG.DisableLogging);
				t->Internal.pSource[i].AddToList=	1;
				
								
			} // New Error or ErrorID
				
		} // Error //
	
	
		/* Log and add to list if necessary */

		if( t->Internal.pSource[i].Log ){
	
			t->Internal.pSource[i].Log=	0;
	
			errcolInternalLogError(	(UDINT)&(t->Internal.pSource[i].SourceName),
									ErrorID,
									t->Internal.pSource[i].pErrorString,
									t );
	
		} // Log //


		if( t->Internal.pSource[i].AddToList ){
	
			Status=	errcolInternalAddError(	i+1, 
											(UDINT)&(t->Internal.pSource[i].Timestamp),
											(UDINT)&(t->Internal.pSource[i].SourceName),
											(UDINT)&(t->Internal.pSource[i].SourceTask),
											ErrorID,
											t->Internal.pSource[i].pErrorString,
											t->Internal.pSource[i].pAcknowledge,
											t );
							
			if( Status == 0 ){
		
				t->Internal.pSource[i].AddToList=	0;
		
			} // Successfully added //
	
		} // AddToList //

		
	} // Valid source //

} // loop through sources looking for errors //


/************************************************/
/* Acknowledge one error						*/
/************************************************/

if( t->IN.CMD.AcknowledgeErrorAtIndex ){

	t->IN.CMD.AcknowledgeErrorAtIndex=	0;
	
	errcolAcknowledge( t->IN.PAR.ErrorIndex, t );

}


/************************************************/
/* Acknowledge all errors						*/
/************************************************/

if( t->IN.CMD.AcknowledgeAllErrors ){
	
	t->IN.CMD.AcknowledgeAllErrors=	0;
	
	for(i=0; i<(t->Internal.NumErrors); i++){
		
		errcolAcknowledge( i, t );
		
	}
	
} 


/************************************************/
/* Acknowledge local errors						*/
/************************************************/

if( t->IN.CMD.AcknowledgeError ){
	
	t->IN.CMD.AcknowledgeError=	0;
	
	t->OUT.STAT.Error=			0;
	t->OUT.STAT.ErrorID=		0;
	strcpy( t->OUT.STAT.ErrorString, "" );

}


/************************************************/
/* Remove errors from the list					*/
/************************************************/

/* Go through the list of errors. 
If the source's Error bit is false or the ErrorID does not match the current ErrorID, 
then remove the error from the list if already acknowledged */

UDINT SourceIndex;

i=0;

while( i < t->Internal.NumErrors ){
	
	
	/* Grab SourceIndex for current error */
	
	SourceIndex=	t->OUT.ErrorInfo[i].SourceIndex;

	
	/* Store current Error and ErrorID info appropriately based on SourceIndex */

	if( SourceIndex > t->Internal.NumSources ){
		
		/* Invalid SourceIndex. Set an error */
	
		ErrorActive=	0;
		errcolInternalSetError( (UINT)ERRCOL_ERR_INVALIDERROR, t );
		
	}
	else if( SourceIndex == 0 ){
	
		/* If SourceIndex == 0, then the error was added without a source.
			Setting the local Error to 0 will force removal based 
			only on the error itself, not the source status. */
			
		ErrorActive=		0;
			
	}
	else{
	
		
		/* If the error has a source, then store the current source status */
		
		if( t->Internal.pSource[SourceIndex-1].pErrorActive != 0 ){
		
			ErrorActive=	*((BOOL*)t->Internal.pSource[SourceIndex-1].pErrorActive);
		
		}
		else{
			
			ErrorActive=	0;
			errcolInternalSetError( (UINT)ERRCOL_ERR_INVALIDSOURCE, t );
			
		}
		
		
		if( t->Internal.pSource[SourceIndex-1].pErrorID != 0 ){
		
			ErrorID=	*((UINT*)t->Internal.pSource[SourceIndex-1].pErrorID);
	
		}
		else{
			
			ErrorID=	0;
			
		}
		
	} // Valid error //
	

	/* Check to see if the error should be removed from the list */
	/* If yes, remove the error and stay here (since the error list
		will be moved up).
		If no, move on */ 
	t->OUT.ErrorInfo[i].Active = ErrorActive && (ErrorID == t->OUT.ErrorInfo[i].ErrorID);
    
	if(		!ErrorActive
		||	(ErrorID != t->OUT.ErrorInfo[i].ErrorID)
		){
      
		if( t->OUT.ErrorInfo[i].Acknowledged ){
	
			errcolInternalRemoveError( i, t );
	
		}
		else{
			
			i++;
		
		}
		
	
	} // Error no longer present //
	
	else{
		
		i++;
		
	}
	
	
} // Loop through error list //


/************************************************/
/* Report ErrorCount							*/
/************************************************/

t->OUT.ErrorCount=	t->Internal.NumErrors;


return 0;


} // End Fn //
