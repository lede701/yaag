#ifndef H_XADUISOUNDENGINE
#define H_XADUISOUNDENGINE

#include <xaudio2.h>
#include <xaudio2fx.h>
#include <deque>
#include "ISound.h"
#include "NullLogger.h"

#define MAXXAUD 16

#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'

namespace Zaxis{ namespace Sound
{
	using std::deque;

	class XAudioSound :
		public ISound
	{
	private:
		struct auNode
		{
			int Id;
			float Volume;
		};
	private: 
		IXAudio2* pxa;
		IXAudio2MasteringVoice * pmv;

		bool _isAudio;
		LPLOGGER _log;

		auNode fileQueue[MAXXAUD];
		UINT qFront;
		UINT qBack;

		IXAudio2SourceVoice* sounds[MAXXAUD];

	public:
		XAudioSound();
		XAudioSound(LPLOGGER log);
		virtual ~XAudioSound();

		virtual void Init();

		virtual bool PlaySound(int Id, float vol);
		virtual LPENGINE SetLog(LPLOGGER log);
		virtual LPLOGGER Log();
		virtual LPLOGGER Log(std::string line);
		virtual LPLOGGER WriteLine(std::string line);

		TCHAR* GetWinFileName(int Id);
		HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkData);
		HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);
		void ClearChannel(unsigned int Id);

		virtual void Update();
		virtual int RunEngine();
		virtual bool IsRunning();

	};

} }// End namespace Zaxis::Sound

#endif