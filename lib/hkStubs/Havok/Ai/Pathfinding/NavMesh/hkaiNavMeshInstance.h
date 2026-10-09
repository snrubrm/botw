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
    hkUint8 _4c[0x70 - 0x4c];
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
    hkUint8 _170[0x180 - 0x170];
    hkArray<hkInt32> m_ownedFaceData;
    hkUint8 _190[0x1a0 - 0x190];
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

static_assert(offsetof(hkaiNavMeshInstance, m_originalFaces) == 0x10);
static_assert(offsetof(hkaiNavMeshInstance, m_faceMap) == 0xe0);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedFaces) == 0xf0);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedFaces) == 0x110);
static_assert(offsetof(hkaiNavMeshInstance, m_originalFaceData) == 0x40);
static_assert(offsetof(hkaiNavMeshInstance, m_faceDataStriding) == 0x48);
static_assert(offsetof(hkaiNavMeshInstance, m_referenceFrame) == 0x70);
static_assert(offsetof(hkaiNavMeshInstance, m_instancedFaceData) == 0x160);
static_assert(offsetof(hkaiNavMeshInstance, m_ownedFaceData) == 0x180);
