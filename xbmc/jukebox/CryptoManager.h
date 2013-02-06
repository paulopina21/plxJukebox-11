/*
 * CryptoManager.h
 *
 *  Created on: Oct 23, 2012
 *      Author: laureon
 */

#ifndef CRYPTOMANAGER_H_
#define CRYPTOMANAGER_H_

#include <cryptopp/aes.h>
using CryptoPP::AES;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <cryptopp/ccm.h>
using CryptoPP::CBC_Mode;
using CryptoPP::ECB_Mode;
using CryptoPP::CFB_Mode;
using CryptoPP::CTR_Mode;

#include <cryptopp/osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include<cryptopp/base64.h>
#include <cryptopp/hex.h>
//using CryptoPP::HexEncoder;

#include "utils/log.h"
#include "utils/StringUtils.h"

class CryptoManager {
public:
  CryptoManager();
  virtual ~CryptoManager();

  void EncryptText(const CStdString& strKey, const CStdString& strInput, CStdString& strOutput);
  void DecryptText(const CStdString& strKey, const CStdString& strInput, CStdString& strOutput);
};

#endif /* CRYPTOMANAGER_H_ */
