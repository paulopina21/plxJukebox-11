

#ifndef __ITUNES_VIS_COMMON_H__
#define __ITUNES_VIS_COMMON_H__

/***********************************************************************/
/* Common functions that have platform specific implementation         */
/***********************************************************************/

int   _get_visualisations(char*** names, char*** paths);
char* _get_visualisation_path(const char* name);
char* _get_executable_path(const char* plugin_path);
void  _get_album_art_from_file( const char *filename, Handle* handle, OSType* format );

void  _copy_to_pascal_string( unsigned char dest[], const char* src, int dest_length );
void  _copy_to_unicode_string( unsigned short dest[], const char* src, int dest_length );

#endif // __ITUNES_VIS_COMMON_H__
