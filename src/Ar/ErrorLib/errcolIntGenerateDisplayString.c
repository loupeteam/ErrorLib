/*
 * File: errcolIntGenerateDisplayString.c
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
/* Generate a string for display and logging 						*/
/********************************************************************/


/* Check for invalid inputs			DONE and TESTED DFB 20130715 */

/* Generate string					DONE and TESTED DFB 20130715 */


unsigned short errcolIntGenerateDisplayString(	unsigned long pDisplayString, 
												unsigned long DisplayStringLength,
												unsigned long pTimestamp, 
												unsigned long pSourceName, 
												unsigned short ErrorID, 
												unsigned long pErrorString)
{
	
	
/************************************************/
/* Check for invalid inputs						*/
/************************************************/

if( 	(pDisplayString == 0)
	||	(DisplayStringLength == 0)
	){
		
	return (UINT)ERRCOL_ERR_INVALIDINPUT;
		
} // Check for null pointer //


/************************************************/
/* Generate DisplayString 						*/
/************************************************/

STRING	ErrorIDString[6];
BOOL	CatSpace=0, CatColon=0;


strcpy( (char*)pDisplayString, "");

if( pTimestamp != 0 ){
	if( strcmp( (char*)pTimestamp, "" ) != 0 ){
		strncat( (char*)pDisplayString, (char*)pTimestamp, DisplayStringLength - strlen((char*)pDisplayString) );
		strncat( (char*)pDisplayString, ": ", DisplayStringLength - strlen((char*)pDisplayString) );
	}
}

if( pSourceName != 0 ){
	if( strcmp( (char*)pSourceName, "" ) != 0 ){
		strncat( (char*)pDisplayString, (char*)pSourceName, DisplayStringLength - strlen((char*)pDisplayString) );
		CatSpace=	1;
		CatColon=	1;
	}
}

if( ErrorID != 0 ){
	if( CatSpace ) strncat( (char*)pDisplayString, " ", DisplayStringLength - strlen((char*)pDisplayString) );
	brsitoa( (DINT)ErrorID, (UDINT)ErrorIDString );
	strncat( (char*)pDisplayString, ErrorIDString, DisplayStringLength - strlen((char*)pDisplayString) );
	CatColon=	1;
}

if( pErrorString != 0 ){
	if( strcmp( (char*)pErrorString, "" ) != 0 ){
		if( CatColon ) strncat( (char*)pDisplayString, ": ", DisplayStringLength - strlen((char*)pDisplayString) );
		strncat( (char*)pDisplayString, (char*)pErrorString, DisplayStringLength - strlen((char*)pDisplayString) );
	}
}


return 0;


} // End Fn //
