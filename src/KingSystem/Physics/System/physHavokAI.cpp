#include "KingSystem/Physics/System/physHavokAI.h"
#include <thread/seadThread.h>
#include <prim/seadScopedLock.h>
#include <Havok/Ai/Pathfinding/World/hkaiWorld.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::phys {

void NavMeshFaceQuery::process(HavokAI* ai) {
    const f32 radius = mCharacter->getRadiusMaybe();
    ai->sub_7100F87334(mCharacter, mPos.isNan() ? nullptr : &mPos, radius, mRadius, _30, this);
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
