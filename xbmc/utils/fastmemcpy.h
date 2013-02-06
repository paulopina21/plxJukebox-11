
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_WIN32) && !defined(__ppc__) && !defined(__powerpc__)
void * fast_memcpy(void * to, const void * from, size_t len);
//#define fast_memcpy memcpy
#else
#define fast_memcpy memcpy
#endif

#ifdef __cplusplus
}
#endif
