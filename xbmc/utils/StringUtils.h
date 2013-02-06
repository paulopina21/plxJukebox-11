
//-----------------------------------------------------------------------
//
//  File:      StringUtils.h
//
//  Purpose:   ATL split string utility
//  Author:    Paul J. Weiss
//
//  Modified to support J O'Leary's CStdString class by kraqh3d
//
//------------------------------------------------------------------------

#ifndef __STRINGUTILS_H_
#define __STRINGUTILS_H_

#include "XBDateTime.h"
#include "utils/StdString.h"
#include <vector>
#include <stdint.h>

class StringUtils
{
public:
  static void JoinString(const CStdStringArray &strings, const CStdString& delimiter, CStdString& result);
  static int SplitString(const CStdString& input, const CStdString& delimiter, CStdStringArray &results, unsigned int iMaxStrings = 0);
  static int FindNumber(const CStdString& strInput, const CStdString &strFind);
  static int64_t AlphaNumericCompare(const wchar_t *left, const wchar_t *right);
  static long TimeStringToSeconds(const CStdString &timeString);
  static void RemoveCRLF(CStdString& strLine);

  /*! \brief convert a time in seconds to a string based on the given time format
   \param seconds time in seconds
   \param format the format we want the time in.
   \return the formatted time
   \sa TIME_FORMAT
   */
  static CStdString SecondsToTimeString(long seconds, TIME_FORMAT format = TIME_FORMAT_GUESS);

  static bool IsNaturalNumber(const CStdString& str);
  static bool IsInteger(const CStdString& str);
  static CStdString SizeToString(int64_t size);
  static const CStdString EmptyString;
  static size_t FindWords(const char *str, const char *wordLowerCase);
  static int FindEndBracket(const CStdString &str, char opener, char closer, int startPos = 0);
  static int DateStringToYYYYMMDD(const CStdString &dateString);
  static void WordToDigits(CStdString &word);
  static CStdString CreateUUID();
  static bool ValidateUUID(const CStdString &uuid); // NB only validates syntax
  static double CompareFuzzy(const CStdString &left, const CStdString &right);
  static int FindBestMatch(const CStdString &str, const CStdStringArray &strings, double &matchscore);
private:
  static CStdString m_lastUUID;
};

#endif
