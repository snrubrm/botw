#pragma once

#include <Havok/Common/Base/hkBase.h>

// Reflection initializer 1775658 identifies hkaiNavMeshInstance, its
// hkReferencedObject parent and 0x1c0 extent. Member records 255dbd0
// identify sectionUid at 0x1a0; lookup 15145d0 independently reads it.
class hkaiNavMeshInstance : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaiNavMeshInstance)
    ~hkaiNavMeshInstance() override;

    // hkReferencedObject's data ends at0xc; derived storage reuses its
    // tail padding. Preserve that unidentified interval explicitly.
    hkUint8 _c[0x1a0 - 0xc];
    hkUint32 m_sectionUid;
    hkUint8 _1a4[0x1c0 - 0x1a4];
};
static_assert(sizeof(hkaiNavMeshInstance) == 0x1c0);
