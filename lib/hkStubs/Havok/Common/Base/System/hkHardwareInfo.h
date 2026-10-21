#pragma once

#include <Havok/Common/Base/Pattern/Singleton/hkSingleton.h>
#include <Havok/Common/Base/hkBase.h>

// Hardware information singleton (create 0x7101582084, registration 0x710158219c, instance slot
// 0x71026720c0). create allocates 0x18 bytes and stores the vtable at +0, 0xffff0001 at +8, the
// hardware thread count at +0xc and 0x800000 at +0x10. hkJobQueueHwSetup (0x7101583c30) and the
// job queue constructor (0x7101583c80) read the count back through this singleton.
class hkHardwareInfo : public hkSingleton<hkHardwareInfo> {
public:
    // 0x7101582110: popcount of the process affinity mask. Declared only.
    static int calcNumHardwareThreads();

    u32 _8;
    int m_numHardwareThreads;
    u32 _10;

private:
    // The created object has a vtable at +0; the vtable itself is not modelled.
    virtual void vtableAnchor_();
};

// 0x71026720c0.
template <>
hkHardwareInfo* hkSingleton<hkHardwareInfo>::s_instance;
