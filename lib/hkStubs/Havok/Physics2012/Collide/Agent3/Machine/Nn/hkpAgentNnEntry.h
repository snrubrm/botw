#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpContactMgr;
class hkpLinkedCollidable;

// CreateAgent 15C11C8 writes the manager, collision-entry indices and collidable
// pair. CopyAndRelinkAgentEntry 15C1F3C uses the same indices and pair.
struct alignas(16) hkpAgentNnEntry {
    hkUint8 _0[4];
    hkUint16 m_agentIndexOnCollidable[2];
    hkpContactMgr* m_contactMgr;
    hkUint8 _10[8];
    hkpLinkedCollidable* m_collidable[2];
    hkUint8 _28[8];
};
static_assert(sizeof(hkpAgentNnEntry) == 0x30);
static_assert(offsetof(hkpAgentNnEntry, m_contactMgr) == 8);
static_assert(offsetof(hkpAgentNnEntry, m_collidable) == 0x18);
