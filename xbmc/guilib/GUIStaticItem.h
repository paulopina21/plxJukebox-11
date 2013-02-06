

#pragma once

/*!
 \file GUIStaticItem.h
 \brief
 */

#include "GUIInfoTypes.h"
#include "xbmc/FileItem.h"
#include "GUIAction.h"

class TiXmlElement;

/*!
 \ingroup lists,items
 \brief wrapper class for a static item in a list container
 
 A wrapper class for the items in a container specified via the <content>
 flag.  Handles constructing items from XML and updating item labels, icons
 and properties.
 
 \sa CFileItem, CGUIBaseContainer
 */
class CGUIStaticItem : public CFileItem
{
public:
  /*! \brief constructor
   Construct an item based on an XML description:
     <item>
       <label>$INFO[MusicPlayer.Artist]</label>
       <label2>$INFO[MusicPlayer.Album]</label2>
       <thumb>bar.png</thumb>
       <icon>foo.jpg</icon>
       <onclick>ActivateWindow(Home)</onclick>
     </item>
   
   \param element XML element to construct from
   \param contextWindow window context to use for any info labels
   */
  CGUIStaticItem(const TiXmlElement *element, int contextWindow);
  virtual ~CGUIStaticItem() {};
  virtual CGUIListItem *Clone() const { return new CGUIStaticItem(*this); };
  
  /*! \brief update any infolabels in the items properties
   Runs through all the items properties, updating any that should be
   periodically recomputed
   \param contextWindow window context to use for any info labels
   */
  void UpdateProperties(int contextWindow);

  /*! \brief update visibility of this item
   \param contextWindow window context to use for any info labels
   \return true if visible state has changed, false otherwise
   */
  bool UpdateVisibility(int contextWindow);

  /*! \brief whether this item is visible or not
   */
  bool IsVisible() const;

  const CGUIAction &GetClickActions() const { return m_clickActions; };
private:
  typedef std::vector< std::pair<CGUIInfoLabel, CStdString> > InfoVector;
  InfoVector m_info;
  unsigned int m_visCondition;
  bool m_visState;
  CGUIAction m_clickActions;
};

typedef boost::shared_ptr<CGUIStaticItem> CGUIStaticItemPtr;
