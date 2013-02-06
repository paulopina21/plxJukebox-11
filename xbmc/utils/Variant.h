#pragma once

#include <map>
#include <vector>
#include <string>
#include <stdint.h>

class CVariant
{
public:
  enum VariantType
  {
    VariantTypeInteger,
    VariantTypeUnsignedInteger,
    VariantTypeBoolean,
    VariantTypeString,
    VariantTypeDouble,
    VariantTypeArray,
    VariantTypeObject,
    VariantTypeNull,
    VariantTypeConstNull
  };

  CVariant(VariantType type = VariantTypeNull);
  CVariant(int integer);
  CVariant(int64_t integer);
  CVariant(unsigned int unsignedinteger);
  CVariant(uint64_t unsignedinteger);
  CVariant(double value);
  CVariant(float value);
  CVariant(bool boolean);
  CVariant(const char *str);
  CVariant(const char *str, unsigned int length);
  CVariant(const std::string &str);
  CVariant(const CVariant &variant);

  bool isInteger() const;
  bool isUnsignedInteger() const;
  bool isBoolean() const;
  bool isString() const;
  bool isDouble() const;
  bool isArray() const;
  bool isObject() const;
  bool isNull() const;

  VariantType type() const;

  int64_t asInteger(int64_t fallback = 0) const;
  uint64_t asUnsignedInteger(uint64_t fallback = 0u) const;
  bool asBoolean(bool fallback = false) const;
  std::string asString(const std::string &fallback = "") const;
  double asDouble(double fallback = 0.0) const;
  float asFloat(float fallback = 0.0f) const;

  CVariant &operator[](const std::string &key);
  const CVariant &operator[](const std::string &key) const;
  CVariant &operator[](unsigned int position);
  const CVariant &operator[](unsigned int position) const;

  CVariant &operator=(const CVariant &rhs);
  bool operator==(const CVariant &rhs) const;

  void push_back(const CVariant &variant);
  void append(const CVariant &variant);

  const char *c_str() const;

  void swap(CVariant &rhs);

private:
  typedef std::vector<CVariant> VariantArray;
  typedef std::map<std::string, CVariant> VariantMap;

public:
  typedef VariantArray::iterator        iterator_array;
  typedef VariantArray::const_iterator  const_iterator_array;

  typedef VariantMap::iterator          iterator_map;
  typedef VariantMap::const_iterator    const_iterator_map;

  iterator_array begin_array();
  const_iterator_array begin_array() const;
  iterator_array end_array();
  const_iterator_array end_array() const;

  iterator_map begin_map();
  const_iterator_map begin_map() const;
  iterator_map end_map();
  const_iterator_map end_map() const;

  unsigned int size() const;
  bool empty() const;
  void clear();
  void erase(const std::string &key);
  void erase(unsigned int position);

  bool isMember(const std::string &key) const;

private:
  union VariantUnion
  {
    int64_t integer;
    uint64_t unsignedinteger;
    bool boolean;
    double dvalue;
  };

  VariantType m_type;
  VariantUnion m_data;
  std::string m_string;
  VariantArray m_array;
  VariantMap m_map;

  static CVariant ConstNullVariant;
};
