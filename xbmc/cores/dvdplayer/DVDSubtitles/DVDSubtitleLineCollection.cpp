

#include "DVDSubtitleLineCollection.h"
#include "DVDClock.h"


CDVDSubtitleLineCollection::CDVDSubtitleLineCollection()
{
  m_pHead = NULL;
  m_pCurrent = NULL;
  m_pTail = NULL;

  m_iSize = 0;
  m_fLastPts = DVD_NOPTS_VALUE;
}

CDVDSubtitleLineCollection::~CDVDSubtitleLineCollection()
{
  Clear();
}

void CDVDSubtitleLineCollection::Add(CDVDOverlay* pOverlay)
{
  ListElement* pElement = new ListElement;
  pElement->pOverlay = pOverlay;
  pElement->pNext = NULL;

  if (!m_pHead)
  {
    m_pHead = m_pTail = pElement;
    m_pCurrent = m_pHead;
  }
  else
  {
    m_pTail->pNext = pElement;
    m_pTail = pElement;
  }

  m_iSize++;
}

void CDVDSubtitleLineCollection::Sort()
{
  if (!m_pHead || !m_pHead->pNext)
    return;
  
  for (ListElement* p1 = m_pHead; p1->pNext->pNext != NULL; p1 = p1->pNext)
  {
    for (ListElement* p2 = p1->pNext; p2->pNext != NULL; p2 = p2->pNext)
    {
      if (p1->pOverlay->iPTSStartTime > p2->pOverlay->iPTSStartTime)
      {
        CDVDOverlay* temp = p1->pOverlay;
        p1->pOverlay = p2->pOverlay;
        p2->pOverlay = temp;
      }
    }
  }
}

CDVDOverlay* CDVDSubtitleLineCollection::Get(double iPts)
{
  CDVDOverlay* pOverlay = NULL;

  if (iPts < m_fLastPts)
    Reset();

  if (m_pCurrent)
  {
    while (m_pCurrent && m_pCurrent->pOverlay->iPTSStopTime < iPts)
    {
      m_pCurrent = m_pCurrent->pNext;
    }

    if (m_pCurrent)
    {
      pOverlay = m_pCurrent->pOverlay;

      // advance to the next overlay
      m_pCurrent = m_pCurrent->pNext;
      m_fLastPts = iPts;
    }
  }
  return pOverlay;
}

void CDVDSubtitleLineCollection::Reset()
{
  m_pCurrent = m_pHead;
}

void CDVDSubtitleLineCollection::Clear()
{
  ListElement* pElement = NULL;

  while (m_pHead)
  {
    pElement = m_pHead;
    m_pHead = pElement->pNext;

    pElement->pOverlay->Release();
    delete pElement;
  }

  m_pTail    = NULL;
  m_pHead    = NULL;
  m_pCurrent = NULL;
  m_iSize    = 0;
  m_fLastPts = DVD_NOPTS_VALUE;
}
