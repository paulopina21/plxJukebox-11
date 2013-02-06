#pragma once


#include "utils/StdString.h"

#ifdef _WIN32
#undef SetPort // WIN32INCLUDES this is defined as SetPortA in WinSpool.h which is being included _somewhere_
#endif

class CURL
{
public:
  CURL(const CStdString& strURL);
  CURL();
  virtual ~CURL(void);

  void Reset();
  void Parse(const CStdString& strURL);
  void SetFileName(const CStdString& strFileName);
  void SetHostName(const CStdString& strHostName);
  void SetUserName(const CStdString& strUserName);
  void SetPassword(const CStdString& strPassword);
  void SetProtocol(const CStdString& strProtocol);
  void SetOptions(const CStdString& strOptions);
  void SetProtocolOptions(const CStdString& strOptions);
  void SetPort(int port);

  bool HasPort() const;

  int GetPort() const;
  const CStdString& GetHostName() const;
  const CStdString& GetDomain() const;
  const CStdString& GetUserName() const;
  const CStdString& GetPassWord() const;
  const CStdString& GetFileName() const;
  const CStdString& GetProtocol() const;
  const CStdString GetTranslatedProtocol() const;
  const CStdString& GetFileType() const;
  const CStdString& GetShareName() const;
  const CStdString& GetOptions() const;
  const CStdString& GetProtocolOptions() const;
  const CStdString GetFileNameWithoutPath() const; /* return the filename excluding path */

  char GetDirectorySeparator() const;

  CStdString Get() const;
  CStdString GetWithoutUserDetails() const;
  CStdString GetWithoutFilename() const;
  bool IsLocal() const;
  bool IsLocalHost() const;
  static bool IsFileOnly(const CStdString &url); ///< return true if there are no directories in the url.
  static bool IsFullPath(const CStdString &url); ///< return true if the url includes the full path
  static void Decode(CStdString& strURLData);
  static void Encode(CStdString& strURLData);
protected:
  int m_iPort;
  CStdString m_strHostName;
  CStdString m_strShareName;
  CStdString m_strDomain;
  CStdString m_strUserName;
  CStdString m_strPassword;
  CStdString m_strFileName;
  CStdString m_strProtocol;
  CStdString m_strFileType;
  CStdString m_strOptions;
  CStdString m_strProtocolOptions;
};
