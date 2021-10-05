/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: errcolInternalLogAcknowledge.c
 * Author: David Blackburn
 * Created: May 17, 2013
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
/* Log that an error was acknowledged 								*/
/********************************************************************/


/* Check for null pointer		DONE and TESTED DFB 20130715 */

/* Generate display string		DONE and TESTED DFB 20131219 */

/* Add ack to logbook			DONE and TESTED DFB 20131219 */
	/* Set error if error		DONE and TESTED DFB 20130715 */


unsigned short errcolInternalLogAcknowledge(	unsigned long pSourceName, 
												unsigned short ErrorID, 
												unsigned long pErrorString, 
												struct ErrorCollector_typ* t)
{
	
/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Generate DisplayString						*/
/************************************************/

STRING DisplayString[ERRCOL_STRLEN_DISPLAYSTRING+1];

errcolIntGenerateDisplayString(	(UDINT)DisplayString, 
								ERRCOL_STRLEN_DISPLAYSTRING,
								0, 
								pSourceName, 
								ErrorID, 
								pErrorString );


/************************************************/
/* Add error to logbook							*/
/************************************************/

UINT Status;
StrExtArgs_typ Args;

Args.s[0]=	(UDINT)&(DisplayString);

Status=	logInfo( t->IN.CFG.LoggerName, ErrorID, "Acknowledged %s", (UDINT)&(Args) );

if( Status != 0 ){
	errcolInternalSetError( Status, t );
}


return Status;


} // End Fn //
