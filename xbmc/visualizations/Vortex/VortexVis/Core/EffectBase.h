

#ifndef _EFFECT_H_
#define _EFFECT_H_

struct IDirect3DTexture9;

class EffectBase
{
public:
	static void RegisterScriptInterface( class asIScriptEngine* );
	EffectBase()
	{
		m_iRefCount = 1;
	}

	virtual ~EffectBase() {};

	void AddRef()
	{
		m_iRefCount++;
	}

	void Release()
	{
		if ( --m_iRefCount == 0 )
			delete this;
	}

	virtual  IDirect3DTexture9* GetTexture() { return 0; }
	virtual  IDirect3DTexture9* GetRenderTarget() { return 0; }

protected:
	int m_iRefCount;
};

template<class A, class B>
B* refCast(A* a)
{
	// If the handle already is a null handle, then just return the null handle
	if( !a ) return 0;

	// Now try to dynamically cast the pointer to the wanted type
	B* b = dynamic_cast<B*>(a);
	if( b != 0 )
	{
		// Since the cast was made, we need to increase the ref counter for the returned handle
		b->AddRef();
	}
	return b;
}

#endif
