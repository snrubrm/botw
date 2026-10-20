#pragma once

#include <Havok/Common/Base/hkBase.h>

// Reflection initializer 0x7101770770 and member records 0x710255c758 /
// 0x710255c780 identify both names, types and offsets. No constructor is
// emitted in the original; the line-of-sight inputs value-initialize it.
struct hkaiAgentTraversalInfo {
    hkReal m_diameter;
    hkUint32 m_filterInfo;
};
static_assert(sizeof(hkaiAgentTraversalInfo) == 8);
