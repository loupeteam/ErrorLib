/*
 * File: errcolAddError.c
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
/* User function to add an error to the error list 					*/
/********************************************************************/


/* Check for null pointer				DONE and TESTED DFB 20130729 */

/* Add error to list					DONE and TESTED DFB 20130729 */
	/* Inconsistency					DONE will not be tested */
	/* Not an inconsistency				DONE and TESTED DFB 20130729 */
	
/* Log error							DONE and TESTED DFB 20130729 */

/* Return proper status					DONE and TESTED DFB 20130729 */

	
unsigned short errcolAddError(	unsigned long pSourceName, 
								unsigned long pErrorString, 
								unsigned short ErrorID, 
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
/* Add error to the error list					*/
/************************************************/

UINT	AddStatus, LogStatus, i;

STRING	SourceTask[ERRCOL_STRLEN_SOURCETASK];
memset( &SourceTask, 0, sizeof(SourceTask) );

ST_name( 0, SourceTask, 0 );

for(i=0; i<ERRCOL_MAXITERATIONS; i++){

	AddStatus=	errcolInternalAddError(	0, 
										(UDINT)&(t->Internal.Timestamp),
										pSourceName,
										(UDINT)&(SourceTask),
										ErrorID,
										pErrorString,
										pAcknowledge,
										t );
									
	if( AddStatus != ERRCOL_ERR_INCONSISTENTERROR ) break;
	
} // Try a few times to handle inconsistencies //


/************************************************/
/* Log error									*/
/************************************************/

if( !(t->IN.CFG.DisableLogging) ){

	LogStatus=	errcolInternalLogError( pSourceName,
										ErrorID,
										pErrorString,
										t );

}

							
/* Prioritize InternalAddError status over LogError status */

if( 	(AddStatus != 0) 
	||	(t->IN.CFG.DisableLogging)
	){
	
	return AddStatus;

}
else{

	return LogStatus;

}


} // End Fn //
