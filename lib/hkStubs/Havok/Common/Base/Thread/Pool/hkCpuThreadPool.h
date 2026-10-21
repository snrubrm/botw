#pragma once

#include <Havok/Common/Base/hkBase.h>

// CPU thread pool configuration (constructor 0x710158629c: 0x28 bytes). ksys::phys::World
// 0x71012b37a4 constructs one, overwrites +0 with (hardware threads - 1) and the two words at
// +0x18 / +0x1c, and passes it to the thread pool factory 0x710132084c. Members without a known
// role keep their offset name and the constructor default.
struct hkCpuThreadPoolCinfo {
    hkCpuThreadPoolCinfo();

    int m_numThreads;          // +0x00, default 1
    int _4;                    // +0x04, the constructor leaves it alone
    void* _8;                  // +0x08, default nullptr
    u32 _10;                   // +0x10, default 0
    u32 _14;                   // +0x14, default 0x80000000
    u32 _18;                   // +0x18, default 0x20000
    u32 _1c;                   // +0x1c, default 0
    const char* m_threadName;  // +0x20, default "HavokWorkerThread"
};
static_assert(sizeof(hkCpuThreadPoolCinfo) == 0x28);
