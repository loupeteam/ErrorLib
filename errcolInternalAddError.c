/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: errcolInternalAddError.c
 * Author: David Blackburn
 * Created: November 23, 2011
 ********************************************************************
 * Implementation of library ErrorLib
 ********************************************************************/

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
/* Internal function to add an error to the error list	 			*/
/********************************************************************/


/* Check for null pointer				DONE and TESTED DFB 20130729 */

/* Check for full error collector		DONE and TESTED DFB 20130729 */

/* Add error to list					DONE and TESTED DFB 20130729 */
	/* All info present					DONE and TESTED DFB 20130729 */
	/* Missing info						DONE and TESTED DFB 20130729 */
	/* Input strings too long			DONE and TESTED DFB 20130729 */
	/* Check for consistency			DONE will not be tested */
	

unsigned short errcolInternalAddError(	unsigned short SourceIndex, 
										unsigned long pTimestamp, 
										unsigned long pSourceName, 
										unsigned long pSourceTask, 
										unsigned short ErrorID, 
										unsigned long pErrorString, 
										unsigned long pAcknowledge, 
										struct ErrorCollector_typ* t)
{


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Check for full ErrorCollector				*/
/************************************************/

if( t->Internal.NumErrors > ERRCOL_MAI_ERRORINFO ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_FULLERRORS, t);

	return (UINT)ERRCOL_ERR_FULLERRORS;
	
} // Full ErrorCollector //


/************************************************/
/* Get error info								*/
/************************************************/

STRING Timestamp[ERRCOL_STRLEN_TIMESTAMP];
memset( &Timestamp, 0, sizeof(Timestamp) );

if( pTimestamp != 0 ){
	
	strncpy( Timestamp, (char*)pTimestamp, ERRCOL_STRLEN_TIMESTAMP );
	
}
else{
	
	strncpy( Timestamp, "", ERRCOL_STRLEN_TIMESTAMP );
	
}


STRING SourceName[ERRCOL_STRLEN_SOURCENAME];
memset( &SourceName, 0, sizeof(SourceName) );

if( pSourceName != 0 ){
	
	strncpy( SourceName, (char*)pSourceName, ERRCOL_STRLEN_SOURCENAME );
	
}
else{
	
	strncpy( SourceName, "", ERRCOL_STRLEN_SOURCENAME );
	
}


STRING SourceTask[ERRCOL_STRLEN_SOURCETASK];
memset( &SourceTask, 0, sizeof(SourceTask) );

if( pSourceTask != 0 ){
	
	strncpy( SourceTask, (char*)pSourceTask, ERRCOL_STRLEN_SOURCETASK );
	
}
else{
	
	strncpy( SourceTask, "", ERRCOL_STRLEN_SOURCETASK );
	
}


STRING ErrorString[ERRCOL_STRLEN_ERRORSTRING];
memset( &ErrorString, 0, sizeof(ErrorString) );

if( pErrorString != 0 ){
	
	strncpy( ErrorString, (char*)pErrorString, ERRCOL_STRLEN_ERRORSTRING );
	
}
else{
	
	strncpy( ErrorString, "", ERRCOL_STRLEN_ERRORSTRING );
	
}


/************************************************/
/* Add error to list							*/
/************************************************/


/* Grab local error index and then increment global index to make timing issues less likely */

UINT iError;

iError=	t->Internal.NumErrors;
t->Internal.NumErrors++;


/* Check for consistency */

if( t->Internal.NumErrors != (iError + 1) ){

	/* If inconsistent, do not add error to list and return status to let the calling 
		function know that the error was not added */
			
	errcolInternalSetError( (UINT)ERRCOL_ERR_INCONSISTENTERROR, t );
	
	return ERRCOL_ERR_INCONSISTENTERROR;
	
} // if SourceIndex <> SourceIndex //


/* Add error to list at local error index, not global */

strncpy( t->OUT.ErrorInfo[iError].Timestamp,	Timestamp,		ERRCOL_STRLEN_TIMESTAMP );

t->OUT.ErrorInfo[iError].SourceIndex=	SourceIndex;

strncpy( t->OUT.ErrorInfo[iError].SourceName,	SourceName,		ERRCOL_STRLEN_SOURCENAME );

strncpy( t->OUT.ErrorInfo[iError].SourceTask,	SourceTask,		ERRCOL_STRLEN_SOURCETASK );

t->OUT.ErrorInfo[iError].ErrorID=		ErrorID;

strncpy( t->OUT.ErrorInfo[iError].ErrorString,	ErrorString,	ERRCOL_STRLEN_ERRORSTRING );

t->OUT.ErrorInfo[iError].Acknowledged=	0;

t->OUT.ErrorInfo[iError].pAcknowledge=	pAcknowledge;


return 0;


} // End Fn //
