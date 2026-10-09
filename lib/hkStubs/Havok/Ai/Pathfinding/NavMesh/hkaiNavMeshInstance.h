#pragma once

#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMesh.h>

// Reflection initializer 1775658 identifies hkaiNavMeshInstance, its
// hkReferencedObject parent and 0x1c0 extent. Member records 255dbd0
// identify sectionUid at 0x1a0; lookup 15145d0 independently reads it.
class hkaiNavMeshInstance : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaiNavMeshInstance)
    ~hkaiNavMeshInstance() override;

    // 0x71015214B0 calculates the face area and writes its normalized world
    // normal. Game 0x7100F7ED6C supplies the instance from StreamingCollection
    // and copies the output xyz while retaining the scalar area return.
    hkReal sub_71015214B0(hkInt32 faceIndex, hkVector4& normalOut) const;

    // hkReferencedObject's data ends at0xc; derived storage reuses its
    // tail padding. Preserve that unidentified interval explicitly.
    hkUint8 _c[0x20 - 0xc];
    // Finish constructor 152e4ec copies these pointer/count views from the
    // original mesh. Reflection marks the views as zeroed storage; neither
    // capacity nor the intervening bytes are assumed. Game f7e64c/f7e754
    // independently consume the edge and vertex domains.
    hkaiNavMesh::Edge* m_originalEdges;
    hkInt32 m_numOriginalEdges;
    hkUint8 _2c[4];
    hkVector4* m_originalVertices;
    hkInt32 m_numOriginalVertices;
    hkUint8 _3c[4];
    hkUint8 _40[0xd0 - 0x40];
    // Reflected records 255dd38 / 255ddb0 / 255de00 / 255de28 identify
    // these actual hkArray fields and their element types.
    hkArray<hkInt32> m_edgeMap;
    hkUint8 _e0[0x100 - 0xe0];
    hkArray<hkaiNavMesh::Edge> m_instancedEdges;
    hkUint8 _110[0x120 - 0x110];
    hkArray<hkaiNavMesh::Edge> m_ownedEdges;
    hkArray<hkVector4> m_ownedVertices;
    hkUint8 _140[0x1a0 - 0x140];
    hkUint32 m_sectionUid;
    hkUint8 _1a4[0x1c0 - 0x1a4];
};
static_assert(sizeof(hkaiNavMeshInstance) == 0x1c0);
static_assert(offsetof(hkaiNavMeshInstance, m_originalEdges) == 0x20);
static_assert(offsetof(hkaiNavMeshInstance, m_originalVertices) == 0x30);
static_assert(offsetof(hkaiNavMeshInstance, m_edgeMap) == 0xd0);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedEdges) == 0x100);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedEdges) == 0x120);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedVertices) == 0x130);
