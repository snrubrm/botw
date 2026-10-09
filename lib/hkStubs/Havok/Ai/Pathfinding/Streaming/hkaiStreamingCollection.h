#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>

class hkaiNavMeshInstance;

// Reflection initializer 1776fb8 establishes the referenced-object parent
// and 0x30 extent. Its instances record255f190 names InstanceInfo and +0x18.
class hkaiStreamingCollection : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaiStreamingCollection)
    ~hkaiStreamingCollection() override;

    // Reflection initializer176e6a4 and six records255b338 identify this
    // 0x30 record. No ownership wrapper is inferred for its pointer members.
    struct InstanceInfo {
        hkaiNavMeshInstance* m_instancePtr;
        hkUint8 _8[0x28 - 8];
        hkUint32 m_treeNode;
    };

    int sub_71015145D0(hkUint32 sectionUid);

    hkBool m_isTemporary;
    hkUint8 _d[0x18 - 0xd];
    hkArray<InstanceInfo> m_instances;
    hkUint8 _28[8];
};
static_assert(sizeof(hkaiStreamingCollection::InstanceInfo) == 0x30);
static_assert(sizeof(hkaiStreamingCollection) == 0x30);
