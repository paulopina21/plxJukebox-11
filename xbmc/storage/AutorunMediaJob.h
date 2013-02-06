#pragma once

#include "system.h"
#include "utils/StdString.h"
#include "utils/Job.h"

class CAutorunMediaJob : public CJob
{
public:
  CAutorunMediaJob(const CStdString &label, const CStdString &path);

  virtual bool DoWork();
private:
  const char *GetWindowString(int selection);

  CStdString m_path, m_label;
};
