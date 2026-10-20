#include "KingSystem/Physics/System/physHavokAI.h"
#include <Havok/Ai/Pathfinding/Utilities/hkaiNavMeshUtils.h>
#include "Game/Actor/aiUnk_NavMeshCallback.h"
#include "KingSystem/Physics/System/physNavMeshEdgeFilter.h"
#include "KingSystem/Physics/System/physNavMeshEdgeResult.h"
#include <geom/seadGeometry.h>
#include <geom/seadRay.h>
#include <geom/seadSegment.h>
#include <thread/seadThread.h>
#include <prim/seadScopedLock.h>
#include <Havok/Ai/Pathfinding/World/hkaiWorld.h>
#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMeshInstance.h>
#include <Havok/Ai/Pathfinding/Streaming/hkaiStreamingCollection.h>
#include "KingSystem/Physics/Ragdoll/physUnk_7102519b90.h"
#include <thread/seadThreadUtil.h>
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/physConversions.h"
#include "Game/gameUnkRttiPlaceholders.h"

#include <prim/seadScopeGuard.h>

#include <Havok/Ai/Pathfinding/NavMesh/Query/hkaiDynamicNavMeshQueryMediator.h>

namespace ksys::phys {

// NON_MATCHING: query temporaries and vector normalization are scheduled differently.
bool HavokAI::sub_7100F851BC(f32 distance, f32 diameter, hkaiWorld* world,
                             const hkVector4f& from, s32 key, const hkVector4f& direction,
                             Unk1* result, u32* out_key,
                             const hkaiAstarEdgeFilter* filter, u32 filter_info) {
    hkaiLineOfSightUtil::DirectPathInput input;
    input.m_startPoint = from;
    input.m_startFaceKey = key;
    if (key == -1) {
        if (result) {
            result->_0.set(std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN());
            result->_30 = false;
        }
        return false;
    }
    input.m_direction = direction;
    input.m_direction.setY(0.0f);
    input.m_direction.normalize<3>();
    input.m_searchRadius = distance;
    if (distance <= std::numeric_limits<f32>::epsilon() ||
        input.m_direction.equalZero().allAreSet(hkVector4fComparison::MASK_XYZ)) {
        if (result) {
            storeToVec3(&result->_0, input.m_startPoint);
            result->_c = result->_0;
            result->_18 = result->_0;
            result->_24 = result->_0;
            result->_30 = true;
        }
        return true;
    }
    input.m_searchRadius = diameter * 0.5f + distance;
    input.m_up = world->m_up;
    input.m_agentInfo.m_diameter = diameter;
    input.m_agentInfo.m_filterInfo = filter_info;
    input.m_edgeFilter = filter ? filter : &sUnk_710260ddf0;
    input.m_outputEdgesOnFailure = true;
    hkaiLineOfSightUtil::LineOfSightOutput output;
    const auto status = hkaiLineOfSightUtil::findDirectPathMaybe(
        world->m_streamingCollection.val(), input, output);
    bool hit = status == hkaiLineOfSightUtil::RESULT_REACHED_RADIUS_LIMIT;
    sead::Vector3f final_point;
    sub_7100F86DE4(result ? &final_point : nullptr, &hit, world, input, output,
                    &input.m_direction);
    if (result) {
        storeToVec3(&result->_0, input.m_startPoint);
        storeToVec3(&result->_c, output.m_finalPoint);
        result->_18 = result->_c;
        result->_24 = final_point;
        result->_30 = hit;
    }
    if (out_key)
        *out_key = output.m_finalFaceKey;
    return hit;
}

// NON_MATCHING: query temporaries and vector normalization are scheduled differently.
bool HavokAI::sub_7100F84D64(f32 half_extent, f32 diameter, hkaiWorld* world,
                             const hkVector4f& from, s32 key, const hkVector4f& position,
                             Unk1* result, u32* out_key,
                             const hkaiAstarEdgeFilter* filter, u32 filter_info) {
    hkaiLineOfSightUtil::LineOfSightInput input;
    input.m_startPoint = from;
    input.m_startFaceKey = key;
    if (key == -1) {
        if (result) {
            result->_0.set(std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN());
            result->_30 = false;
        }
        return false;
    }
    hkaiNavMeshQueryMediator::ClosestPointInput closest_input;
    closest_input.m_position.load<3>(&position(0));
    closest_input.m_halfExtents.set(half_extent, half_extent, 0.0f, 0.0f);
    input.m_goalFaceKey = world->getMediator()->getClosestPoint(closest_input, input.m_goalPoint);
    if (input.m_goalFaceKey == u32(-1)) {
        if (result) {
            storeToVec3(&result->_0, input.m_startPoint);
            result->_c.set(std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN(),
                           std::numeric_limits<f32>::quiet_NaN());
            result->_30 = false;
        }
        return false;
    }
    hkVector4f direction;
    direction.setSub(input.m_goalPoint, input.m_startPoint);
    const f32 length = direction.normalizeWithLength<3>();
    input.m_searchRadius = length;
    if (length <= std::numeric_limits<f32>::epsilon()) {
        if (result) {
            storeToVec3(&result->_0, input.m_startPoint);
            result->_c = result->_0;
            result->_18 = result->_0;
            result->_24 = result->_0;
            result->_30 = true;
        }
        return true;
    }
    input.m_searchRadius = diameter * 0.5f + length + 0.1f;
    input.m_up = world->m_up;
    input.m_agentInfo.m_diameter = diameter;
    input.m_agentInfo.m_filterInfo = filter_info;
    input.m_edgeFilter = filter ? filter : &sUnk_710260ddf0;
    input.m_outputEdgesOnFailure = true;
    hkaiLineOfSightUtil::LineOfSightOutput output;
    const auto status = hkaiLineOfSightUtil::graphSearchMaybe(
        direction, input.m_goalPoint, input.m_goalFaceKey,
        world->m_streamingCollection.val(), input, output);
    bool hit = status == hkaiLineOfSightUtil::RESULT_REACHED_GOAL;
    sead::Vector3f final_point;
    if (status == hkaiLineOfSightUtil::RESULT_REACHED_RADIUS_LIMIT) {
        final_point.set(std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN());
    } else if (result) {
        hkVector4f horizontal = direction;
        horizontal.setY(0.0f);
        const bool has_direction = horizontal.lengthSquared<3>() > 0.0f;
        if (has_direction)
            horizontal.normalize<3>();
        sub_7100F86DE4(&final_point, &hit, world, input, output,
                        has_direction ? &horizontal : nullptr);
    } else {
        sub_7100F86DE4(nullptr, &hit, world, input, output, nullptr);
    }
    if (result) {
        storeToVec3(&result->_0, input.m_startPoint);
        storeToVec3(&result->_c, input.m_goalPoint);
        storeToVec3(&result->_18, output.m_finalPoint);
        result->_24 = final_point;
        result->_30 = hit;
    }
    if (out_key)
        *out_key = output.m_finalFaceKey;
    return hit;
}

// NON_MATCHING: face/edge remap branches and vector calculations are scheduled differently.
void HavokAI::sub_7100F86DE4(sead::Vector3f* out, bool* hit, hkaiWorld* world,
                            const hkaiLineOfSightUtil::InputBase& input,
                            const hkaiLineOfSightUtil::LineOfSightOutput& output,
                            const hkVector4f* direction) {
    auto* collection = world->m_streamingCollection.val();
    if (output.m_numIterationsOut < 2) {
        hkaiAstarEdgeFilter::NavMeshQuery query{};
        query.m_start = {0xffffffff, nullptr, nullptr, input.m_startPoint};
        query.m_goal = {0xffffffff, nullptr, nullptr, output.m_finalPoint};
        query.m_faceKey = input.m_startFaceKey;
        auto* instance = collection->m_instances[input.m_startFaceKey >> 22].m_instancePtr;
        const s32 index = input.m_startFaceKey & 0x3fffff;
        if (index < instance->m_originalFaces.m_size) {
            const s32 mapped = instance->m_faceMap.isEmpty() ? index : instance->m_faceMap[index];
            if (mapped == -1) {
                query.m_face = &instance->m_originalFaces.m_data[index];
                query.m_faceData = static_cast<const hkInt32*>(instance->m_originalFaceData) +
                                  index * instance->m_faceDataStriding;
            } else {
                query.m_face = &instance->m_instancedFaces[mapped];
                query.m_faceData = instance->m_instancedFaceData.begin() +
                                  mapped * instance->m_faceDataStriding;
            }
        } else {
            const s32 owned = index - instance->m_originalFaces.m_size;
            query.m_face = &instance->m_ownedFaces[owned];
            query.m_faceData = instance->m_ownedFaceData.begin() +
                              owned * instance->m_faceDataStriding;
        }
        hkaiAstarEdgeFilter::NavMeshIsEnabledCallbackContext context{
            collection, &input.m_agentInfo, &query, 0x52};
        if (!input.m_edgeFilter->isEnabledMaybe(context)) {
            *hit = false;
            if (out)
                storeToVec3(out, input.m_startPoint);
            return;
        }
    }
    if (!out)
        return;
    if (*hit) {
        out->set(std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN());
        return;
    }
    storeToVec3(out, output.m_finalPoint);
    if (!direction)
        return;

    u32 boundary_key = 0xffffffff;
    bool inspect_final_face = true;
    if (!output.m_visitedEdgesOut.isEmpty()) {
        const u32 key = output.m_visitedEdgesOut[output.m_visitedEdgesOut.getSize() - 1];
        auto* instance = collection->m_instances[key >> 22].m_instancePtr;
        const s32 index = key & 0x3fffff;
        const hkaiNavMesh::Edge* edge;
        if (index < instance->m_originalEdges.m_size) {
            const s32 mapped = instance->m_edgeMap.isEmpty() ? index : instance->m_edgeMap[index];
            edge = mapped == -1 ? &instance->m_originalEdges.m_data[index] :
                                 &instance->m_instancedEdges[mapped];
        } else {
            edge = &instance->m_ownedEdges[index - instance->m_originalEdges.m_size];
        }
        u32 opposite = edge->m_oppositeFace;
        if (opposite != 0xffffffff) {
            const u32 section = edge->m_flags.anyIsSet(hkaiNavMesh::EDGE_EXTERNAL_OPPOSITE) ?
                                    opposite & 0xffc00000 : u32(instance->m_runtimeId) << 22;
            opposite = section | (opposite & 0x3fffff);
        }
        if (opposite != output.m_finalFaceKey) {
            boundary_key = key;
            inspect_final_face = false;
        }
    }
    if (inspect_final_face) {
        auto* instance = collection->m_instances[output.m_finalFaceKey >> 22].m_instancePtr;
        const s32 face_index = output.m_finalFaceKey & 0x3fffff;
        const hkaiNavMesh::Face* face;
        if (face_index < instance->m_originalFaces.m_size) {
            const s32 mapped = instance->m_faceMap.isEmpty() ? face_index :
                                                               instance->m_faceMap[face_index];
            face = mapped == -1 ? &instance->m_originalFaces.m_data[face_index] :
                                 &instance->m_instancedFaces[mapped];
        } else {
            face = &instance->m_ownedFaces[face_index - instance->m_originalFaces.m_size];
        }
        const sead::Ray2f ray(sead::Vector2f(out->x, out->z),
                              sead::Vector2f((*direction)(0), (*direction)(2)));
        s32 edge_index = face->m_numUserEdges > 0 ? face->m_startUserEdgeIndex :
                                                   face->m_startEdgeIndex;
        while (edge_index != -1) {
            const hkaiNavMesh::Edge* edge;
            if (edge_index < instance->m_originalEdges.m_size) {
                const s32 mapped = instance->m_edgeMap.isEmpty() ? edge_index :
                                                                   instance->m_edgeMap[edge_index];
                edge = mapped == -1 ? &instance->m_originalEdges.m_data[edge_index] :
                                     &instance->m_instancedEdges[mapped];
            } else {
                edge = &instance->m_ownedEdges[edge_index - instance->m_originalEdges.m_size];
            }
            const s32 vertex_count = instance->m_originalVertices.m_size;
            const hkVector4& a = edge->m_a < vertex_count ?
                instance->m_originalVertices.m_data[edge->m_a] :
                instance->m_ownedVertices[edge->m_a - vertex_count];
            const hkVector4& b = edge->m_b < vertex_count ?
                instance->m_originalVertices.m_data[edge->m_b] :
                instance->m_ownedVertices[edge->m_b - vertex_count];
            hkVector4 world_a;
            hkVector4 world_b;
            world_a._setTransformedPos(instance->m_referenceFrame.m_transform, a);
            world_b._setTransformedPos(instance->m_referenceFrame.m_transform, b);
            const sead::Segment2f segment(sead::Vector2f(world_a(0), world_a(2)),
                                          sead::Vector2f(world_b(0), world_b(2)));
            if (sead::Geometry::calcSquaredDistanceRayToSegment(ray, segment, nullptr, nullptr) <
                0.010000001f) {
                boundary_key = (output.m_finalFaceKey & 0xffc00000) | u32(edge_index);
                break;
            }
            const s32 user_end = face->m_startUserEdgeIndex + face->m_numUserEdges - 1;
            if (edge_index >= face->m_startUserEdgeIndex && edge_index < user_end) {
                ++edge_index;
            } else if (edge_index == user_end) {
                edge_index = face->m_startEdgeIndex;
            } else if (edge_index >= face->m_startEdgeIndex &&
                       edge_index < face->m_startEdgeIndex + face->m_numEdges - 1) {
                ++edge_index;
            } else {
                return;
            }
        }
    }
    if (boundary_key == 0xffffffff)
        return;
    Unk_7100f7e64c edge(collection, boundary_key, nullptr);
    sead::Vector3f start;
    sead::Vector3f end;
    edge.sub_7100F7E754(&start, &end, nullptr, nullptr, nullptr, nullptr, nullptr);
    const sead::Vector3f delta = end - start;
    const f32 parameter = delta.dot(*out - start) / delta.squaredLength();
    *out = start + delta * parameter;
}


// NON_MATCHING: face/edge traversal and remap selection use different induction registers.
void HavokAI::sub_7100F82278(Unk_7102519a98* obj) {
    if (!obj || !obj->_10)
        return;
    auto* instance = obj->_10;
    for (s32 face_index = 0;
         face_index < instance->m_originalFaces.m_size + instance->m_ownedFaces.getSize();
         ++face_index) {
        const hkaiNavMesh::Face* face;
        if (face_index < instance->m_originalFaces.m_size) {
            const s32 mapped = instance->m_faceMap.isEmpty() ? face_index : instance->m_faceMap[face_index];
            face = mapped == -1 ? &instance->m_originalFaces.m_data[face_index] :
                                 &instance->m_instancedFaces[mapped];
        } else {
            face = &instance->m_ownedFaces[face_index - instance->m_originalFaces.m_size];
        }
        const s32 edge_end = face->m_startUserEdgeIndex + face->m_numUserEdges;
        for (s32 edge_index = face->m_startUserEdgeIndex; edge_index < edge_end; ++edge_index) {
            const hkaiNavMesh::Edge* edge;
            if (edge_index < instance->m_originalEdges.m_size) {
                const s32 mapped = instance->m_edgeMap.isEmpty() ? edge_index : instance->m_edgeMap[edge_index];
                edge = mapped == -1 ? &instance->m_originalEdges.m_data[edge_index] :
                                     &instance->m_instancedEdges[mapped];
            } else {
                edge = &instance->m_ownedEdges[edge_index - instance->m_originalEdges.m_size];
            }
            if (edge->m_oppositeEdge == 0xffffffff)
                continue;
            const s32 section = edge->m_flags.anyIsSet(hkaiNavMesh::EDGE_EXTERNAL_OPPOSITE) ?
                                    s32(edge->m_oppositeEdge >> 22) : instance->m_runtimeId;
            if (section == instance->m_runtimeId)
                continue;
            auto* opposite = _28->m_streamingCollection->m_instances[section].m_instancePtr;
            if (!opposite)
                continue;
            auto* opposite_edge = sub_7100F83D20(opposite->m_originalEdges.m_data,
                opposite->m_originalEdges.m_size, &opposite->m_instancedEdges,
                &opposite->m_ownedEdges, opposite->m_originalEdgeData,
                &opposite->m_instancedEdgeData, &opposite->m_edgeMap,
                edge->m_oppositeEdge & 0x3fffff, opposite->m_edgeDataStriding, 0);
            if (opposite_edge) {
                opposite_edge->m_oppositeEdge = 0xffffffff;
                opposite_edge->m_oppositeFace = 0xffffffff;
            }
        }
    }
}

// NON_MATCHING: remap branches and reverse-edge field stores are grouped differently.
void HavokAI::sub_7100F83848(const hkArray<hkaiUserEdgeUtils::UserEdgePair>* pairs) {
    auto lock = sead::makeScopedLock(_50);
    for (const auto& pair : *pairs) {
        const s32 section_a = _28->m_streamingCollection->sub_71015145D0(pair.m_instanceUidA);
        const s32 section_b = _28->m_streamingCollection->sub_71015145D0(pair.m_instanceUidB);
        if (section_a == -1 || section_b == -1)
            continue;
        auto* a = _28->m_streamingCollection->m_instances[section_a].m_instancePtr;
        auto* b = _28->m_streamingCollection->m_instances[section_b].m_instancePtr;
        if (!a || !b)
            continue;
        const hkaiNavMesh::Face* face;
        if (pair.m_faceA < a->m_originalFaces.m_size) {
            const s32 mapped = a->m_faceMap.isEmpty() ? pair.m_faceA : a->m_faceMap[pair.m_faceA];
            face = mapped == -1 ? &a->m_originalFaces.m_data[pair.m_faceA] : &a->m_instancedFaces[mapped];
        } else {
            face = &a->m_ownedFaces[pair.m_faceA - a->m_originalFaces.m_size];
        }
        const s32 edge_end = face->m_startUserEdgeIndex + face->m_numUserEdges;
        for (s32 edge_index = face->m_startUserEdgeIndex; edge_index < edge_end; ++edge_index) {
            auto* edge = sub_7100F83D20(a->m_originalEdges.m_data, a->m_originalEdges.m_size,
                &a->m_instancedEdges, &a->m_ownedEdges, a->m_originalEdgeData,
                &a->m_instancedEdgeData, &a->m_edgeMap, edge_index, a->m_edgeDataStriding, 0);
            if (!edge || edge->m_oppositeEdge == 0xffffffff)
                continue;
            const s32 opposite_section = edge->m_flags.anyIsSet(hkaiNavMesh::EDGE_EXTERNAL_OPPOSITE) ?
                                            s32(edge->m_oppositeEdge >> 22) : a->m_runtimeId;
            if (opposite_section != section_b || (edge->m_oppositeFace & 0x3fffff) != pair.m_faceB)
                continue;
            auto* opposite = sub_7100F83D20(b->m_originalEdges.m_data, b->m_originalEdges.m_size,
                &b->m_instancedEdges, &b->m_ownedEdges, b->m_originalEdgeData,
                &b->m_instancedEdgeData, &b->m_edgeMap, edge->m_oppositeEdge & 0x3fffff,
                b->m_edgeDataStriding, 0);
            if (!opposite)
                continue;
            edge->m_oppositeEdge = 0xffffffff;
            edge->m_oppositeFace = 0xffffffff;
            opposite->m_oppositeEdge = 0xffffffff;
            opposite->m_oppositeFace = 0xffffffff;
        }
    }
}



void NavMeshFaceQuery::process(HavokAI* ai) {
    const f32 radius = mCharacter->getRadiusMaybe();
    ai->sub_7100F87334(mCharacter, mPos.isNan() ? nullptr : &mPos, radius, mRadius, _30, this);
}

// NON_MATCHING: the ring-buffer store loads the buffer pointer before the capacity (the original loads
// the capacity first); the rest of the function matches.
void HavokAI::sub_7100F81A00(Unk_7102519a98* obj, const sead::Matrix34f& transform) {
    obj->_64 = transform;
    obj->_60.fetchOr(0x100);
    HavokAI* pending = obj->_58.exchange(this);
    if (pending && pending != reinterpret_cast<HavokAI*>(uintptr_t(this) | 1))
        return;
    _40->_120.push(obj);
}

void HavokAI::sub_7100F83460(NavMeshObjMaybe* obj) {
    auto lock = sead::makeScopedLock(_50);
    if (obj->_98 != this && !obj->_98) {
        if (obj->_8)
            _28->sub_710153AABC(obj->_8);
        if (obj->_10)
            _28->sub_710151E18C(obj->_10);
        obj->_98 = this;
    }
}

void HavokAI::sub_7100F834CC(NavMeshObjMaybe* obj, bool queued) {
    auto lock = sead::makeScopedLock(_50);
    if (obj->_98) {
        if (obj->_98 != this)
            return;
        if (!queued) {
            _40->sub_71012AA270(obj);
            obj->_a0.exchange(nullptr);
        }
        if (obj->_8)
            _28->sub_710153AC2C(obj->_8);
        if (obj->_10)
            _28->sub_710151E2EC(obj->_10);
        obj->_98 = nullptr;
    } else if (!queued) {
        _40->sub_71012AA270(obj);
        obj->_a0.exchange(nullptr);
    }
}


void HavokAI::destroyQuery(NavMeshQuery* query) {
    _40->sub_71012A9EE8(query);
}

void HavokAI::sub_7100F83A94(NavMeshQuery* query) {
    _40->sub_71012AA000(query);
}

void HavokAI::sub_7100F83A9C(NavMeshQuery* query) {
    _40->sub_71012AA080(query);
}

bool HavokAI::submitQuery(NavMeshQuery* query) {
    return _40->sub_71012A9F68(query);
}

void HavokAI::sub_7100F82BCC(NavMeshCharacter* nav) {
    nav->_220 &= ~2u;
    nav->_220 |= 1;
    HavokAI* pending = nav->_20.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_138.push(nav);
}

void HavokAI::sub_7100F82C88(NavMeshCharacter* nav) {
    nav->inlineReset();
    nav->_220 &= ~1u;
    nav->_220 |= 2;
    HavokAI* pending = nav->_20.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_138.push(nav);
}

void HavokAI::sub_7100F8305C(NavMeshObjMaybe* obj) {
    obj->_a8.reset(NavMeshObjMaybe::Flag::_2);
    obj->_a8.set(NavMeshObjMaybe::Flag::_1);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F83118(NavMeshObjMaybe* obj) {
    obj->_a8.set(NavMeshObjMaybe::Flag::_4);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F833A8(NavMeshObjMaybe* obj) {
    obj->_a8.reset(NavMeshObjMaybe::Flag::_1);
    obj->_a8.set(NavMeshObjMaybe::Flag::_2);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

void HavokAI::sub_7100F83580(NavMeshObj2Maybe* obj) {
    obj->_80 &= ~2u;
    obj->_80 |= 1;
    HavokAI* pending = obj->_78.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_168.push(obj);
}

void HavokAI::sub_7100F8363C(NavMeshObj2Maybe* obj) {
    obj->_80 |= 4;
    HavokAI* pending = obj->_78.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_168.push(obj);
}

// NON_MATCHING: the common cancellation block keeps owner presence across the calls;
// the original duplicates cancellation in the owner and no-owner paths.
void HavokAI::sub_7100F83790(NavMeshObj2Maybe* obj, bool queued) {
    auto lock = sead::makeScopedLock(_50);
    const bool has_owner = obj->_70 != nullptr;
    if (has_owner && obj->_70 != this)
        return;
    if (!queued) {
        _40->sub_71012AA2F0(obj);
        obj->_78.exchange(nullptr);
    }
    if (has_owner) {
        sub_7100F83848(&obj->mPairs);
        mEdgeObjects.erase(obj);
        obj->_70 = nullptr;
    }
}

// NON_MATCHING: the original orders the two flag updates differently on each path (b: clear 0x10 first; !b: clear 8
// first); matches with `if (on) { reset(_10); change(_8, on); } else { reset(_8); change(_10, !on); }`
void HavokAI::sub_7100F831C0(NavMeshObjMaybe* obj, bool on) {
    obj->_a8.change(NavMeshObjMaybe::Flag::_10, !on);
    obj->_a8.change(NavMeshObjMaybe::Flag::_8, on);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}

// NON_MATCHING: same as sub_7100F831C0 (flags 0x40 / 0x20)
void HavokAI::sub_7100F832B4(NavMeshObjMaybe* obj, bool on) {
    obj->_a8.change(NavMeshObjMaybe::Flag::_40, !on);
    obj->_a8.change(NavMeshObjMaybe::Flag::_20, on);
    HavokAI* pending = obj->_a0.exchange(this);
    if (!pending || uintptr_t(pending) == (uintptr_t(this) | 1))
        _40->_150.push(obj);
}


// NON_MATCHING: bounds and edge-result temporaries use separate stack storage.
void HavokAI::sub_7100F854C4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb) {
    hkArray<hkaiNavMeshUtils::FaceEdgePair> hits;
    if (_90.tryLock()) {
        auto* collection = _28->m_streamingCollection.val();
        auto* mediator = _28->getMediator();
        hkAabb bounds;
        toHkVec4(&bounds.m_min, aabb->getMin());
        toHkVec4(&bounds.m_max, aabb->getMax());
        hkaiNavMeshUtils::queryAabbEdgesMaybe(collection, mediator, bounds, hits);
        for (const auto& hit : hits) {
            Unk_7100f7e64c edge(_28->m_streamingCollection.val(), hit.m_edgeKey, nullptr);
            if (callback->m0(&edge))
                break;
        }
        _90.unlock();
    }
}

// NON_MATCHING: bounds and edge-result temporaries use separate stack storage.
void HavokAI::sub_7100F8565C(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb) {
    hkArray<hkaiNavMeshUtils::FaceEdgePair> hits;
    if (_c8.tryLock()) {
        auto* collection = _30->m_streamingCollection.val();
        auto* mediator = _30->getMediator();
        hkAabb bounds;
        toHkVec4(&bounds.m_min, aabb->getMin());
        toHkVec4(&bounds.m_max, aabb->getMax());
        hkaiNavMeshUtils::queryAabbEdgesMaybe(collection, mediator, bounds, hits);
        for (const auto& hit : hits) {
            Unk_7100f7e64c edge(_30->m_streamingCollection.val(), hit.m_edgeKey, nullptr);
            if (callback->m0(&edge))
                break;
        }
        _c8.unlock();
    }
}

void HavokAI::sub_7100F857F4(Unk_NavMeshCallback* callback, const sead::BoundBox3f* aabb) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    if (_90.tryLock()) {
        sub_7100F854C4(callback, aabb);
        _90.unlock();
    } else if (_c8.tryLock()) {
        sub_7100F8565C(callback, aabb);
        _c8.unlock();
    }
}

// NON_MATCHING: scheduling only: the world load moves after the direction build, and the callee's unused this
// argument costs an extra "mov x0" before the call.
void HavokAI::sub_7100F85974(void* user, const sead::Vector3f* pos, bool flag, f32 a, f32 b, f32 c) {
    if (!_90.tryLock())
        return;

    hkVector4f direction;
    direction.set(pos->x, pos->y, pos->z, 0.0f);
    sub_7100F85A78(_28, &direction, nullptr, flag, user, a, b + b, c);
    _90.unlock();
}

// NON_MATCHING: register allocation only: the original keeps this in x23 / nav in x21, ours swaps the two.
bool HavokAI::sub_7100F87334(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius,
                            f32 search_radius, bool flag, NavMeshFaceCallback* callback) {
    if (!_90.tryLock())
        return false;

    hkVector4f direction;
    if (pos)
        loadFromVec3(&direction, *pos);
    else
        direction = nav->_8->_20;

    const bool hit = sub_7100F85A78(_28, &direction, nav, flag, callback, search_radius, radius + radius,
                                    sUnk_7101ec27f8);
    _90.unlock();
    return hit;
}

// NON_MATCHING: register allocation only: as sub_7100F87334.
bool HavokAI::sub_7100F87464(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius,
                            f32 search_radius, bool flag, NavMeshFaceCallback* callback) {
    if (!_c8.tryLock())
        return false;

    hkVector4f direction;
    if (pos)
        loadFromVec3(&direction, *pos);
    else
        direction = nav->_8->_20;

    const bool hit = sub_7100F85A78(_30, &direction, nav, flag, callback, search_radius, radius + radius,
                                    sUnk_7101ec27f8);
    _c8.unlock();
    return hit;
}

// NON_MATCHING: one prologue copy is scheduled the other way round (the original moves `pos` before
// `radius`); the body, both lock paths and the return value match.
bool HavokAI::sub_7100F87594(NavMeshCharacter* nav, const sead::Vector3f* pos, f32 radius,
                             f32 search_radius, bool flag, NavMeshFaceCallback* callback) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    bool hit = false;
    if (_90.tryLock()) {
        hit = sub_7100F87334(nav, pos, radius, search_radius, flag, callback);
        _90.unlock();
    } else if (_c8.tryLock()) {
        hit = sub_7100F87464(nav, pos, radius, search_radius, flag, callback);
        _c8.unlock();
    }
    return hit;
}

Unk_7100f7e9f0 HavokAI::sub_7100F87A80(sead::Vector3f* out, const sead::Vector3f& from,
                                       const sead::Vector3f& to) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    if (_90.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F87760(out, from, to);
        _90.unlock();
        return result;
    }
    if (_c8.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F878F0(out, from, to);
        _c8.unlock();
        return result;
    }
    return Unk_7100f7e9f0();
}

