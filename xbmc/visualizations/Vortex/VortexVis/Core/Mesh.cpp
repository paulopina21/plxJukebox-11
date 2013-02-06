

#include "Mesh.h"
#include <new>
#include <stdio.h>

Mesh::Mesh()
{
	m_iRefCount = 1;
	m_pMesh = NULL;
}

Mesh::~Mesh()
{
	if ( m_pMesh )
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//--------------------
// reference counting
//--------------------

void Mesh::AddRef()
{
	m_iRefCount++;
}

void Mesh::Release()
{
	if ( --m_iRefCount == 0 )
		delete this;
}

void Mesh::CreateTextMesh( string& InString, bool bCentered )
{
	if ( m_pMesh )
	{
		m_pMesh->Release();
	}

	m_pMesh = Renderer::CreateD3DXTextMesh( InString.c_str(), bCentered );
}
