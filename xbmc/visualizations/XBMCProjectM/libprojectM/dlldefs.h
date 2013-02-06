
/**
 * $Id$
 *
 * DLL definitions for exporting symbols on various platforms
 *
 * $Log$
 */

#ifndef _DLLDEFS_H
#define _DLLDEFS_H

#ifndef DLLEXPORT
#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#else /** !WIN32 */
#define DLLEXPORT
#endif /** WIN32 */
#endif /** !DLLEXPORT */

#endif /** !_DLLDEFS_H */