Unk_7100f7e9f0 HavokAI::sub_7100F87ED0(sead::Vector3f* out, const sead::Vector3f& to, f32 a3) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    if (_90.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F87C40(out, to, a3);
        _90.unlock();
        return result;
    }
    if (_c8.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F87D88(out, to, a3);
        _c8.unlock();
        return result;
    }
    return Unk_7100f7e9f0();
}

Unk_7100f7e9f0 HavokAI::sub_7100F88B1C(NavMeshCharacter* nav, sead::Vector3f* out,
                                       const sead::Vector3f& to, f32 a3) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    if (_90.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F8885C(nav, out, to, a3);
        _90.unlock();
        return result;
    }
    if (_c8.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F889BC(nav, out, to, a3);
        _c8.unlock();
        return result;
    }
    return Unk_7100f7e9f0();
}

// NON_MATCHING: the original's callee call does not set x0 (its first argument slot is unused), so
// ours has one extra "mov x0" before the call.
Unk_7100f7e9f0 HavokAI::sub_7100F88FD0(NavMeshCharacter* nav, sead::Vector3f* out,
                                       const sead::Vector3f& to, f32 value) {
    if (_c8.tryLock()) {
        const Unk_7100f7e9f0 result = sub_7100F88CF8(out, &_c8.mEvent, _30, nav, to, value);
        _c8.unlock();
        return result;
    }
    return Unk_7100f7e9f0();
}

