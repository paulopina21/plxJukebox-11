#ifndef _RENDER_FLAGS_H_
#define _RENDER_FLAGS_H_



#define RENDER_FLAG_BOT         0x01
#define RENDER_FLAG_TOP         0x02
#define RENDER_FLAG_BOTH (RENDER_FLAG_BOT | RENDER_FLAG_TOP)
#define RENDER_FLAG_FIELDMASK   0x03

#define RENDER_FLAG_FIELD0      0x80
#define RENDER_FLAG_FIELD1      0x100

// #define RENDER_FLAG_LAST        0x40

#define RENDER_FLAG_NOOSD       0x04 /* don't draw any osd */
#define RENDER_FLAG_NOOSDALPHA  0x08 /* don't allow alpha when osd is drawn */

/* these two flags will be used if we need to render same image twice (bob deinterlacing) */
#define RENDER_FLAG_NOLOCK      0x10   /* don't attempt to lock texture before rendering */
#define RENDER_FLAG_NOUNLOCK    0x20   /* don't unlock texture after rendering */

/* this defines what color translation coefficients */
#define CONF_FLAGS_YUVCOEF_MASK(a) ((a) & 0x07)
#define CONF_FLAGS_YUVCOEF_BT709 0x01
#define CONF_FLAGS_YUVCOEF_BT601 0x02
#define CONF_FLAGS_YUVCOEF_240M  0x03
#define CONF_FLAGS_YUVCOEF_EBU   0x04

#define CONF_FLAGS_YUV_FULLRANGE 0x08
#define CONF_FLAGS_FULLSCREEN    0x10

/* defines color primaries */
#define CONF_FLAGS_COLPRI_MASK(a) ((a) & 0xe0)
#define CONF_FLAGS_COLPRI_BT709   0x20
#define CONF_FLAGS_COLPRI_BT470M  0x40
#define CONF_FLAGS_COLPRI_BT470BG 0x60
#define CONF_FLAGS_COLPRI_170M    0x80
#define CONF_FLAGS_COLPRI_240M    0xa0

/* defines chroma subsampling sample location */
#define CONF_FLAGS_CHROMA_MASK(a) ((a) & 0x0300)
#define CONF_FLAGS_CHROMA_LEFT    0x0100
#define CONF_FLAGS_CHROMA_CENTER  0x0200
#define CONF_FLAGS_CHROMA_TOPLEFT 0x0300

/* defines color transfer function */
#define CONF_FLAGS_TRC_MASK(a) ((a) & 0x0c00)
#define CONF_FLAGS_TRC_BT709      0x0400
#define CONF_FLAGS_TRC_GAMMA22    0x0800
#define CONF_FLAGS_TRC_GAMMA28    0x0c00

#define CONF_FLAGS_FORMAT_MASK(a) ((a) & 0x00fff000)
#define CONF_FLAGS_FORMAT_YV12   0x001000
#define CONF_FLAGS_FORMAT_NV12   0x002000
#define CONF_FLAGS_FORMAT_UYVY   0x004000
#define CONF_FLAGS_FORMAT_YUY2   0x008000
#define CONF_FLAGS_FORMAT_DXVA   0x010000
#define CONF_FLAGS_FORMAT_VDPAU  0x020000
#define CONF_FLAGS_FORMAT_VAAPI  0x030000
#define CONF_FLAGS_FORMAT_OMXEGL 0x040000
#define CONF_FLAGS_FORMAT_CVBREF 0x080000
#define CONF_FLAGS_FORMAT_BYPASS 0x100000
#endif
