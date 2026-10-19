#include "KingSystem/Physics/System/physHavokAI.h"
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
    ai->sub_7100F85974(_10, &_18, flag, _24, y, z);
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

u32 sub_7100F8C540(const Unk_7100F7C274Maybe* obj) {
    return obj->_9c;
}