// NON_MATCHING: clang folds the shared 10.0f / flag branch into an fcsel and rematerialises the argument set-up
// at the call; the original branches to one shared block that re-tests _2c.
void Unk_7102372790::process(HavokAI* ai) {
    f32 y = _28;
    f32 z;
    bool flag;
    if (y > 0.0f) {
        if (_2c >= 0 && _30 > 0.0f) {
            z = _30;
            flag = _2c != 0;
        } else {
            z = 10.0f;
            if (_2c < 0)
                flag = true;
            else
                flag = _2c != 0;
        }
    } else {
        y = 0.0f;
        z = 10.0f;
        flag = true;
    }
    ai->sub_7100F85974(static_cast<NavMeshFaceCallback*>(this), &_18, flag, _24, y, z);
}

// NON_MATCHING: two argument copies in the prologue are scheduled the other way round
bool HavokAI::sub_7100F86174(const sead::Vector3f& from, const sead::Vector3f& to, Unk1* result, f32 a4) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    bool hit = false;
    if (_90.tryLock()) {
        hit = sub_7100F85C00(a4, &from, &to, result);
        _90.unlock();
    } else if (_c8.tryLock()) {
        hit = sub_7100F85EB8(a4, &from, &to, result);
        _c8.unlock();
    }
    return hit;
}

