#pragma once

#include <Havok/Common/Base/hkBase.h>

// Only the last value is listed: ksys::phys::World passes it to hkThreadPool::processAllJobs
// (0x71012b3f50) and stores it in the job queue cinfo (0x71012b37a4).
enum hkJobType {
    HK_JOB_TYPE_MAX = 15,
};

// ksys::phys::World allocates 0x340 bytes for the queue (0x71012b37a4); the layout is not modelled.
class hkJobQueue {
public:
    enum JobStatus : int;

    // 0x710158487c: World 0x71012b3f50 passes true.
    JobStatus processAllJobs(bool addTimers = true);
};

// Configuration passed to the job queue constructor. The constructor 0x7101583c30 fills 0x24 bytes:
// 1 at +0, true at +4, 0 at +8, hkHardwareInfo::instance()->m_numHardwareThreads at +0xc, then zeros
// up to 0x80000000 at +0x1c. ksys::phys::World 0x71012b37a4 overwrites +0xc with the hardware
// thread count and +0x20 with HK_JOB_TYPE_MAX.
struct hkJobQueueHwSetup {
    hkJobQueueHwSetup();

    u32 m_numThreads;          // +0x00, default 1
    hkBool m_semaphoreMode;    // +0x04, default true
    u32 _8;                    // +0x08, default 0
    int m_numHardwareThreads;  // +0x0c, from hkHardwareInfo
    u64 _10;                   // +0x10, default 0
    u32 _18;                   // +0x18, default 0
    u32 _1c;                   // +0x1c, default 0x80000000
    u32 m_maxJobType;          // +0x20, not initialised by the constructor
};
static_assert(sizeof(hkJobQueueHwSetup) == 0x28);
