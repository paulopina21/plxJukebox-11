#pragma once



#include "utils/StdString.h"

class CFileItemList;

namespace XFILE
{
  namespace VIDEODATABASEDIRECTORY
  {
    class CQueryParams;

    typedef enum _NODE_TYPE
    {
      NODE_TYPE_NONE=0,
      NODE_TYPE_MOVIES_OVERVIEW,
      NODE_TYPE_TVSHOWS_OVERVIEW,
      NODE_TYPE_GENRE,
      NODE_TYPE_ACTOR,
      NODE_TYPE_ROOT,
      NODE_TYPE_OVERVIEW,
      NODE_TYPE_TITLE_MOVIES,
      NODE_TYPE_YEAR,
      NODE_TYPE_DIRECTOR,
      NODE_TYPE_TITLE_TVSHOWS,
      NODE_TYPE_SEASONS,
      NODE_TYPE_EPISODES,
      NODE_TYPE_RECENTLY_ADDED_MOVIES,
      NODE_TYPE_RECENTLY_ADDED_EPISODES,
      NODE_TYPE_STUDIO,
      NODE_TYPE_MUSICVIDEOS_OVERVIEW,
      NODE_TYPE_RECENTLY_ADDED_MUSICVIDEOS,
      NODE_TYPE_TITLE_MUSICVIDEOS,
      NODE_TYPE_MUSICVIDEOS_ALBUM,
      NODE_TYPE_SETS,
      NODE_TYPE_COUNTRY
    } NODE_TYPE;

    typedef struct {
      NODE_TYPE node;
      int       id;
      int       label;
    } Node;
    
    class CDirectoryNode
    {
    public:
      static CDirectoryNode* ParseURL(const CStdString& strPath);
      static void GetDatabaseInfo(const CStdString& strPath, CQueryParams& params);
      virtual ~CDirectoryNode();

      NODE_TYPE GetType() const;

      bool GetChilds(CFileItemList& items);
      virtual NODE_TYPE GetChildType() const;
      virtual CStdString GetLocalizedName() const;

      CDirectoryNode* GetParent() const;

      bool CanCache() const;
    protected:
      CDirectoryNode(NODE_TYPE Type, const CStdString& strName, CDirectoryNode* pParent);
      static CDirectoryNode* CreateNode(NODE_TYPE Type, const CStdString& strName, CDirectoryNode* pParent);

      void CollectQueryParams(CQueryParams& params) const;

      const CStdString& GetName() const;
      int GetID() const;
      void RemoveParent();

      virtual bool GetContent(CFileItemList& items) const;

      CStdString BuildPath() const;

    private:
      void AddQueuingFolder(CFileItemList& items) const;

    private:
      NODE_TYPE m_Type;
      CStdString m_strName;
      CDirectoryNode* m_pParent;
    };
  }
}



