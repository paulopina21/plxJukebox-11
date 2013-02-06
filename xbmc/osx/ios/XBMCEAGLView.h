

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface XBMCEAGLView : UIView
{    
@private
  EAGLContext *context;
  // The pixel dimensions of the CAEAGLLayer.
  GLint framebufferWidth;
  GLint framebufferHeight;
  // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
  GLuint defaultFramebuffer, colorRenderbuffer, depthRenderbuffer;
	// the shader program object
	GLuint program;
	//
	GLfloat rotz;
	
	BOOL animating;
  BOOL xbmcAlive;
  BOOL pause;
  NSConditionLock* animationThreadLock;
  NSThread* animationThread;

	// Use of the CADisplayLink class is the preferred method for controlling the animation timing.
	// CADisplayLink will link to the main display and fire every vsync when added to a given run-loop.
	CADisplayLink *displayLink;
  CFTimeInterval displayFPS;
	BOOL displayLinkSupported;
}
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (readonly, nonatomic, getter=isXBMCAlive) BOOL xbmcAlive;
@property (readonly, nonatomic, getter=isPause) BOOL pause;

- (void) initDisplayLink;
- (void) deinitDisplayLink;
- (double) getDisplayLinkFPS;
- (void) pauseAnimation;
- (void) resumeAnimation;
- (void) startAnimation;
- (void) stopAnimation;
- (void) setFramebuffer;
- (bool) presentFramebuffer;

@end
