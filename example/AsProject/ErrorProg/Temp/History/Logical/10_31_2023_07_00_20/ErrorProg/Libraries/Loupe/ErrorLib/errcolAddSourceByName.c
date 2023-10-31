/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: errcolAddSourceByName.c
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


/************************************************************************************************************************/
/* Add a source to the ErrorCollector by providing a variable name. This requires the variable to have certain elements	*/
/************************************************************************************************************************/


/* Check for null pointers						DONE and TESTED DFB 20130715 */
/* Check for uninitialized ErrorCollector		DONE and TESTED DFB 20130715 */
/* Check for full ErrorCollector				DONE and TESTED DFB 20130715 */
/* Get addresses								DONE and TESTED DFB 20130715 */
	/* pError									DONE and TESTED DFB 20130715 */
	/* pErrorID									DONE and TESTED DFB 20130715 */
	/* pErrorString								DONE and TESTED DFB 20130715 */
	/* pAcknowledge								DONE and TESTED DFB 20130715 */
	/* pSourceName								DONE and TESTED DFB 20130715 */
/* Add source									DONE and TESTED DFB 20130715 */


unsigned short errcolAddSourceByName(unsigned long pSourceName, unsigned long pVarName, struct ErrorCollector_typ* t)
{


/********************************************************************************************************

This function will add a source to the list of items to check for errors.
It uses the PV_xgetadr function to get the address of the configured error elements.


pVarName is the address of a string containing the variable name.
pSourceName is the address of a string containing the source name to display in the logger and error list.
t is an IN_OUT variable for the ErrorCollector structure.


Sample Function Calls:

ST:	errcolAddSourceByName( ADR('gRecMgr'), ADR('Recipe Manager'), gErrorCollector);

C:	errcolAddSourceByName( (UDINT)&("gRecMgr"), (UDINT)&("Recipe Manager"), &gErrorCollector);

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


if( pVarName == 0 ){
	
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

/* Find addresses of variables */

STRING	VarName[ERRCOL_STRLEN_VARNAME + 1];
UDINT	DataLength,
		pErrorActive,
		pErrorID,
		pErrorString,
		pAcknowledge;
UINT	Status;


/* For all VarNames, first copy pVarName, then cat the appropriate ending */
/* Then use PV_xgetadr to get variable address */
/* Then check PV_xgetadr status */
/* If there is an error getting the address of Error, return with an error */
/* If there is an error getting the address of others, continue */


/* Error */

strncpy( VarName, (char*)pVarName, ERRCOL_STRLEN_VARNAME );
strncat( VarName, ".", ERRCOL_STRLEN_VARNAME - strlen(VarName) );
strncat( VarName, t->IN.CFG.StructureElementNames.ErrorActive, ERRCOL_STRLEN_VARNAME - strlen(VarName) );

Status=	PV_xgetadr( VarName, 
					&pErrorActive, 
					&DataLength );

if( Status != 0 ){
	
	errcolInternalSetError( Status, t );

	strncat( t->OUT.STAT.ErrorString, (char*)pVarName, ERRCOL_STRLEN_ERRORSTRING - strlen(t->OUT.STAT.ErrorString) );
	strncat( t->OUT.STAT.ErrorString, ".", ERRCOL_STRLEN_ERRORSTRING - strlen(t->OUT.STAT.ErrorString) );
	
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
	
	return Status;
	
}
	

/* ErrorID */

strncpy( VarName, (char*)pVarName, ERRCOL_STRLEN_VARNAME );
strncat( VarName, ".", ERRCOL_STRLEN_VARNAME - strlen(VarName) );
strncat( VarName, t->IN.CFG.StructureElementNames.ErrorID, ERRCOL_STRLEN_VARNAME - strlen(VarName) );

Status=	PV_xgetadr( VarName, 
					&pErrorID, 
					&DataLength );
	

/* ErrorString */

strncpy( VarName, (char*)pVarName, ERRCOL_STRLEN_VARNAME );
strncat( VarName, ".", ERRCOL_STRLEN_VARNAME - strlen(VarName) );
strncat( VarName, t->IN.CFG.StructureElementNames.ErrorString, ERRCOL_STRLEN_VARNAME - strlen(VarName) );

Status=	PV_xgetadr( VarName, 
					&pErrorString, 
					&DataLength );


/* Acknowledge */

strncpy( VarName, (char*)pVarName, ERRCOL_STRLEN_VARNAME );
strncat( VarName, ".", ERRCOL_STRLEN_VARNAME - strlen(VarName) );
strncat( VarName, t->IN.CFG.StructureElementNames.Acknowledge, ERRCOL_STRLEN_VARNAME - strlen(VarName) );

Status=	PV_xgetadr( VarName, 
					&pAcknowledge, 
					&DataLength );


/************************************************/
/* Add source to ErrorCollector					*/
/************************************************/

Status=	errcolAddSourceByAddress( pSourceName, pErrorActive, pErrorString, pErrorID, pAcknowledge, t );


return Status;


} // End fn //
