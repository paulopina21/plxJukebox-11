

#include "EffectBase.h"
#include "angelscript.h"

void EffectBase::RegisterScriptInterface( class asIScriptEngine* pScriptEngine )
{
	int r;

	//---------------------------------------------------------------------------
	// Register the base effect class
	r = pScriptEngine->RegisterObjectType( "EffectBase", 0, asOBJ_REF );//	 assert(r >= 0);
	r = pScriptEngine->RegisterObjectBehaviour( "EffectBase", asBEHAVE_ADDREF, "void f()", asMETHOD( EffectBase, AddRef ), asCALL_THISCALL ); //assert(r >= 0);
	r = pScriptEngine->RegisterObjectBehaviour( "EffectBase", asBEHAVE_RELEASE, "void f()", asMETHOD( EffectBase, Release ), asCALL_THISCALL ); //assert(r >= 0);
}