// Written by sub_7100F809BC (they sit next to the counter below in the original data).
KSYS_VISIBILITY_HIDDEN u8 sUnk_710260DE48;
KSYS_VISIBILITY_HIDDEN u8 sUnk_710260DE4C;
// 0x710260de10 (.bss): the query filter object whose address the closest-point queries
// 0x7100f8885c / 0x7100f889bc store in QueryInput::_10. Its contents are not read by these
// functions; the Havok mediator owns the filter definition.
u8 sUnk_710260de10;
// Defined in the NavMeshCharacter TU with the request id allocator.
extern sead::Atomic<u32> sUnk_710260de50;

// 0x7100f809bc (unnamed): resets the nav mesh id state (the counter the request ids come from).
void sub_7100F809BC() {
    sUnk_710260DE48 = 0;
    sUnk_710260DE4C = 0xfe;
    sUnk_710260de50 = 1;
}

bool HavokAI::sub_7100F86334(NavMeshCharacter* nav, const Unk2& query, const u32* tail,
                            Unk1* result) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    bool hit = false;
    if (_90.tryLock()) {
        hit = sub_7100F8688C(nav, query, tail, result);
        _90.unlock();
    } else if (_c8.tryLock()) {
        hit = sub_7100F864DC(nav, query, tail, result);
        _c8.unlock();
    }
    return hit;
}

