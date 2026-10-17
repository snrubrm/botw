#pragma once

#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMesh.h>
#include <Havok/Ai/Pathfinding/NavMesh/hkaiReferenceFrame.h>
#include <Havok/Common/Base/Container/Array/hkSimpleArray.h>

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
    hkUint8 _c[0x10 - 0xc];
    // Reflected kind 26 at 255dbd0 and finish constructor 152e4ec
    // establish this borrowed face pointer/count view.
    hkSimpleArray<hkaiNavMesh::Face> m_originalFaces;
    // Finish constructor 152e4ec copies these pointer/count views from the
    // original mesh. Reflected kind 26 is TYPE_SIMPLEARRAY with ignored
    // serialization; there is no capacity or ownership field. Game
    // f7e64c/f7e754 independently consume the edge and vertex domains.
    hkSimpleArray<hkaiNavMesh::Edge> m_originalEdges;
    hkSimpleArray<hkVector4> m_originalVertices;
    // Reflection 255dc48 / 255dc70 identifies a void pointer and signed
    // word stride. Finish constructor 152e4ec borrows both from the mesh;
    // game f7eee4 selects this storage and indexes stride-sized records.
    void* m_originalFaceData;
    hkInt32 m_faceDataStriding;
    hkUint8 _4c[0x50 - 0x4c];
    // Reflection 255dc98 / 255dcc0 fixes the borrowed edge-data pointer
    // and signed word stride. Edge COW f83d20 copies stride int32 values.
    void* m_originalEdgeData;
    hkInt32 m_edgeDataStriding;
    hkUint8 _5c[0x70 - 0x5c];
    hkaiReferenceFrame m_referenceFrame;
    // Reflected records 255dd38 / 255ddb0 / 255de00 / 255de28 identify
    // these actual hkArray fields and their element types.
    hkArray<hkInt32> m_edgeMap;
    // Reflected records 255dd60 / 255dd88 / 255ddd8, independently
    // selected by signed face index in area calculation 15214b0.
    hkArray<hkInt32> m_faceMap;
    hkArray<hkaiNavMesh::Face> m_instancedFaces;
    hkArray<hkaiNavMesh::Edge> m_instancedEdges;
    hkArray<hkaiNavMesh::Face> m_ownedFaces;
    hkArray<hkaiNavMesh::Edge> m_ownedEdges;
    hkArray<hkVector4> m_ownedVertices;
    hkUint8 _140[0x160 - 0x140];
    // Reflection 255dea0 / 255def0 fixes the int32 element domains.
    // Game f7eee4 independently selects each array for mapped/owned faces.
    hkArray<hkInt32> m_instancedFaceData;
    // Reflection 255dec8 / 255df18 identifies the matching edge arrays.
    hkArray<hkInt32> m_instancedEdgeData;
    hkArray<hkInt32> m_ownedFaceData;
    hkArray<hkInt32> m_ownedEdgeData;
    hkUint32 m_sectionUid;
    // Reflection 255df68 names the signed runtimeId. Game f82278/f83848
    // use this index for an edge whose external-opposite flag is clear.
    hkInt32 m_runtimeId;
    hkUint8 _1a8[0x1c0 - 0x1a8];
};
static_assert(sizeof(hkaiNavMeshInstance) == 0x1c0);
static_assert(offsetof(hkaiNavMeshInstance, m_originalEdges) == 0x20);
static_assert(offsetof(hkaiNavMeshInstance, m_originalVertices) == 0x30);
static_assert(offsetof(hkaiNavMeshInstance, m_edgeMap) == 0xd0);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedEdges) == 0x100);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedEdges) == 0x120);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedVertices) == 0x130);

static_assert(offsetof(hkaiNavMeshInstance, m_originalFaces) == 0x10);
static_assert(offsetof(hkaiNavMeshInstance, m_faceMap) == 0xe0);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedFaces) == 0xf0);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedFaces) == 0x110);
static_assert(offsetof(hkaiNavMeshInstance, m_originalFaceData) == 0x40);
static_assert(offsetof(hkaiNavMeshInstance, m_faceDataStriding) == 0x48);
static_assert(offsetof(hkaiNavMeshInstance, m_referenceFrame) == 0x70);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedFaceData) == 0x160);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedFaceData) == 0x180);
static_assert(offsetof(hkaiNavMeshInstance, m_originalEdgeData) == 0x50);
static_assert(offsetof(hkaiNavMeshInstance, m_edgeDataStriding) == 0x58);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedEdgeData) == 0x170);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedEdgeData) == 0x190);
static_assert(offsetof(hkaiNavMeshInstance, m_runtimeId) == 0x1a4);

// Explicit-array edge copy-on-write helper. Caller 15235e0 passes these
// instance fields individually; originalEdges is edge storage, not a receiver.
// The native scope/name is unknown. The last argument is a word-sized zero/
// nonzero flag; a missing mapped edge returns null when copying is disabled.
hkaiNavMesh::Edge* sub_7100F83D20(
    const hkaiNavMesh::Edge* originalEdges, hkInt32 originalCount,
    hkArray<hkaiNavMesh::Edge>* instancedEdges, hkArray<hkaiNavMesh::Edge>* ownedEdges,
    const void* originalEdgeData, hkArray<hkInt32>* instancedEdgeData,
    hkArray<hkInt32>* edgeMap, hkInt32 edgeIndex, hkInt32 edgeDataStriding,
    hkInt32 copyIfNeeded);
