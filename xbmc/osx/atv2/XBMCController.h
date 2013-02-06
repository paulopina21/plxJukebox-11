

#import <Foundation/Foundation.h>
#import <BackRow/BackRow.h>
#import "XBMCEAGLView.h"

@interface XBMCController : BRController
{
  int padding[16];  // credit is due here to SapphireCompatibilityClasses!!
        
  int m_screensaverTimeout;
  BRController *m_controller;
}
// message from which our instance is obtained
//+ (XBMCController*) sharedInstance;

- (void) applicationDidExit;
- (void) initDisplayLink;
- (void) deinitDisplayLink;
- (double) getDisplayLinkFPS;
- (void) setFramebuffer;
- (bool) presentFramebuffer;
- (CGSize) getScreenSize;
- (void) disableSystemSleep;
- (void) enableSystemSleep;
- (void) disableScreenSaver;
- (void) enableScreenSaver;

@end

extern XBMCController *g_xbmcController;
