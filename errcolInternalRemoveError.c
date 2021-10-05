/********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: errcolInternalRemoveError.c
 * Author: David Blackburn
 * Created: December 07, 2011
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
/* Remove an error from the error list 								*/
/********************************************************************/


/* Check for null pointer 			DONE and TESTED DFB 20111213 */

/* Check for invalid inputs			DONE and TESTED DFB 20111213 */

/* Remove error						DONE and TESTED DFB 20111213 */
	/* First error					DONE and TESTED DFB 20111213 */
	/* Middle error					DONE and TESTED DFB 20111213 */
	/* Last error					DONE and TESTED DFB 20111213 */


unsigned short errcolInternalRemoveError(unsigned short ErrorIndex, struct ErrorCollector_typ* t)
{


/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( t == 0 ){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


if( t->Internal.NumErrors == 0 ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_EMPTYLIST, t );
	
	return ERRCOL_ERR_EMPTYLIST;
	
} // Check for empty error list //


if( ErrorIndex > (t->Internal.NumErrors - 1) ){
	
	errcolInternalSetError( (UINT)ERRCOL_ERR_INVALIDINPUT, t );
	
	return ERRCOL_ERR_INVALIDINPUT;
	
} // Check for invalid ErrorIndex //


/************************************************/
/* Remove error from the list					*/
/************************************************/

/* Copy bottom portion of list up one, then clear last entry and decrement NumErrors */


/* Find number of items to move */

UDINT NumToMove;

NumToMove=	(t->Internal.NumErrors - 1) - ErrorIndex;


/* If you need to, copy bottom of list up one */

if( NumToMove > 0 ){

	memcpy( &(t->OUT.ErrorInfo[ErrorIndex]),
			&(t->OUT.ErrorInfo[ErrorIndex + 1]),
			NumToMove * sizeof(t->OUT.ErrorInfo[0]) );
		
}


/* Clear the last entry after moving the items */

memset( &(t->OUT.ErrorInfo[t->Internal.NumErrors - 1]), 0, sizeof(t->OUT.ErrorInfo[0]) );


/* Decrement the number of errors present in the list */

t->Internal.NumErrors--;


return 0;


} // End Fn //
