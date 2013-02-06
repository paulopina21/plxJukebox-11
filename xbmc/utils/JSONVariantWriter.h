#pragma once


#include "system.h"
#include "Variant.h"
#include <yajl/yajl_gen.h>
#ifdef HAVE_YAJL_YAJL_VERSION_H
#include <yajl/yajl_version.h>
#endif

class CJSONVariantWriter
{
public:
  static std::string Write(const CVariant &value, bool compact);
private:
  static bool InternalWrite(yajl_gen g, const CVariant &value);
};
