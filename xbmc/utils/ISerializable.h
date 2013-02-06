#pragma once


class CVariant;

class ISerializable
{
public:
  virtual void Serialize(CVariant& value) = 0;
  virtual ~ISerializable() {}
};
