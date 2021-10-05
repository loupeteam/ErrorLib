/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: ErrorCollectorFn_Init.c
 * Author: David Blackburn
 * Created: November 18, 2011
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
/* Initialize an ErrorCollector 									*/
/********************************************************************/


/* Check for null pointer					DONE and TESTED DFB 20130715 */

/* Initialize ErrorCollector				DONE and TESTED DFB 20130715 */
	/* Clear OUT and Internal				DONE and TESTED DFB 20130715 */
	/* Check CFG values						DONE and TESTED DFB 20131219 */
	/* Get Timestamp						DONE and TESTED DFB 20130715 */
	/* Allocate memory for sources			DONE and TESTED DFB 20130715 */
	/* Clear allocated memory				DONE and TESTED DFB 20130715 */
	/* Add error collector as source		DONE and TESTED DFB 20130715 */


unsigned short ErrorCollectorFn_Init(struct ErrorCollector_typ* t)
{


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Initialize ErrorCollector					*/
/************************************************/


/* Clear OUT and Internal */

memset( &(t->OUT), 		0,	sizeof(ErrorCollector_OUT_typ) );
memset( &(t->Internal),	0,	sizeof(ErrorCollector_Internal_typ) );


/* Check CFG values */

if( strcmp(t->IN.CFG.ErrorCollectorSourceName, "") == 0 )	strcpy( t->IN.CFG.ErrorCollectorSourceName,	ERRCOL_DEFAULT_ERRCOLSOURCENAME );

if( t->IN.CFG.MaxSources == 0 )	t->IN.CFG.MaxSources=	ERRCOL_DEFAULT_MAXSOURCES;

if( strcmp(t->IN.CFG.StructureElementNames.ErrorActive, "") == 0 )	strcpy( t->IN.CFG.StructureElementNames.ErrorActive, 	ERRCOL_DEFAULT_ELEM_ERRORACTIVE);
if( strcmp(t->IN.CFG.StructureElementNames.ErrorID, "") == 0 )		strcpy( t->IN.CFG.StructureElementNames.ErrorID,		ERRCOL_DEFAULT_ELEM_ERRORID);
if( strcmp(t->IN.CFG.StructureElementNames.ErrorString, "") == 0 )	strcpy( t->IN.CFG.StructureElementNames.ErrorString,	ERRCOL_DEFAULT_ELEM_ERRORSTRING);
if( strcmp(t->IN.CFG.StructureElementNames.Acknowledge, "") == 0 )	strcpy( t->IN.CFG.StructureElementNames.Acknowledge,	ERRCOL_DEFAULT_ELEM_ACKNOWLEDGE);

if( !t->IN.CFG.DisableLogging )
{
	if( strcmp(t->IN.CFG.LoggerName, "") == 0 )	strcpy( t->IN.CFG.LoggerName, ERRCOL_DEFAULT_LOGGERNAME);
}


/* Get the current timestamp */

DTGetTime_typ	GetTime;

memset( &GetTime, 0, sizeof(GetTime) );


GetTime.enable=	1;

DTGetTime(&GetTime);


if( GetTime.status == 0 ){
	
	GenerateTimestamp(	GetTime.DT1,
						(UDINT)t->Internal.Timestamp, 
						sizeof(t->Internal.Timestamp)-1);
	
}


/* Allocate memory for Sources - add 1 extra for error collector errors */

if( TMP_alloc(	(t->IN.CFG.MaxSources + 1) * sizeof(ErrorCollector_Int_Source_typ), 
				(void**)&(t->Internal.pSource) ) != 0 ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_ALLOC, t );
		
	return (UINT)ERRCOL_ERR_ALLOC;	
	
}

/* Clear allocated memory */

memset( t->Internal.pSource, 0, (t->IN.CFG.MaxSources + 1) * sizeof(ErrorCollector_Int_Source_typ) );


/* Add error collector as source */

t->Internal.NumSources=	1;

t->Internal.pSource[0].pErrorActive=	(UDINT)&(t->OUT.STAT.Error);
t->Internal.pSource[0].pErrorID=		(UDINT)&(t->OUT.STAT.ErrorID);
t->Internal.pSource[0].pErrorString=	(UDINT)&(t->OUT.STAT.ErrorString);
t->Internal.pSource[0].pAcknowledge=	(UDINT)&(t->IN.CMD.AcknowledgeError);
strncpy( t->Internal.pSource[0].SourceName, t->IN.CFG.ErrorCollectorSourceName, ERRCOL_STRLEN_SOURCENAME );
ST_name( 0, t->Internal.pSource[0].SourceTask, 0 );


/* DONE */

t->Internal.Initialized=	1;

return 0;


} // End Fn //
