#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>

// Reflection class "hkaiEdgePath" with the nested types FollowingCornerInfo / Edge /
// TraversalState. The native constructor 0x710152cda4 and destructor 0x7100f7cc68
// fix the two arrays at +0x10 (0x90-byte elements) and +0x20 (4-byte elements) and
// the word at +0x30. The element fields are still unmodelled.
class hkaiEdgePath : public hkReferencedObject {
    HK_DECLARE_CLASS_ALLOCATOR(hkaiEdgePath)
public:
    struct Edge {
        hkUint8 _0[0x90];
    };
    struct TraversalState {
        hkInt32 _0;
    };

    hkaiEdgePath();
    ~hkaiEdgePath() override;

    /* 0x10 */ hkArray<Edge> m_edges;
    /* 0x20 */ hkArray<TraversalState> m_traversalStates;
    /* 0x30 */ hkUint32 _30;
    /* 0x34 */ hkUint8 _34[0xc];
};
static_assert(sizeof(hkaiEdgePath) == 0x40);
