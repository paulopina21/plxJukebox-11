

#ifndef STAT_UTF8_H__
#define STAT_UTF8_H__

#define stat64 __stat64

extern int stat64_utf8(const char* __file, struct stat64* __buf);

#endif //STAT_UTF8_H__