bool HavokAI::sub_7100F86324(NavMeshCharacter* nav, const Unk2& query, Unk1* result) {
    return sub_7100F86334(nav, query, &query._34, result);
}

void HavokAI::sub_7100F81854() {
    _38->sub_7100F8962C();
}

bool HavokAI::startNavMeshSystemThread() {
    return _38->start();
}

void HavokAI::sendStepMessageToNavMeshSysThread(f32 dt) {
    _38->sub_7100F895FC(dt);
}

void HavokAI::sub_7100F8185C() {
    _38->_10c = false;
}

// NON_MATCHING: vector loads, the mediator result test and lock cleanup are scheduled differently.
Unk_7100f7e9f0 HavokAI::sub_7100F87760(sead::Vector3f* out, const sead::Vector3f& from,
                                      const sead::Vector3f& to) {
    hkaiNavMeshQueryMediator::RaycastInput input;
    loadFromVec3(&input.m_from, from);
    loadFromVec3(&input.m_to, to);
    auto& lock = _90;
    if (!lock.tryLock())
        return {};
    auto unlock = sead::makeScopeGuard([&lock] { lock.unlock(); });
    hkaiNavMeshQueryMediator::RaycastOutput hit;
    if (!_28->getMediator()->castRay(input, hit))
        return {};
    out->x = from.x + (to.x - from.x) * hit.m_hitFraction;
    out->y = from.y + (to.y - from.y) * hit.m_hitFraction;
    out->z = from.z + (to.z - from.z) * hit.m_hitFraction;
    // Construct the result before releasing our lock reference. Its ctor retains its own event ref.
    return Unk_7100f7e9f0(_28->m_streamingCollection.val(), s32(hit.m_faceKey), &lock.mEvent);
}

