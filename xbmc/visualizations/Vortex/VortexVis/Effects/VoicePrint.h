

#ifndef _VOICEPRINT_H_
#define _VOICEPRINT_H_

#include <new.h>
#include "Renderer.h"
#include "EffectBase.h"
#include <string>

using namespace std;

class VoicePrint : public EffectBase
{
public:
	static void RegisterScriptInterface( class asIScriptEngine* );
	VoicePrint();
	~VoicePrint();
	void Init();
	void Render();
	void LoadColourMap( string& filename );
	void SetRect(float minX, float minY, float maxX, float maxY);
	void SetSpeed(float speed);

	IDirect3DTexture9* GetTexture() { return m_texture; }

private:
	int					m_iCurrentTexture;
	LPDIRECT3DTEXTURE9  m_texture;
	LPDIRECT3DTEXTURE9  m_tex1;
	LPDIRECT3DTEXTURE9	m_tex2;
	LPDIRECT3DTEXTURE9  m_colourMap;
	LPDIRECT3DTEXTURE9  m_spectrumTexture;
	float               m_speed;
	float               m_minX;
	float               m_maxX;
	float               m_minY;
	float               m_maxY;
};

#endif
