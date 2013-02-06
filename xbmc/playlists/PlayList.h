#pragma once


#include "FileItem.h"
#include <boost/shared_ptr.hpp>

namespace PLAYLIST
{
class CPlayList
{
public:
  CPlayList(void);
  virtual ~CPlayList(void);
  virtual bool Load(const CStdString& strFileName);
  virtual bool LoadData(std::istream &stream);
  virtual bool LoadData(const CStdString& strData);
  virtual void Save(const CStdString& strFileName) const {};

  void Add(CPlayList& playlist);
  void Add(const CFileItemPtr &pItem);
  void Add(CFileItemList& items);

  // for Party Mode
  void Insert(CPlayList& playlist, int iPosition = -1);
  void Insert(CFileItemList& items, int iPosition = -1);
  void Insert(const CFileItemPtr& item, int iPosition = -1);

  int FindOrder(int iOrder) const;
  const CStdString& GetName() const;
  void Remove(const CStdString& strFileName);
  void Remove(int position);
  bool Swap(int position1, int position2);
  bool Expand(int position); // expands any playlist at position into this playlist
  void Clear();
  int size() const;
  int RemoveDVDItems();

  const CFileItemPtr operator[] (int iItem) const;
  CFileItemPtr operator[] (int iItem);

  void Shuffle(int iPosition = 0);
  void UnShuffle();
  bool IsShuffled() const { return m_bShuffled; }

  void SetPlayed(bool bPlayed) { m_bWasPlayed = true; };
  bool WasPlayed() const { return m_bWasPlayed; };

  void SetUnPlayable(int iItem);
  int GetPlayable() const { return m_iPlayableItems; };

  void UpdateItem(const CFileItem *item);

  const CStdString& ResolveURL(const CFileItemPtr &item) const;

protected:
  CStdString m_strPlayListName;
  CStdString m_strBasePath;
  int m_iPlayableItems;
  bool m_bShuffled;
  bool m_bWasPlayed;

//  CFileItemList m_vecItems;
  std::vector <CFileItemPtr> m_vecItems;
  typedef std::vector <CFileItemPtr>::iterator ivecItems;

private:
  void Add(const CFileItemPtr& item, int iPosition, int iOrderOffset);
  void DecrementOrder(int iOrder);
  void IncrementOrder(int iPosition, int iOrder);
};

typedef boost::shared_ptr<CPlayList> CPlayListPtr;
}
