

#ifndef _PRESET_H_

class asIScriptEngine;
class asIScriptContext;
class asIScriptModule;

class Preset
{
public:
	void Init( asIScriptEngine* pScriptEngine, char* pModuleName );
	bool Begin( char* pFilename );
	void Render();
	void End();
	bool IsValid() { return m_bValid; }

	int m_presetId;

private:
	bool	m_bValid;
	char	m_moduleName[32];
	int		m_iRenderFuncId;
	asIScriptEngine* m_pScriptEngine;
	asIScriptModule* m_pModule;
	asIScriptContext* m_pContext;
};

#endif
