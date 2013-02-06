

#ifndef _MESH_H_
#define _MESH_H_

#include "Renderer.h"
#include <string>

using namespace std;

class Mesh
{
public:
		Mesh();
		void CreateTextMesh( string& InString, bool bCentered = true );

		void AddRef();
		void Release();
		LPD3DXMESH GetMesh() { return m_pMesh; };
protected:
		~Mesh();
		int m_iRefCount;

		LPD3DXMESH	m_pMesh;

};

inline Mesh* Mesh_Factory()
{
	// The class constructor is initializing the reference counter to 1
	return new Mesh();
}

#endif
