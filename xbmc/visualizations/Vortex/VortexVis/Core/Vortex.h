

#ifndef _VORTEX_H_

#include <d3d9.h>

class asIScriptEngine;
class VisTrack;

struct UserSettings
{
	bool RandomPresetsEnabled;
	bool PresetLocked;
	bool TransitionsEnabled;
	bool ShowAudioAnalysis;
	bool StopFirstPreset;
	bool ShowFPS;
	bool ShowDebugConsole;
	float TimeBetweenPresets;
	float TimeBetweenPresetsRand;

	UserSettings()
	{
		RandomPresetsEnabled = true;
		PresetLocked = false;
		TransitionsEnabled = true;
		ShowAudioAnalysis = false;
		StopFirstPreset = true;
		ShowFPS = false;
		ShowDebugConsole = false;
		TimeBetweenPresets = 10.0f;
		TimeBetweenPresetsRand = 0.0f;
	}

};

class Vortex
{
public:
	void Init( LPDIRECT3DDEVICE9 pD3DDevice, int iPosX, int iPosY, int iWidth, int iHeight, float fPixelRatio );
	void Start( int iChannels, int iSamplesPerSec, int iBitsPerSample, const char* szSongName );
	void Shutdown();
	void AudioData( const short* pAudioData, int iAudioDataLength, float* pFreq, int iFreqDataLength );
	void Render();
	void UpdateTrack( VisTrack* pVisTrack );
	void UpdateAlbumArt( char* artFilename );
	void LoadNextPreset();
	void LoadPreviousPreset();
	void LoadRandomPreset();
	void LoadPreset( int PresetId );

	int GetCurrentPresetIndex();
	int GetPresets( char*** Presets );

	UserSettings& GetUserSettings();
	void LoadSettings();
	void SaveSettings();

private:
	bool InitAngelScript();
	asIScriptEngine* m_pScriptEngine;
};

#endif // _VORTEX_H_
