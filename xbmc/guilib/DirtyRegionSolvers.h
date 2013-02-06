#pragma once


#include "IDirtyRegionSolver.h"

class CUnionDirtyRegionSolver : public IDirtyRegionSolver
{
public:
  virtual void Solve(const CDirtyRegionList &input, CDirtyRegionList &output);
};

class CFillViewportAlwaysRegionSolver : public IDirtyRegionSolver
{
public:
  virtual void Solve(const CDirtyRegionList &input, CDirtyRegionList &output);
};

class CFillViewportOnChangeRegionSolver : public IDirtyRegionSolver
{
public:
  virtual void Solve(const CDirtyRegionList &input, CDirtyRegionList &output);
};

class CGreedyDirtyRegionSolver : public IDirtyRegionSolver
{
public:
  CGreedyDirtyRegionSolver();
  virtual void Solve(const CDirtyRegionList &input, CDirtyRegionList &output);
private:
  float m_costNewRegion;
  float m_costPerArea;
};