// NON_MATCHING: vector loads, the mediator result test and lock cleanup are scheduled differently.
Unk_7100f7e9f0 HavokAI::sub_7100F878F0(sead::Vector3f* out, const sead::Vector3f& from,
                                      const sead::Vector3f& to) {
    hkaiNavMeshQueryMediator::RaycastInput input;
    loadFromVec3(&input.m_from, from);
    loadFromVec3(&input.m_to, to);
    auto& lock = _c8;
    if (!lock.tryLock())
        return {};
    auto unlock = sead::makeScopeGuard([&lock] { lock.unlock(); });
    hkaiNavMeshQueryMediator::RaycastOutput hit;
    if (!_30->getMediator()->castRay(input, hit))
        return {};
    out->x = from.x + (to.x - from.x) * hit.m_hitFraction;
    out->y = from.y + (to.y - from.y) * hit.m_hitFraction;
    out->z = from.z + (to.z - from.z) * hit.m_hitFraction;
    return Unk_7100f7e9f0(_30->m_streamingCollection.val(), s32(hit.m_faceKey), &lock.mEvent);
}

// NON_MATCHING: input-vector stores and shared-lock register allocation differ.
Unk_7100f7e9f0 HavokAI::sub_7100F87C40(sead::Vector3f* out, const sead::Vector3f& to,
                                      f32 radius) {
    hkaiNavMeshQueryMediator::ClosestPointInput input;
    toHkVec4(&input.m_position, to);
    input.m_halfExtents.set(radius, radius, 0.0f, 0.0f);
    auto& lock = _90;
    if (!lock.tryLock())
        return {};
    auto unlock = sead::makeScopeGuard([&lock] { lock.unlock(); });
    hkVector4 closest;
    const hkUint32 key = _28->getMediator()->getClosestPoint(input, closest);
    if (key == hkUint32(-1))
        return {};
    if (out)
        storeToVec3(out, closest);
    return Unk_7100f7e9f0(_28->m_streamingCollection.val(), s32(key), &lock.mEvent);
}

