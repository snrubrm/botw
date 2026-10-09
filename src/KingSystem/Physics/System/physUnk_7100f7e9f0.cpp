#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physNavMeshEdgeResult.h"
#include <thread/seadAtomic.h>
#include <thread/seadEvent.h>
#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMeshInstance.h>
#include <Havok/Ai/Pathfinding/Streaming/hkaiStreamingCollection.h>

namespace ksys::phys {

// Placeholder: a sead::Event with a reference count (released by ~Unk_7100f7e9f0).
class Unk_7100f7e9f0Event {
public:
    sead::Event mEvent;
    sead::Atomic<s32> mRefCount;
};
static_assert(offsetof(Unk_7100f7e9f0Event, mRefCount) == 0x30);

// NON_MATCHING: edge selection branches and address calculations differ.
Unk_7100f7e64c::Unk_7100f7e64c(hkaiStreamingCollection* collection, s32 key,
                               Unk_7100f7e9f0Event* event) {
    if (key == -1) {
        mInstance = nullptr;
        mEdge = nullptr;
        mEvent = nullptr;
    } else {
        mInstance = collection->m_instances[u32(key) >> 22].m_instancePtr;
        const s32 edge_index = key & 0x3fffff;
        if (edge_index >= mInstance->m_originalEdges.m_size) {
            mEdge = &mInstance->m_ownedEdges[edge_index - mInstance->m_originalEdges.m_size];
        } else if (mInstance->m_edgeMap.isEmpty()) {
            mEdge = &mInstance->m_instancedEdges[edge_index];
        } else {
            const s32 mapped_index = mInstance->m_edgeMap[edge_index];
            if (mapped_index == -1)
                mEdge = &mInstance->m_originalEdges.m_data[edge_index];
            else
                mEdge = &mInstance->m_instancedEdges[mapped_index];
        }
        mEvent = event;
    }
    event = mEvent;
    if (event) {
        while (true) {
            const s32 count = event->mRefCount;
            if (u32(count) > 0xff)
                break;
            if (event->mRefCount.compareExchange(count, count + 1)) {
                if (count == 0)
                    event->mEvent.resetSignal();
                break;
            }
        }
    }
}

Unk_7100f7e64c::~Unk_7100f7e64c() {
    auto* event = mEvent;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
}

// NON_MATCHING: vertex-selection comparisons, midpoint/direction load order and vector registers differ.
void Unk_7100f7e64c::sub_7100F7E754(sead::Vector3f* start_out, sead::Vector3f* end_out,
                                     sead::Vector3f* midpoint_out, sead::Vector3f* direction_out,
                                     f32* length_out, sead::Vector3f* side_out,
                                     sead::Vector3f* up_out) const {
    if (!start_out || !end_out || !mInstance)
        return;
    const s32 original_count = mInstance->m_originalVertices.m_size;
    const hkVector4& vertex_a = mEdge->m_a < original_count ?
                                   mInstance->m_originalVertices.m_data[mEdge->m_a] :
                                   mInstance->m_ownedVertices[mEdge->m_a - original_count];
    const hkVector4& vertex_b = mEdge->m_b < original_count ?
                                   mInstance->m_originalVertices.m_data[mEdge->m_b] :
                                   mInstance->m_ownedVertices[mEdge->m_b - original_count];
    hkVector4 world_a;
    hkVector4 world_b;
    world_a._setTransformedPos(mInstance->m_referenceFrame.m_transform, vertex_a);
    world_b._setTransformedPos(mInstance->m_referenceFrame.m_transform, vertex_b);
    world_a.store<3>(start_out->e.data());
    world_b.store<3>(end_out->e.data());
    if (midpoint_out)
        *midpoint_out = *start_out + (*end_out - *start_out) * 0.5f;

    sead::Vector3f direction;
    sead::Vector3f up;
    if (side_out) {
        if (!direction_out)
            direction_out = &direction;
        if (!up_out)
            up_out = &up;
    }
    if (!direction_out && length_out)
        direction_out = &direction;
    if (direction_out) {
        *direction_out = *end_out - *start_out;
        const f32 length = direction_out->normalize();
        if (length_out)
            *length_out = length;
    }
    if (up_out)
        *up_out = sead::Vector3f::ey;
    if (side_out) {
        side_out->setCross(*up_out, *direction_out);
        side_out->normalize();
    }
}

// Separate translation unit: the original calls the constructor out of line from
// NavMeshCharacter::sub_7100F76078.
Unk_7100f7e9f0::Unk_7100f7e9f0() : _0(nullptr), _8(-1), _10(nullptr) {}

Unk_7100f7e9f0::Unk_7100f7e9f0(hkaiStreamingCollection* collection, s32 key,
                                   Unk_7100f7e9f0Event* event)
    : _0(collection), _8(key), _10(event) {
    if (event) {
        while (true) {
            const s32 count = event->mRefCount;
            if (u32(count) > 0xff)
                break;
            if (event->mRefCount.compareExchange(count, count + 1)) {
                if (count == 0)
                    event->mEvent.resetSignal();
                break;
            }
        }
    }
}

Unk_7100f7e9f0& Unk_7100f7e9f0::operator=(const Unk_7100f7e9f0& other) {
    auto* event = _10;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
    _0 = other._0;
    _8 = other._8;
    _10 = other._10;
    event = _10;
    if (event) {
        while (true) {
            const s32 count = event->mRefCount;
            if (u32(count) > 0xff)
                break;
            if (event->mRefCount.compareExchange(count, count + 1)) {
                if (count == 0)
                    event->mEvent.resetSignal();
                break;
            }
        }
    }
    return *this;
}

Unk_7100f7e9f0::~Unk_7100f7e9f0() {
    auto* event = _10;
    if (event && event->mRefCount.decrement() == 1)
        event->mEvent.setSignal();
}

bool Unk_7100f7e9f0::sub_7100F7EB40() const {
    return _0 && _8 != -1;
}

// NON_MATCHING: face/edge selection, loop induction and vector store scheduling differ.
bool Unk_7100f7e9f0::sub_7100F7EB60(sead::Vector3f* position_out) const {
    if (!_0 || _8 == -1)
        return false;
    auto* instance = _0->m_instances[u32(_8) >> 22].m_instancePtr;
    if (!instance)
        return false;
    const s32 face_index = _8 & 0x3fffff;
    const hkaiNavMesh::Face* face;
    if (face_index >= instance->m_originalFaces.m_size) {
        face = &instance->m_ownedFaces[face_index - instance->m_originalFaces.m_size];
    } else if (instance->m_faceMap.isEmpty()) {
        face = &instance->m_instancedFaces[face_index];
    } else {
        const s32 mapped_index = instance->m_faceMap[face_index];
        if (mapped_index == -1)
            face = &instance->m_originalFaces.m_data[face_index];
        else
            face = &instance->m_instancedFaces[mapped_index];
    }
    hkVector4 sum;
    sum.setZero();
    for (s32 edge_index = face->m_startEdgeIndex;
         edge_index < face->m_startEdgeIndex + face->m_numEdges; ++edge_index) {
        const hkaiNavMesh::Edge* edge;
        if (edge_index >= instance->m_originalEdges.m_size) {
            edge = &instance->m_ownedEdges[edge_index - instance->m_originalEdges.m_size];
        } else if (instance->m_edgeMap.isEmpty()) {
            edge = &instance->m_instancedEdges[edge_index];
        } else {
            const s32 mapped_index = instance->m_edgeMap[edge_index];
            if (mapped_index == -1)
                edge = &instance->m_originalEdges.m_data[edge_index];
            else
                edge = &instance->m_instancedEdges[mapped_index];
        }
        const hkVector4& vertex_a = edge->m_a < instance->m_originalVertices.m_size ?
                                       instance->m_originalVertices.m_data[edge->m_a] :
                                       instance->m_ownedVertices[edge->m_a - instance->m_originalVertices.m_size];
        const hkVector4& vertex_b = edge->m_b < instance->m_originalVertices.m_size ?
                                       instance->m_originalVertices.m_data[edge->m_b] :
                                       instance->m_ownedVertices[edge->m_b - instance->m_originalVertices.m_size];
        hkVector4 world_a;
        hkVector4 world_b;
        world_a._setTransformedPos(instance->m_referenceFrame.m_transform, vertex_a);
        world_b._setTransformedPos(instance->m_referenceFrame.m_transform, vertex_b);
        if (edge_index == face->m_startEdgeIndex)
            sum.add(world_a);
        sum.add(world_b);
    }
    sum.store<3>(position_out->e.data());
    *position_out *= 1.0f / (face->m_numEdges + 1);
    return true;
}

f32 Unk_7100f7e9f0::sub_7100F7ED6C(sead::Vector3f* normal_out) const {
    auto* instance = _0->m_instances[u32(_8) >> 22].m_instancePtr;
    if (!instance)
        return 0.0f;
    hkVector4 normal;
    const f32 area = instance->sub_71015214B0(_8 & 0x3fffff, normal);
    if (normal_out)
        normal.store<3>(normal_out->e.data());
    return area;
}

// NON_MATCHING: selected storage/index branches and register assignment differ.
s32 Unk_7100f7e9f0::sub_7100F7EEE4() const {
    if (!_0 || _8 == -1)
        return 0;
    auto* instance = _0->m_instances[u32(_8) >> 22].m_instancePtr;
    if (!instance || instance->m_faceDataStriding == 0)
        return 0;
    const s32 face_index = _8 & 0x3fffff;
    const hkInt32* data;
    s32 data_index;
    if (face_index >= instance->m_originalFaces.m_size) {
        data = instance->m_ownedFaceData.data();
        data_index = face_index - instance->m_originalFaces.m_size;
    } else if (instance->m_faceMap.isEmpty()) {
        data = instance->m_instancedFaceData.data();
        data_index = face_index;
    } else {
        const s32 mapped_index = instance->m_faceMap[face_index];
        if (mapped_index == -1) {
            // Reflection 2538e08, mesh destructor 1520ec8 and instance init
            // 152ea04 establish this borrowed pointer's int32 storage/lifetime.
            data = static_cast<const hkInt32*>(instance->m_originalFaceData);
            data_index = face_index;
        } else {
            data = instance->m_instancedFaceData.data();
            data_index = mapped_index;
        }
    }
    return data[data_index * instance->m_faceDataStriding] & 0xffff;
}

}  // namespace ksys::phys
