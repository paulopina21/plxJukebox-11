

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <AudioToolbox/AudioToolbox.h>

#import "XBMC_events.h"
#include "XBMC_keysym.h"

@interface XBMCController : UIViewController
{
  int m_screensaverTimeout;
	
  /* Touch handling */
  CGSize screensize;
  CGPoint lastGesturePoint;
  CGFloat lastPinchScale;
  CGFloat currentPinchScale;  
  CGFloat screenScale;
  bool touchBeginSignaled;
	
  UIInterfaceOrientation orientation;

  XBMC_Event lastEvent;
}
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property CGPoint lastGesturePoint;
@property CGFloat lastPinchScale;
@property CGFloat currentPinchScale;
@property CGFloat screenScale;
@property bool touchBeginSignaled;
@property CGSize screensize;
@property XBMC_Event lastEvent;

// message from which our instance is obtained
- (void) pauseAnimation;
- (void) resumeAnimation;
- (void) startAnimation;
- (void) stopAnimation;
- (void) sendKey: (XBMCKey) key;
- (void) observeDefaultCenterStuff: (NSNotification *) notification;
- (void) initDisplayLink;
- (void) deinitDisplayLink;
- (double) getDisplayLinkFPS;
- (void) setFramebuffer;
- (bool) presentFramebuffer;
- (CGSize) getScreenSize;
- (UIInterfaceOrientation) getOrientation;
- (void)createGestureRecognizers;
- (void) disableSystemSleep;
- (void) enableSystemSleep;
- (void) disableScreenSaver;
- (void) enableScreenSaver;
@end

extern XBMCController *g_xbmcController;
