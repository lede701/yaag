#include "NetCrypt.h"

#include <cstdlib>
#include <time.h>

// Encryption headers
/*
#include <aes.h>
#include <base64.h>
#include <modes.h>
#include <filters.h>
*/
#include <iostream>
#include <sstream>

namespace Zaxis{ namespace Network{

	NetCrypt::NetCrypt(std::string iKey, std::string iIv)
	{
		iv = iIv;
		key = iKey;
		_errno = 0;
		_errmsg = "";
	}


	NetCrypt::~NetCrypt()
	{
	}

	std::string NetCrypt::Encrypt(const std::string &data)
	{

		std::string ciphertext;
		std::string b64;

		try
		{
			b64 = data;
			/*
			CryptoPP::AES::Encryption aesEncryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
			CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)iv.c_str());

			CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
			stfEncryptor.Put(reinterpret_cast<const unsigned char*>(data.c_str()), data.length() + 1);
			stfEncryptor.MessageEnd();

			CryptoPP::Base64Encoder bEnc;
			bEnc.Attach(new CryptoPP::StringSink(b64));
			bEnc.Put((byte *)ciphertext.c_str(), ciphertext.length());
			bEnc.MessageEnd();
			*/
		}
		catch (...)
		{
			b64 = "";
			_errno = 1;
			_errmsg = "ERROR: Encryption error NetCrypt->Encrypt(std::string)";
		}

		return b64;
	}

	std::string NetCrypt::Decrypt(const std::string &data)
	{
		std::string decryptedtext = trim(data);
		std::string delim = "\r\n";

		int pos = decryptedtext.find_first_of(delim);
		if (pos == std::string::npos)
		{
			pos = decryptedtext.length();
		}

		std::ostringstream out;
		do
		{
			std::string decFrag = decryptedtext.substr(0, pos);
			try
			{
				/*
				std::string encData;
				std::string decData;
				CryptoPP::Base64Decoder bDec;
				bDec.Attach(new CryptoPP::StringSink(encData));
				bDec.Put((byte *)decFrag.c_str(), decFrag.length());
				bDec.MessageEnd();

				CryptoPP::AES::Decryption aesDecyption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
				CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecyption, (byte*)iv.c_str());

				CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decData));
				stfDecryptor.Put(reinterpret_cast<const unsigned char*>(encData.c_str()), encData.size());
				stfDecryptor.MessageEnd();
				out << trim(decData) << "\r\n";
				//*/
			}
			catch (...)
			{
				decryptedtext = "";
				_errno = 2;
				_errmsg = "ERROR: Decryption error NetCrypt->Decrypt(std::string)";
			}

			if (pos < decryptedtext.length())
			{
				// Trim off the process data
				decryptedtext = decryptedtext.substr(pos + 2, decryptedtext.length());
				pos = decryptedtext.find_first_of(delim);
				// Make sure we get the back data of string
				if (decryptedtext.length() > 0 && pos == std::string::npos)
				{
					pos = decryptedtext.length();
				}
			}
			else
			{
				pos = std::string::npos;
			}
		} while (pos != std::string::npos);
		
		if (out.str().length() > 0)
		{
			decryptedtext = out.str();
		}

		return decryptedtext;
	}

	int NetCrypt::GetErrNo()
	{
		return _errno;
	}

	std::string NetCrypt::GetErrMsg()
	{
		return _errmsg;
	}

	std::string NetCrypt::RandomKey()
	{
		std::string rndKey = "";

		char idx = 0;
		char oIdx = 0;
		time_t currTime;
		time(&currTime);
		srand(currTime);
		for (int i = 0; i < 16; i++)
		{
			// Make sure next character is not the same
			do
			{
				idx = std::rand() % 93 + 33;
			} while (idx == oIdx);
			// Store new character
			rndKey += idx;
			oIdx = idx;
		}

		return rndKey;
	}

	std::string NetCrypt::trim(const std::string s)
	{
		int st = 0;
		int en = s.length() - 1;
		std::string retVal = s;
		if (en > 0)
		{
			bool btrim = true;
			do
			{
				btrim = false;
				if (s[st] == 9 || s[st] == 32 || s[st] == 10 || s[st] == 13)
				{
					st++;
					btrim = true;
				}
				if (st >= s.length())
				{
					break;
				}
			} while (btrim);

			do
			{
				btrim = false;
				if (s[en] == 9 || s[en] == 32 || s[en] == 10 || s[en] == 13 || s[en] == '\0')
				{
					btrim = true;
					en--;
				}
				if (en < 0)
				{
					break;
				}
			} while (btrim);
			en++;
			// Check to see if we have something to trim
			if (st < en)
			{
				retVal = s.substr(st, en - st);
			}
			else
			{
				retVal = "";
			}
		}// Endif valid string size check
		return retVal;
	}

	NetCrypt *NetCrypt::Hello()
	{
		NetCrypt *crypt = new NetCrypt("weneedaspecial02", "ivkeycomplex9761");
		return crypt;
	}

} }// End namespace Zaxis::Network

