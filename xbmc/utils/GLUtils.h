#pragma once



// GL Error checking macro
// this function is useful for tracking down GL errors, which otherwise
// just result in undefined behavior and can be difficult to track down.
//
// Just call it 'VerifyGLState()' after a sequence of GL calls
//
// if GL_DEBUGGING and HAS_GL are defined, the function checks
// for GL errors and prints the current state of the various matrices;
// if not it's just an empty inline stub, and thus won't affect performance
// and will be optimized out.

void _VerifyGLState(const char* szfile, const char* szfunction, int lineno);
#if defined(GL_DEBUGGING) && (defined(HAS_GL) || defined(HAS_GLES))
#define VerifyGLState() _VerifyGLState(__FILE__, __FUNCTION__, __LINE__)
#else
#define VerifyGLState()
#endif

void LogGraphicsInfo();

