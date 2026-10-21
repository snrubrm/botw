#include <Havok/Common/Base/Thread/Pool/hkCpuThreadPool.h>

hkCpuThreadPoolCinfo::hkCpuThreadPoolCinfo()
    : m_numThreads(1),
      _8(nullptr),
      _10(0),
      _14(0x80000000),
      _18(0x20000),
      _1c(0),
      m_threadName("HavokWorkerThread") {}
