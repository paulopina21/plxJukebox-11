

#ifndef _MAP_H_
#define _MAP_H_

#include <new.h>
#include "Renderer.h"
#include "EffectBase.h"

class Map : public EffectBase
{
public:
	static void RegisterScriptInterface( class asIScriptEngine* );

	Map();
	~Map();
	void Init();
	void Render();
	void SetValues( unsigned int x, unsigned int y, float uOffset, float vOffset, float r, float g, float b);
	void SetTimed();
	IDirect3DTexture9* GetTexture() { return m_texture; }
	IDirect3DTexture9* GetRenderTarget() { return m_texture; }

private:
	IDirect3DVertexBuffer9*  m_vBuffer;
	IDirect3DIndexBuffer9* m_iBuffer;
	LPDIRECT3DTEXTURE9  m_texture;
	LPDIRECT3DTEXTURE9  m_tex1;
	LPDIRECT3DTEXTURE9  m_tex2;
	int m_iCurrentTexture;
	PosColNormalUVVertex* m_vertices;
	int m_numIndices;
	bool m_timed;
};

#endif
