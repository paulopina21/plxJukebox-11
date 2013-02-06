

/* Include file for SDL keyboard event handling */

#ifndef _XBMC_keyboard_h
#define _XBMC_keyboard_h

#include <stdint.h>

#include "XBMC_keysym.h"

/* Keysym structure
   - The scancode is hardware dependent, and should not be used by general
     applications.  If no hardware scancode is available, it will be 0.

   - The 'unicode' translated character is only available when character
     translation is enabled by the XBMC_EnableUNICODE() API.  If non-zero,
     this is a UNICODE character corresponding to the keypress.  If the
     high 9 bits of the character are 0, then this maps to the equivalent
     ASCII character:
	char ch;
	if ( (keysym.unicode & 0xFF80) == 0 ) {
		ch = keysym.unicode & 0x7F;
	} else {
		An international character..
	}
 */
typedef struct XBMC_keysym {
	unsigned char scancode;			/* hardware specific scancode */
	XBMCKey sym;			/* SDL virtual keysym */
	XBMCMod mod;			/* current key modifiers */
	uint16_t unicode;			/* translated character */
} XBMC_keysym;

/* This is the mask which refers to all hotkey bindings */
#define XBMC_ALL_HOTKEYS		0xFFFFFFFF

#endif /* _XBMC_keyboard_h */
