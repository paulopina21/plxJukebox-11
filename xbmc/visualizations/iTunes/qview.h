

#ifndef __QVIEW_H__
#define __QVIEW_H__

void* get_view    (int width, int height);
int   get_pixels  (void* dest, long dest_size, bool opengl);
void  release_view(void* view);

#endif // __QVIEW_H__
