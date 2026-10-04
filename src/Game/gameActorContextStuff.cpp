#include "Game/gameActorContextStuff.h"
#include "Game/gameSceneSubsys12.h"

#include <prim/seadScopedLock.h>

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
