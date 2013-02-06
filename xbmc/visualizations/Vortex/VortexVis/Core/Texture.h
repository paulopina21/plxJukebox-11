

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Renderer.h"
#include <string>

using namespace std;

class Texture
{
public:
	Texture();
	void CreateTexture();
	void LoadTexture( string& filename );

	void AddRef();
	void Release();

	LPDIRECT3DTEXTURE9 m_pTexture;
	bool m_renderTarget;

protected:
	~Texture();
	int m_iRefCount;
};

inline Texture* Texture_Factory()
{
	// The class constructor is initializing the reference counter to 1
	return new Texture();
}

#endif
