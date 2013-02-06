

/* Include file for SDL mouse event handling */

#ifndef _XBMC_mouse_h
#define _XBMC_mouse_h

/* Useful data types */
typedef struct XBMC_Rect {
  int16_t   x, y;
  uint16_t  w, h;
} XBMC_Rect;


typedef struct WMcursor WMcursor;	/* Implementation dependent */
typedef struct XBMC_Cursor {
	XBMC_Rect area;			/* The area of the mouse cursor */
	int16_t hot_x, hot_y;		/* The "tip" of the cursor */
	unsigned char *data;			/* B/W cursor data */
	unsigned char *mask;			/* B/W cursor mask */
	unsigned char *save[2];			/* Place to save cursor area */
	WMcursor *wm_cursor;		/* Window-manager cursor */
} XBMC_Cursor;

#endif /* _XBMC_mouse_h */
