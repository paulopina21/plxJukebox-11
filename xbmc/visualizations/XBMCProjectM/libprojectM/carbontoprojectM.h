r
/**
 * $Id: carbontoprojectM.hpp,v 1.2 2004/11/12 15:12:58 cvs Exp $
 *
 * Translates CARBON -> projectM variables
 *
 * $Log$
 */

#ifndef _CARBONTOPROJECTM_H
#define _CARBONTOPROJECTM_H

#include "event.h"

#ifdef WIN32
#else
#endif

projectMEvent carbon2pmEvent( EventRecord *event ) { \
\
    switch ( event->what ) { \
        case updateEvt: \
            return PROJECTM_VIDEORESIZE; \
        case keyUp: \
            return PROJECTM_KEYUP; \
        case keyDown: \
            return PROJECTM_KEYDOWN; \
        default:
            return PROJECTM_KEYUP; \
      } \
  } \

projectMKeycode carbon2pmKeycode( EventRecord *event ) { \
    projectMKeycode char_code = (projectMKeycode)(event->message & charCodeMask); \
    switch ( char_code ) { \
        case kFunctionKeyCharCode: { \
            switch ( ( event->message << 16 ) >> 24 ) { \
                case 111: { \
                    return PROJECTM_K_F12; \
                  } \
                case 103: { \
                    return PROJECTM_K_F11; \
                  } \
                case 109: { \
                    return PROJECTM_K_F10; \
                  } \
                case 101: { \
                    return PROJECTM_K_F9; \
                  } \
                case 100: { \
                    return PROJECTM_K_F8; \
                  } \
                case 98: { \
                    return PROJECTM_K_F7; \
                  } \
                case 97: { \
                    return PROJECTM_K_F6; \
                  } \
                case 96: { \
                    return PROJECTM_K_F5; \
                  } \
                case 118: { \
                    return PROJECTM_K_F4; \
                  } \
                case 99: { \
                    return PROJECTM_K_F3; \
                  } \
                case 120: { \
                    return PROJECTM_K_F2; \
                  } \
                case 122: { \
                    return PROJECTM_K_F1; \
                  } \
              } \
          } \
        default: { \
            return char_code; \
          } \
      } \
  } \

projectMModifier carbon2pmModifier( EventRecord *event ) { \
    return (projectMModifier)PROJECTM_K_LSHIFT; \
  } \

#endif /** _CARBONTOPROJECTM_H */
