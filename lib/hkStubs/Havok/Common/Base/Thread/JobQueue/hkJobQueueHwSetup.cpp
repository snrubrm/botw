#include <Havok/Common/Base/System/hkHardwareInfo.h>
#include <Havok/Common/Base/Thread/JobQueue/hkJobQueue.h>

hkJobQueueHwSetup::hkJobQueueHwSetup()
    : m_numThreads(1),
      m_semaphoreMode(true),
      _8(0),
      m_numHardwareThreads(hkHardwareInfo::instance()->m_numHardwareThreads),
      _10(0),
      _18(0),
      _1c(0x80000000) {}
