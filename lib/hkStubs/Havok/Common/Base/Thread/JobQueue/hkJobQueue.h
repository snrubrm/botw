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
