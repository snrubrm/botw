#pragma once

#include <Havok/Common/Base/hkBase.h>

// Reflection 152ce18 identifies hkaiNavMesh and its hkReferencedObject parent,
// with extent 0xb0. The unrelated mesh storage remains unidentified here.
class hkaiNavMesh : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaiNavMesh)
    ~hkaiNavMesh() override;

    // Native reflection 152ce18 / member records 2538c78 establish
    // the 0x10-byte face. Area calculation 15214b0 independently uses
    // its signed start edge and signed edge count.
    struct Face {
        hkInt32 m_startEdgeIndex;
        hkInt32 m_startUserEdgeIndex;
        hkInt16 m_numEdges;
        hkInt16 m_numUserEdges;
        hkInt16 m_clusterIndex;
        hkUint16 m_padding;
    };

    enum EdgeFlagBits {
        EDGE_SILHOUETTE = 1,
        EDGE_RETRIANGULATED = 2,
        EDGE_ORIGINAL = 4,
        OPPOSITE_EDGE_UNLOADED_UNUSED = 8,
        EDGE_USER = 16,
        EDGE_BLOCKED = 32,
        EDGE_EXTERNAL_OPPOSITE = 64,
    };

    // The same initializer builds all seven hkaiNavMeshEdge member records
    // at 2671378 and fixes its extent at 0x14. Independent game f7e64c
    // indexes 0x14 records, f7e754 uses signed a/b, and 66a30c tests
    // oppositeEdge against the invalid packed-key value 0xffffffff.
    struct Edge {
        hkInt32 m_a;
        hkInt32 m_b;
        hkUint32 m_oppositeEdge;
        hkUint32 m_oppositeFace;
        hkFlags<EdgeFlagBits, hkUint8> m_flags;
        hkUint8 m_paddingByte;
        hkHalf m_userEdgeCost;
    };

    hkUint8 _c[0xb0 - 0xc];
};
static_assert(sizeof(hkaiNavMesh) == 0xb0);
static_assert(sizeof(hkaiNavMesh::Edge) == 0x14);
static_assert(offsetof(hkaiNavMesh::Edge, m_oppositeEdge) == 0x8);
static_assert(offsetof(hkaiNavMesh::Edge, m_userEdgeCost) == 0x12);

static_assert(sizeof(hkaiNavMesh::Face) == 0x10);
static_assert(offsetof(hkaiNavMesh::Face, m_numEdges) == 0x8);
