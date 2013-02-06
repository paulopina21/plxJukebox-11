#pragma once



#include "guilib/Geometry.h"

class CApplication;
class CAction;

class CInertialScrollingHandler
{
  friend class CApplication;
  public:
    CInertialScrollingHandler();
    
    bool IsScrolling(){return m_bScrolling;}    
    
  private:
    bool CheckForInertialScrolling(const CAction* action);
    bool ProcessInertialScroll(float frameTime);
  
    //-------------------------------------------vars for inertial scrolling animation with gestures
    bool          m_bScrolling;        //flag indicating that we currently do the inertial scrolling emulation
    bool          m_bAborting;         //flag indicating an abort of scrolling
    CPoint        m_iFlickVelocity;
    CPoint        m_iLastGesturePoint;
    CPoint        m_inertialDeacceleration;
    unsigned int  m_inertialStartTime;  
};
