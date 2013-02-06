#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#pragma once



//
// C++ Interface: CKeyboard
//
// Description: Adds features like international keyboard layout mapping on top of the
// platform specific low level keyboard classes.
// Here it must be done only once. Within the other mentioned classes it would have to be done several times.
//
// Keyboards alyways deliver printable characters, logical keys for functional behaviour, modifiers ... alongside
// Based on the same hardware with the same scancodes (also alongside) but delivered with different labels to customers
// the software must solve the mapping to the real labels. This is done here.
// The mapping must be specified by an xml configuration that should be able to access everything available,
// but this allows for double/redundant or ambiguous mapping definition, e.g.
// ASCII/unicode could be derived from scancodes, virtual keys, modifiers and/or other ASCII/unicode.

#include "windowing/XBMC_events.h"
#include "guilib/Key.h"

class CKeyboardStat
{
public:
  CKeyboardStat();
  ~CKeyboardStat();

  void Initialize();

  const CKey ProcessKeyDown(XBMC_keysym& keysym);
  void       ProcessKeyUp(void);

  CStdString GetKeyName(int KeyID);

private:
  bool LookupSymAndUnicodePeripherals(XBMC_keysym &keysym, uint8_t *key, char *unicode);

  XBMC_keysym m_lastKeysym;
  unsigned int m_lastKeyTime;
};

extern CKeyboardStat g_Keyboard;

#endif
