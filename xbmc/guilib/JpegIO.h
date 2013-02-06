

#ifndef GUILIB_JPEGIO_H
#define GUILIB_JPEGIO_H

#ifdef TARGET_WINDOWS
#define XMD_H
#pragma comment(lib, "jpeg-static.lib")
#endif

#include <jpeglib.h>
#include "utils/StdString.h"

class CJpegIO
{

public:
  CJpegIO();
  ~CJpegIO();
  bool           Open(const CStdString& m_texturePath,  unsigned int m_minx=0, unsigned int m_miny=0);
  bool           Decode(const unsigned char *pixels, unsigned int pitch, unsigned int format);
  void           Close();

  unsigned int   FileSize()    { return m_imgsize; }
  unsigned int   Width()       { return m_width; }
  unsigned int   Height()      { return m_height; }
  unsigned int   Orientation() { return m_orientation; }

protected:
  static  void   jpeg_error_exit(j_common_ptr cinfo);

  bool           GetExif();
  unsigned int   findExifMarker( unsigned char *jpegData, 
                                 unsigned int dataSize, 
                                 unsigned char *&exifPtr);
  unsigned char  *m_inputBuff;
  unsigned int   m_inputBuffSize;
  unsigned int   m_minx;
  unsigned int   m_miny;
  struct         jpeg_decompress_struct m_cinfo;
  CStdString     m_texturePath;

  unsigned int   m_imgsize;
  unsigned int   m_width;
  unsigned int   m_height;
  unsigned int   m_orientation;
};

#endif
