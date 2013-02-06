

#ifndef _DEBUG_CONSOLE_H_
#define _DEBUG_CONSOLE_H_


class DebugConsole
{
public:
	static void Log( const char* pText, ... );
	static void Warn( const char* pText, ... );
	static void Error( const char* pText, ... );
	static void Render();
	static void Init();
};
#endif
