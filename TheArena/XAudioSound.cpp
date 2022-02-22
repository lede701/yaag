#include "XAudioSound.h"

namespace Zaxis{ namespace Sound
{

	XAudioSound::XAudioSound()
	{
		SetLog(new Zaxis::Logging::NullLogger());
		Init();
	}

	XAudioSound::XAudioSound(LPLOGGER log)
	{
		SetLog(log);
		Init();
	}

	XAudioSound::~XAudioSound()
	{
		CoUninitialize();
	}

	void XAudioSound::Init()
	{
		/*
		HRESULT hr;
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		_isAudio = false;
		hr = XAudio2Create(&pxa, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (FAILED(hr))
		{
			Log("Failed to create XAdui2");
			return;
		}
		hr = pxa->CreateMasteringVoice(&pmv);
		if (FAILED(hr))
		{
			Log("Failed to create master voice");
			return;
		}

		qFront = 0;
		qBack = 0;

		for (int i = 0; i < MAXXAUD; i++)
		{
			sounds[i] = NULL;
		}

		Log("XAudio2 has been started");
		_isAudio = true;
		*/
	}

	LPENGINE XAudioSound::SetLog(LPLOGGER log)
	{
		_log = log;
		return this;
	}

	LPLOGGER XAudioSound::Log()
	{
		return _log;
	}

	LPLOGGER XAudioSound::Log(std::string line)
	{
		Log()->WriteLine(line);
		return Log();
	}

	LPLOGGER XAudioSound::WriteLine(std::string line)
	{
		Log()->WriteLine(line);
		return Log();
	}

	bool XAudioSound::PlaySound(int iId, float vol)
	{
		bool bRetVal = false;
		// Check if we can add something to the queue
		if ((qBack + 1) % MAXXAUD != qFront)
		{
			auNode node = { iId, vol };
			qBack = (qBack + 1) % MAXXAUD;
			fileQueue[qBack] = node;
		}// Endif qBack is not equal to front of queue

		return bRetVal;
	}

	bool XAudioSound::IsRunning()
	{
		return _isAudio;
	}

	void XAudioSound::Update()
	{
		while (qBack != qFront)
		{
			// Load sound to play
			qFront = (qFront + 1) & MAXXAUD;
			TCHAR* file = GetWinFileName(fileQueue[qFront].Id);
			HANDLE hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (INVALID_HANDLE_VALUE != hFile)
			{
				if (INVALID_SET_FILE_POINTER != SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
				{
					ClearChannel(qFront);
					DWORD dwChunkSize;
					DWORD dwChunkPos;
					FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPos);
					DWORD fileType;
					ReadChunkData(hFile, &fileType, sizeof(DWORD), dwChunkPos);
					if (fileType != fourccWAVE)
					{
						continue;
					}

					FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPos);
					WAVEFORMATEXTENSIBLE wfx;
					ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPos);
					FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPos);
					BYTE* pData = new BYTE[dwChunkSize];
					ReadChunkData(hFile, pData, dwChunkSize, dwChunkPos);
					XAUDIO2_BUFFER buff;
					buff.AudioBytes = dwChunkSize;
					buff.pAudioData = pData;
					buff.Flags = XAUDIO2_END_OF_STREAM;
					pxa->CreateSourceVoice(&sounds[qFront], (WAVEFORMATEX*)&wfx);
					// Set volume of sound voice
					sounds[qFront]->SetVolume(fileQueue[qFront].Volume);
					// Play sound!
					sounds[qFront]->Start(0);
				}
			}
		}
	}

	HRESULT XAudioSound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD &dwChunkSize, DWORD &dwChunkDataPos)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());

		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (hr == S_OK)
		{
			DWORD dwRead;
			if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());

			if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());

			switch (dwChunkType)
			{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
					hr = HRESULT_FROM_WIN32(GetLastError());
				break;

			default:
				if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
					return HRESULT_FROM_WIN32(GetLastError());
			}

			dwOffset += sizeof(DWORD) * 2;

			if (dwChunkType == fourcc)
			{
				dwChunkSize = dwChunkDataSize;
				dwChunkDataPos = dwOffset;
				return S_OK;
			}

			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRIFFDataSize) return S_FALSE;

		}

		return S_OK;
	}

	HRESULT XAudioSound::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());
		DWORD dwRead;
		if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	int XAudioSound::RunEngine()
	{
		Update();
		return 0;
	}

	TCHAR* XAudioSound::GetWinFileName(int Id)
	{
		TCHAR* ptr = NULL;
		switch (Id)
		{
		case 1:
			//ptr = "sound\\intro.wav";
			break;
		case 2:
			//ptr = "sounds\\bow_fire.wav";
			break;
		}

		return ptr;
	}

	void XAudioSound::ClearChannel(unsigned int Id)
	{
		if (sounds[Id] != NULL)
		{
			sounds[Id]->DestroyVoice();
			delete sounds[Id];
			sounds[Id] = NULL;
		}
	}

} }// End namespace Zaxis::Sound

