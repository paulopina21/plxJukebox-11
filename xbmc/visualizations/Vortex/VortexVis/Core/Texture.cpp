

#include "Texture.h"
#include "Renderer.h"
#include <new>
#include <stdio.h>

Texture::Texture()
{
	m_iRefCount = 1;
	m_pTexture = NULL;
	m_renderTarget = false;

} // Constructor

Texture::~Texture()
{
  if (!m_renderTarget)
  {
	  Renderer::ReleaseTexture(m_pTexture);
  }
  else if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

} // Destructor

//--------------------
// reference counting
//--------------------

void Texture::AddRef()
{
	m_iRefCount++;
}

void Texture::Release()
{
	if ( --m_iRefCount == 0 )
		delete this;
}

void Texture::CreateTexture()
{
	m_pTexture = Renderer::CreateTexture(512, 512);
	m_renderTarget = true;

} // CreateTexture

void Texture::LoadTexture(string& filename)
{
	char fullname[ 512 ];
	sprintf_s(fullname, 512, "%s%s", g_TexturePath, filename.c_str() );
	m_pTexture = Renderer::LoadTexture(fullname);

} // LoadTexture
