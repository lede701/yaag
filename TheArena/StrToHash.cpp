#include "StrToHash.h"
//#include <base64.h>
//#include <sha.h>
//#include <hex.h>

using namespace std;

string StrToHash(const string src)
{
	string strHash = src;
	/*
	CryptoPP::SHA256 hash;
	byte digest[CryptoPP::SHA256::DIGESTSIZE];

	// Calculate the hash of provided string
	hash.CalculateDigest(digest, (byte*)src.c_str(), src.length());

	// Convert hash into a hex string
	CryptoPP::Base64Encoder bEncoder;
	CryptoPP::HexEncoder encoder;
	bEncoder.Attach(new CryptoPP::StringSink(strHash));
	bEncoder.Put(digest, sizeof(digest));
	bEncoder.MessageEnd();
	//*/

	return strHash;
}