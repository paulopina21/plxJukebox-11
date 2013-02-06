/*
 * CryptoManager.cpp
 *
 *  Created on: Oct 23, 2012
 *      Author: laureon
 */

#include "CryptoManager.h"

#include <string>

CryptoManager::CryptoManager() {
  // TODO Auto-generated constructor stub

}

CryptoManager::~CryptoManager() {
  // TODO Auto-generated destructor stub
}

void CryptoManager::EncryptText(const CStdString& strKey, const CStdString& strInput, CStdString& strOutput) {
  AutoSeededRandomPool prng;

//  byte key[strKey.size()];
//  key = (byte*)strKey.c_str();
//  memcpy(key,strKey.c_str(),strKey.size());
  //strncpy((char*)key, strKey.c_str(), sizeof(key));

//  byte* key = (byte*) strKey.c_str();

  byte iv[ AES::BLOCKSIZE ];
//  prng.GenerateBlock( iv, sizeof(iv) );
  strncpy((char*)iv, "", sizeof(iv));

  std::string plain = strInput.c_str();
  std::string cipher, encoded;

  /*********************************\
  \*********************************/
//  byte* encoded = new byte[strInput.size()];

//  int size = strInput.size();
//  char plainText[size-1];
//  strncpy((char*)plainText, strInput.c_str(), sizeof(plainText));
//  CLog::Log(LOGDEBUG, "%s: XML: %s ", __FUNCTION__, plain.c_str());

  try
  {
      ECB_Mode< AES >::Encryption e((byte*) strKey.c_str(), strKey.size());
//      e.ProcessData((byte*)plainText, (byte*)plainText, size);
//
 //      e.SetKeyWithIV( key, sizeof(key), iv);
 //     e.SetKey( key, sizeof(key));

      // CFB mode must not use padding. Specifying
      //  a scheme will result in an exception
      CryptoPP::StringSource( plain, true, new CryptoPP::StreamTransformationFilter( e,  new StringSink(cipher)  ) );

//      CBC_Mode<AES>::Encryption cfbEncryption(key, sizeof(key), iv);
//      cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, size);
  }
  catch( CryptoPP::Exception& e )
  {
    CLog::Log(LOGERROR, "%s ERROR: %s ", __FUNCTION__, e.what());
      //cerr << e.what() << endl;
      return;
  }
//  string plainText = "your string";
//  string encoded;
//  StringSource(plainText, true, new Base64Encoder(new
//  StringSink(encoded)));
  // Pretty print cipher text
  CryptoPP::StringSource( cipher, true, new CryptoPP::Base64Encoder( new StringSink( encoded ) ) ); // StringSource
  strOutput = encoded;
}

//void CryptoManager::EncryptText(const CStdString& strKey, const CStdString& strInput, CStdString& strOutput) {
//  AutoSeededRandomPool prng;
//
//  //strKey.trim();
//
//  byte key[16];
//  strncpy((char*)key, strKey.c_str(), strKey.size());
//
//  byte iv[AES::BLOCKSIZE];
//  prng.GenerateBlock(iv, sizeof(iv));
//
////  CLog::Log(LOGDEBUG, "%s: StringKey: %s ", __FUNCTION__, strKey.c_str());
////
////  CLog::Log(LOGDEBUG, "%s: ConvertedKey: %s ", __FUNCTION__, (char*)key);
////
////
////  byte* strCrypted = (byte*) strInput.c_str();//malloc(strInput.size() * sizeof(byte));
////
////  CLog::Log(LOGDEBUG, "%s: XML: %s ", __FUNCTION__, (char*)strCrypted);
////
////  CFB_Mode<AES>::Encryption cfbEncryption(key, sizeof(key), iv);
////  cfbEncryption.ProcessData(strCrypted, (byte*)strInput.c_str(), strInput.size()+1);
////
////  strOutput = (char*)strCrypted;
//
//  //free(strCrypted);
//
//
////    string plainText = "your string";
////    string encoded;
////    StringSource(plainText, true, new Base64Encoder(new StringSink(encoded)));
//
//
//  std::string plainText = strInput.c_str();
//
//  std::string cipher;
//
//  StringSink* sink = new StringSink(cipher);
//  CBC_Mode<AES>::Encryption aes(key, sizeof(key), iv);
////  aes.ProcessData((byte*)plainText, (byte*)plainText, sizeof(plainText));
//  CryptoPP::Base64Encoder* base64_enc = new CryptoPP::Base64Encoder(sink);
//  StreamTransformationFilter* aes_enc = new StreamTransformationFilter(aes, base64_enc);
//  CryptoPP::StringSource source(plainText, true, aes_enc);
//  strOutput = plainText;
//
////  byte output[strInput.Size()];
////  aes_enc->Get(output,0);
//
//}

void CryptoManager::DecryptText(const CStdString& strKey, const CStdString& strInput, CStdString& strOutput) {
  AutoSeededRandomPool prng;

  byte key[AES::DEFAULT_KEYLENGTH];
  strncpy((char*)key, strKey.c_str(), sizeof(key));

  byte iv[ AES::BLOCKSIZE ];
  prng.GenerateBlock( iv, sizeof(iv) );

  std::string recovered = strInput.c_str();
  std::string cipher;

  try
  {
      CFB_Mode< AES >::Decryption d;
      d.SetKeyWithIV( key, sizeof(key), iv );

      // The StreamTransformationFilter removes
      //  padding as required.
      CryptoPP::StringSource( cipher, true, new CryptoPP::StreamTransformationFilter( d, new StringSink(recovered) ) ); // StringSource

      strOutput = recovered;
  }
  catch( CryptoPP::Exception& e )
  {
    return;
  }

}
