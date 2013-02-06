
#ifndef _OSX_AUTOPOOL_H_
#define _OSX_AUTOPOOL_H_

class CCocoaAutoPool
{
  public:
    CCocoaAutoPool();
    ~CCocoaAutoPool();
  private:
    void *m_opaque_pool;
};

#ifdef __cplusplus
extern "C"
{
#endif
  // Pools.
  //
  void* Cocoa_Create_AutoReleasePool(void);
  void Cocoa_Destroy_AutoReleasePool(void* pool);
  
#ifdef __cplusplus
}
#endif

#endif
