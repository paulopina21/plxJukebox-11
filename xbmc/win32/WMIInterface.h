#pragma once




#include <Wbemidl.h> 
#pragma comment(lib, "wbemuuid.lib") 
#pragma comment(lib, "comsuppw.lib")


class CWIN32Wmi
{
public:
  CWIN32Wmi(void);
  virtual ~CWIN32Wmi(void);

  bool Connect();
  void Release();
  void testquery();

  std::vector<CStdString> GetWMIStrVector(CStdString& strQuery, CStdStringW& strProperty);
  CStdString GetWMIString(CStdString& strQuery, CStdStringW& strProperty);



private:

  HRESULT hres;
	IWbemLocator *pLoc;
	IWbemServices *pSvc;
	IEnumWbemClassObject	*pEnumerator;
  IWbemClassObject *pclsObj;

  bool bconnected;


};