// NON_MATCHING: input-vector stores and shared-lock register allocation differ.
Unk_7100f7e9f0 HavokAI::sub_7100F87D88(sead::Vector3f* out, const sead::Vector3f& to,
                                      f32 radius) {
    hkaiNavMeshQueryMediator::ClosestPointInput input;
    toHkVec4(&input.m_position, to);
    input.m_halfExtents.set(radius, radius, 0.0f, 0.0f);
    auto& lock = _c8;
    if (!lock.tryLock())
        return {};
    auto unlock = sead::makeScopeGuard([&lock] { lock.unlock(); });
    hkVector4 closest;
    const hkUint32 key = _30->getMediator()->getClosestPoint(input, closest);
    if (key == hkUint32(-1))
        return {};
    if (out)
        storeToVec3(out, closest);
    return Unk_7100f7e9f0(_30->m_streamingCollection.val(), s32(key), &lock.mEvent);
}

// NON_MATCHING: the input-vector setup is scheduled differently (the original loads the position
// with lane loads and stores the half-extent lanes separately); the query and lock sequence match.
bool HavokAI::sub_7100F842A8(NavMeshCharacter* nav, sead::Vector3f* out, const void* a,
                             const void* b, u64 flag, void* result, const void* user) {
    if (sead::ThreadMgr::instance()->getCurrentThread() != _38) {
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(
            sead::ThreadMgr::instance()->getCurrentThread()->getPriority()));
        static_cast<void>(sead::ThreadUtil::ConvertPriorityPlatformToSead(_38->getPriority()));
    }

    if (_90.tryLock()) {
        const bool hit = sub_7100F84484(nav, out, a, b, flag, result, user);
        _90.unlock();
        return hit;
    }
    if (_c8.tryLock()) {
        const bool hit = sub_7100F84910(nav, out, a, b, flag, result, user);
        _c8.unlock();
        return hit;
    }
    return false;
}

