#pragma once


#include <string>
#include <ctime>
#include <stdint.h>

using namespace std;

class CFTPParse
{
public:
  CFTPParse();
  int FTPParse(string str);
  string getName();
  int getFlagtrycwd();
  int getFlagtryretr();
  uint64_t getSize();
  time_t getTime();
private:
  string m_name;            // not necessarily 0-terminated
  int m_flagtrycwd;         // 0 if cwd is definitely pointless, 1 otherwise
  int m_flagtryretr;        // 0 if retr is definitely pointless, 1 otherwise
  uint64_t m_size;              // number of octets
  time_t m_time;            // modification time
  void setTime(string str); // Method used to set m_time from a string
  int getDayOfWeek(int month, int date, int year); // Method to get day of week
};
