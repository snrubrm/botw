#include "Game/gameActorContextStuff.h"

#include <prim/seadScopedLock.h>
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