Unk_7100f7e9f0 HavokAI::sub_7100F8885C(NavMeshCharacter* nav, sead::Vector3f* out,
                                       const sead::Vector3f& to, f32 radius) {
    hkaiNavMeshQueryMediator::ClosestPointInput input;
    toHkVec4(&input.m_position, to);
    input.m_halfExtents.set(radius, radius, 0.0f);
    input._0 = nav->_8->_98;
    input._10 = &sUnk_710260de10;
    auto& lock = _90;
    if (!lock.tryLock())
        return {};
    auto unlock = sead::makeScopeGuard([&lock] { lock.unlock(); });
    hkVector4 closest;
    const hkUint32 key = _28->getMediator()->getClosestPoint(input, closest);
    if (key == hkUint32(-1))
        return {};
    if (out)
        storeToVec3(out, closest);
    return Unk_7100f7e9f0(_28->m_streamingCollection.val(), s32(key), &lock.mEvent);
}

// NON_MATCHING: as sub_7100F8885C (input-vector setup only).
Unk_7100f7e9f0 HavokAI::sub_7100F889BC(NavMeshCharacter* nav, sead::Vector3f* out,
                                       const sead::Vector3f& to, f32 radius) {
    hkaiNavMeshQueryMediator::ClosestPointInput input;
    toHkVec4(&input.m_position, to);
    input.m_halfExtents.set(radius, radius, 0.0f);
    input._0 = nav->_8->_98;
    input._10 = &sUnk_710260de10;
    auto& lock = _c8;
    if (!lock.tryLock())
        return {};
    auto unlock = sead::makeScopeGuard([&lock] { lock.unlock(); });
    hkVector4 closest;
    const hkUint32 key = _30->getMediator()->getClosestPoint(input, closest);
    if (key == hkUint32(-1))
        return {};
    if (out)
        storeToVec3(out, closest);
    return Unk_7100f7e9f0(_30->m_streamingCollection.val(), s32(key), &lock.mEvent);
}


}  // namespace ksys::phys

Unk_71024f6f70::~Unk_71024f6f70() = default;

// As res::EntryFactory<T>::newResource_.
sead::DirectResource* Unk_71024f6f70::newResource_(sead::Heap* heap_, s32 alignment) {
    sead::Heap* heap = ksys::util::getHeapOrCurrentHeap(heap_);
    sead::ScopedCurrentHeapSetter setter{heap};
    return new (heap, alignment, std::nothrow_t{}) ksys::phys::Unk_7102519b90;
}

// Placeholder: the objects whose +0x60 / +0xc0 / +0x48 / +0x9c fields the helpers below read.
struct Unk_7100F7C274Maybe {
    u8 _0[0x60];
    void* _60;
    u8 _68[0x9c - 0x68];
    u8 _9c;
    u8 _9d[0xc0 - 0x9d];
    u32 _c0;
    u8 _c4[0x48];
};

bool sub_7100F7C274(const Unk_7100F7C274Maybe* obj) {
    return obj->_60 != nullptr;
}

u32 sub_7100F7C5E0(const Unk_7100F7C274Maybe* obj) {
    return obj->_c0;
}
