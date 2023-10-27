/*
 * File: errcolInternalSetError.c
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
/* Set error status on ErrorCollector 								*/
/********************************************************************/


/* Check for null pointer		DONE and TESTED DFB 20111213 */

/* Set Error status				DONE and TESTED DFB 20111213 */
	/* Error					DONE and TESTED DFB 20111213 */
	/* ErrorID					DONE and TESTED DFB 20111213 */
	/* ErrorString				DONE and TESTED DFB 20131219 */


unsigned short errcolInternalSetError(unsigned short ErrorID, struct ErrorCollector_typ* t)
{


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Set error status								*/
/************************************************/

t->OUT.STAT.Error=		1;
t->OUT.STAT.ErrorID=	ErrorID;
	

/* Set ErrorString */

switch( ErrorID ){
	

	/* No error */	

	case 0: strncpy( t->OUT.STAT.ErrorString, "", ERRCOL_STRLEN_ERRORSTRING ); break;


	/* ErrorLib Errors */
	
	case ERRCOL_ERR_ALLOC:				strncpy( t->OUT.STAT.ErrorString, "Error allocating memory for sources.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_INVALIDINPUT:		strncpy( t->OUT.STAT.ErrorString, "Invalid function input.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_NOTINIT:			strncpy( t->OUT.STAT.ErrorString, "Error collector is not initialized.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_FULLSOURCES:		strncpy( t->OUT.STAT.ErrorString, "Error collector is full. No more sources can be handled. Check IN.CFG.MaxSources.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_FULLERRORS:			strncpy( t->OUT.STAT.ErrorString, "Error collector is full. No more errors can be handled.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_INVALIDSOURCE:		strncpy( t->OUT.STAT.ErrorString, "Invalid source. Suggest reinitializing error collector.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_INVALIDERROR:		strncpy( t->OUT.STAT.ErrorString, "Invalid error. Check IN.PAR.ErrorIndex.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_EMPTYLIST:			strncpy( t->OUT.STAT.ErrorString, "Tried to remove an error from an empty list.", ERRCOL_STRLEN_ERRORSTRING ); break;
	case ERRCOL_ERR_INCONSISTENTERROR:	strncpy( t->OUT.STAT.ErrorString, "Tried to add error, but there was an inconsistency. An AcknowledgeAll should be executed when safe.", ERRCOL_STRLEN_ERRORSTRING ); break;
	
	
	/* sys_lib Errors */
	
	case 3300:
	case 3310:
	case 3311:
	case 3312:
	case 3313:
	case 3314:
	case 3324:
	case 3332:
	case 3333:
	case 3336:
	
	case 9133:

	case 14700:
	case 14702:
	case 14703:
	case 14704:
	case 14710:
	case 14714:	strncpy( t->OUT.STAT.ErrorString, "Error with sys_lib library. Check VarName: ", ERRCOL_STRLEN_ERRORSTRING ); break;
	
	case 58200:
	case 58201:
	case 58202:
	case 58203:
	case 58300:
	case 58301:
	case 58302:	strncpy( t->OUT.STAT.ErrorString, "Logging error. Check loggers.", ERRCOL_STRLEN_ERRORSTRING ); break;
	
	default:	strncpy( t->OUT.STAT.ErrorString, "Unknown error.", ERRCOL_STRLEN_ERRORSTRING ); break;
	
} // switch( ErrorID ) //


return 0;


} // End Fn //
