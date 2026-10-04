#include "Game/gameActorContextStuff.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"

#include <prim/seadScopedLock.h>

ActorContextStuff::ActorContextStuff(ksys::act::BaseProc* proc)
    : sead::TListNode<ActorContextStuff*>(this), _638(5, _648.getBufferPtr()),
      _670(5, _680.getBufferPtr()) {
    _708.acquire(proc, false);
}

ActorContextStuff::~ActorContextStuff() {
    erase();
    ksys::phys::System::instance()->removeSystemGroupHandler(_6b0);
}

// NON_MATCHING: the handler-index argument uses w2 rather than x2, and flag stores are scheduled differently.
void ActorContextStuff::sub_710065D8E4(sead::Heap* heap, bool a2) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    _6a8 = ksys::phys::System::instance()->sub_71012168C8(ksys::phys::ContactLayerType::Entity, 0);
    _6b0 = ksys::phys::System::instance()->addSystemGroupHandler(ksys::phys::ContactLayerType::Entity, 0);
    for (s32 i = 0; i < _70.size(); ++i) {
        _70[i].sub_710066074C(this, i, a2, _6a8, heap);
        _670.pushBack(&_70[i]);
    }
    if (a2)
        _68 |= 2;
    else
        _68 &= ~2;
}

Unk_710243be90* ActorContextStuff::sub_710065E2B0(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i) {
        if (_638.at(i)->sub_7100661538(proc)) {
            _638.at(i)->sub_7100660AD8(static_cast<ksys::act::Actor*>(proc));
            _638.unsafeAt(i)->_48->setSystemGroupHandler(_6a8);
            return _638.at(i);
        }
    }
    return nullptr;
}

void ActorContextStuff::sub_710065E4BC(bool delete_actor) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    for (auto& handle : _6b8) {
        if (handle.isAllocatedOrFailed())
            handle.deleteProc();
    }
    _6c = 0;
    while (auto* entry = _638.popBack()) {
        entry->sub_71006613B0(delete_actor);
        _670.pushBack(entry);
    }
    auto* scene = GameSceneSubsys12::instance();
    if ((scene && scene->_a78.isBitOn(1)) || ksys::evt::Manager::instance()->hasActiveEvent()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_708, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: the last entry test is moved before the nested unlock, reducing the stack frame.
bool ActorContextStuff::sub_710065E638() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    bool cleared = false;
    {
        // The original holds this same lock twice while checking the entries.
        sead::ScopedLock<sead::CriticalSection> entries_lock(&_28);
        for (auto& entry : _70) {
            cleared = entry.sub_71006606E8();
            if (!cleared)
                break;
        }
    }
    if (!cleared)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_708, &accessor))
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    return true;
}

bool ActorContextStuff::sub_710065E788(sead::Matrix34f* matrix, s32 index) {
    if (auto* scene = GameSceneSubsys12::instance()) {
        if (scene->_300.hasProc() && scene->_310 == this && scene->sub_7100664F30())
            return sub_710065E88C(matrix, index);
    }
    if (_68 & 2)
        return sub_710065DE90(matrix, index);
    return sub_710065ECF8(matrix, index);
}

void ActorContextStuff::x_0() {
    for (auto& entry : _70)
        entry.sub_7100661988();
}

void ActorContextStuff::x() {
    for (auto& entry : _70)
        entry.sub_71006619DC();
}

// NON_MATCHING: Vector3's assignment emits scalar stores instead of the original aggregate copy.
void ActorContextStuff::sub_710065F12C(sead::Vector3f* out, s32 index) {
    if (out) {
        if (auto* scene = GameSceneSubsys12::instance())
            *out = scene->_bc4[index];
    }
}

// NON_MATCHING: register allocation exchanges the context count and scene registers.
void ActorContextStuff::sub_710065F16C(sead::Vector3f* out, s32 index) {
    if (out) {
        if (auto* scene = GameSceneSubsys12::instance()) {
            const s32 count = sub_710065F044();
            scene->sub_7100664C30(out, count, index);
        }
    }
}

f32 ActorContextStuff::sub_710065F1F0(f32 scale) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (auto* scene = GameSceneSubsys12::instance())
        return scene->sub_7100664B3C(this, scale);
    return 1.0f;
}

bool ActorContextStuff::sub_710065F954() const {
    if (auto* scene = GameSceneSubsys12::instance()) {
        if (scene->_300.hasProc() && scene->_310 == this)
            return scene->x();
    }
    return false;
}

// NON_MATCHING: the compiler combines the progress clamp and exchanges the saved float registers.
f32 ActorContextStuff::sub_710065FA28(ksys::act::BaseProc* proc, f32 time) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i) {
        if (!_638.at(i)->sub_7100661538(proc))
            continue;
        const s32 index = _638.unsafeAt(i)->_68;
        // 65fac8/65fad4 and65fb30/65fb38 retain the original nested lock/unlock pair.
        sead::ScopedLock<sead::CriticalSection> entry_lock(&_28);
        if (index < 0 || index >= _70.size())
            return 0.0f;
        const auto& entry = _70[index];
        if (entry._74 <= 0.0f)
            return entry._70 > time ? 0.0f : 1.0f;
        const f32 progress = (time - entry._70) / entry._74;
        if (progress < 0.0f)
            return 0.0f;
        if (progress > 1.0f)
            return 1.0f;
        return progress;
    }
    return 0.0f;
}

s32 ActorContextStuff::sub_710065F044() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    return _638.size();
}

// NON_MATCHING: the compiler uses an increasing induction variable for the unrolled reduction.
s32 ActorContextStuff::sub_710065F07C() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    s32 count = 0;
    for (s32 i = 0; i < _638.size(); ++i)
        count += (_638.unsafeAt(i)->_28 >> 3) & 1;
    return count;
}

void ActorContextStuff::sub_710065F9AC() {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    const s32 count = _638.size();
    for (s32 i = 0; i < count; ++i)
        _638.at(i)->sub_71006618AC();
}

ksys::act::BaseProcLink* ActorContextStuff::sub_710065F80C(s32 index) {
    sead::ScopedLock<sead::CriticalSection> lock(&_28);
    if (index >= 0 && index < sub_710065F044())
        return &_638.at(index)->_30;
    return nullptr;
}
