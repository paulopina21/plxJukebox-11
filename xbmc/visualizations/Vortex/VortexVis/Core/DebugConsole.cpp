

#include "DebugConsole.h"
#include "Renderer.h"
#include <stdio.h>

#define NUM_LINES ( 100 )

namespace
{
	struct ConsoleLine
	{
		char	Txt[ 255 ];
		DWORD	Col;
	};

	ConsoleLine Lines[ NUM_LINES ];
	int iCurrentLine = 0;
	char Temp[1024];
	bool bHasError = false;
}

void AddTxt( char* pText, DWORD Col )
{
	int iOffset = 0;
	int len = strlen( pText );
	while ( len > 0 )
	{
		strcpy_s( Lines[ iCurrentLine ].Txt, 255, &pText[ iOffset ] );
		Lines[ iCurrentLine ].Col = Col;
		len -= 254;
		iOffset += 254;
		iCurrentLine = ( iCurrentLine + 1 ) % NUM_LINES;
	}
}

void DebugConsole::Log( const char* pText, ... )
{
	va_list arglist;
	va_start(arglist,pText);
	vsprintf(Temp,pText,arglist);
	va_end(arglist);

	AddTxt( Temp, 0xffffffff );
	OutputDebugStringA( Temp );
}

void DebugConsole::Warn( const char* pText, ... )
{
	va_list arglist;
	va_start(arglist,pText);
	vsprintf(Temp,pText,arglist);
	va_end(arglist);

	AddTxt( Temp, 0xffffff00 );
	OutputDebugStringA( Temp );
}

void DebugConsole::Error( const char* pText, ... )
{
	va_list arglist;
	va_start(arglist,pText);
	vsprintf(Temp,pText,arglist);
	va_end(arglist);

	AddTxt( Temp, 0xffff0000 );
	bHasError = true;
	OutputDebugStringA( Temp );
}

int iLineHeight = 14;

void DebugConsole::Render()
{
//  	if ( bHasError == false )
//  		return;

	int iViewportHeight = Renderer::GetViewportHeight();
	int iLineToDraw = iCurrentLine - 1;
	if ( iLineToDraw < 0 )
		iLineToDraw += NUM_LINES;

	for ( int iLine = NUM_LINES - 1; iLine >= 0; iLine-- )
	{
		Renderer::DrawText( 0, ( float )iViewportHeight - ( ( NUM_LINES - iLine )* iLineHeight ), Lines[ iLineToDraw ].Txt, Lines[ iLineToDraw ].Col );
		iLineToDraw = ( iLineToDraw - 1 );
		if ( iLineToDraw < 0 )
			iLineToDraw += NUM_LINES;
	}
}

void DebugConsole::Init()
{
	for ( int i = 0; i < NUM_LINES; i++ )
	{
		AddTxt( "", 0xffffffff );
	}
}
