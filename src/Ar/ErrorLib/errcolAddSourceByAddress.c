/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: errcolAddSourceByAddress.c
 * Author: David Blackburn
 * Created: November 22, 2011
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


/************************************************************************************************************/
/* Add a source to the ErrorCollector by providing addresses. This relaxes the restriction on data types	*/
/************************************************************************************************************/


/* Check for null pointers						DONE and TESTED DFB 20130715 */
/* Check for uninitialized ErrorCollector		DONE and TESTED DFB 20130715 */
/* Check for full ErrorCollector				DONE and TESTED DFB 20130715 */
/* Add source									DONE and TESTED DFB 20130715 */


unsigned short errcolAddSourceByAddress(	unsigned long pSourceName, 
											unsigned long pErrorActive, 
											unsigned long pErrorString, 
											unsigned long pErrorID, 
											unsigned long pAcknowledge, 
											struct ErrorCollector_typ* t)
{
	

/********************************************************************************************************

This function will add a source to the list of sources to check for errors.

pError is the address of a BOOL variable used to indicate the presence of an error with the source.
pErrorID is the address of a UINT variable for the source ErrorID.
pErrorString is the address of a STRING variable for the source ErrorString.
pAcknowledge is the address of a BOOL variable used to acknowledge errors.
pSourceName is the address of a STRING variable containing the name of the source.
t is an IN_OUT variable for the ErrorCollector structure.


Sample Function Calls:

ST:	errcolAddSourceByAddress(	ADR(FunctionBlockInstance.Error),
								ADR(FunctionBlockInstance.ErrorID),
								ADR(FunctionBlockInstance.ErrorString),
								ADR(FunctionBlockInstance.AcknowledgeError),
								ADR('FunctionBlockInstance'),
								gErrorCollector);

C:	errcolAddSourceByAddress(	(UDINT)&(FunctionBlockInstance.Error),
								(UDINT)&(FunctionBlockInstance.ErrorID),
								(UDINT)&(FunctionBlockInstance.ErrorString),
								(UDINT)&(FunctionBlockInstance.AcknowledgeError),
								(UDINT)&('FunctionBlockInstance'),
								&gErrorCollector);

********************************************************************************************************/


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


if( !(t->Internal.Initialized) ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_NOTINIT, t );
	
	return (UINT)ERRCOL_ERR_NOTINIT;
	
} // ErrorCollector not initialized //


if( pErrorActive == 0 ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_INVALIDINPUT, t);
	
	errcolInternalAddError(	1, 
							(UDINT)&(t->Internal.Timestamp),
							(UDINT)&(t->Internal.pSource[0].SourceName),
							(UDINT)&(t->Internal.pSource[0].SourceTask),
							t->OUT.STAT.ErrorID,
							t->Internal.pSource[0].pErrorString,
							t->Internal.pSource[0].pAcknowledge,
							t );
	
	if( !t->IN.CFG.DisableLogging ){
		errcolInternalLogError(	(UDINT)&(t->Internal.pSource[0].SourceName),
								t->OUT.STAT.ErrorID,
								t->Internal.pSource[0].pErrorString,
								t );
	}
								
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Check for full ErrorCollector				*/
/************************************************/

if( t->Internal.NumSources >= t->IN.CFG.MaxSources ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_FULLSOURCES, t);
	
	errcolInternalAddError(	1, 
							(UDINT)&(t->Internal.Timestamp),
							(UDINT)&(t->Internal.pSource[0].SourceName),
							(UDINT)&(t->Internal.pSource[0].SourceTask),
							t->OUT.STAT.ErrorID,
							t->Internal.pSource[0].pErrorString,
							t->Internal.pSource[0].pAcknowledge,
							t );
	
	if( !t->IN.CFG.DisableLogging ){
		errcolInternalLogError(	(UDINT)&(t->Internal.pSource[0].SourceName),
								t->OUT.STAT.ErrorID,
								t->Internal.pSource[0].pErrorString,
								t );
	}
								
	return (UINT)ERRCOL_ERR_FULLSOURCES;
	
} // Full ErrorCollector //


/************************************************/
/* Add source to ErrorCollector					*/
/************************************************/

UINT	iSource;

iSource=	t->Internal.NumSources;
t->Internal.NumSources++;

t->Internal.pSource[iSource].pErrorActive=	pErrorActive;
t->Internal.pSource[iSource].pErrorID=		pErrorID;
t->Internal.pSource[iSource].pErrorString=	pErrorString;
t->Internal.pSource[iSource].pAcknowledge=	pAcknowledge;

memset( &(t->Internal.pSource[iSource].SourceName), 0, sizeof(t->Internal.pSource[iSource].SourceName) );
if( pSourceName != 0 ) strncpy( t->Internal.pSource[iSource].SourceName, (char*)pSourceName, ERRCOL_STRLEN_SOURCENAME);

ST_name(0, t->Internal.pSource[iSource].SourceTask, 0 );


return 0;


} // End Fn //
