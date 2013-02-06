

#import <BackRow/BackRow.h>

@class XBMCTopShelfController;

//--------------------------------------------------------------
@interface XBMCAppliance : BRBaseAppliance {
  NSArray *_applianceCategories;
  XBMCTopShelfController *_topShelfController;
}
@property(nonatomic, readonly, retain) id topShelfController;
@end
