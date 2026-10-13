#include "Game/gameEventMgr1.h"
#include <heap/seadHeap.h>
#include <prim/seadScopedLock.h>
#include <new>

SEAD_SINGLETON_DISPOSER_IMPL(EventMgr1)

EventMgr1::~EventMgr1() {
    for (s32 i = 0; i < mDeathCounters.size(); ++i) {
        auto* counter = mDeathCounters.unsafeAt(i);
        counter->~Unk_7102518b60();
        if (mHeap)
            mHeap->free(counter);
    }
    mDeathCounters.freeBuffer();
    for (s32 i = 0; i < mGetCounters.size(); ++i) {
        auto* counter = mGetCounters.unsafeAt(i);
        counter->~Unk_7102518b60();
        if (mHeap)
            mHeap->free(counter);
    }
    mGetCounters.freeBuffer();
}

bool EventMgr1::init(s32 capacity, sead::Heap* heap) {
    if (!heap)
        return false;
    mHeap = heap;
    if (capacity < 1)
        return false;
    if (!mDeathCounters.tryAllocBuffer(capacity, mHeap) ||
        !mGetCounters.tryAllocBuffer(capacity, mHeap))
        return false;
    for (s32 i = 0; i < mDeathCounters.capacity(); ++i) {
        auto* counter = new (mHeap, std::nothrow_t{}) Unk_7102518b60;
        if (!counter)
            return false;
        mDeathCounters.pushBack(counter);
    }
    for (s32 i = 0; i < mGetCounters.capacity(); ++i) {
        auto* counter = new (mHeap, std::nothrow_t{}) Unk_7102518b60;
        if (!counter)
            return false;
        mGetCounters.pushBack(counter);
    }
    return true;
}

void EventMgr1::calc() {
    for (s32 i = 0; i < mDeathCounters.size(); ++i)
        mDeathCounters[i]->sub_710127F594();
    for (s32 i = 0; i < mGetCounters.size(); ++i)
        mGetCounters[i]->sub_710127F594();
}

void EventMgr1::initBeforeStageGenB() {
    for (s32 i = 0; i < mDeathCounters.size(); ++i)
        mDeathCounters[i]->sub_710127F6C8();
    for (s32 i = 0; i < mGetCounters.size(); ++i)
        mGetCounters[i]->sub_710127F6C8();
}

bool EventMgr1::sub_7100E48A90(const sead::SafeString& actor_name,
                            const sead::SafeString& game_data_name, bool initialize) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    s32 free_index = -1;
    for (s32 i = 0; i < mDeathCounters.size(); ++i) {
        auto* counter = mDeathCounters[i];
        if (counter->mActorName == actor_name)
            return true;
        if (free_index < 0 && counter->sub_710127F648())
            free_index = i;
    }
    if (free_index < 0)
        return false;
    return mDeathCounters[free_index]->sub_710127F6F4(actor_name, game_data_name, initialize);
}

void EventMgr1::sub_7100E48C44(const sead::SafeString& name) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mDeathCounters.size(); ++i) {
        auto* counter = mDeathCounters[i];
        if (counter->mActorName == name)
            counter->sub_710127F6C8();
    }
}

void EventMgr1::sub_7100E48D8C(const sead::SafeString& name) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mDeathCounters.size(); ++i) {
        auto* counter = mDeathCounters[i];
        if (counter->mActorName == name)
            counter->sub_710127F668(1);
    }
}

bool EventMgr1::sub_7100E48ED8(const sead::SafeString& actor_name,
                            const sead::SafeString& game_data_name, bool initialize) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    s32 free_index = -1;
    for (s32 i = 0; i < mGetCounters.size(); ++i) {
        auto* counter = mGetCounters[i];
        if (counter->mActorName == actor_name)
            return true;
        if (free_index < 0 && counter->sub_710127F648())
            free_index = i;
    }
    if (free_index < 0)
        return false;
    return mGetCounters[free_index]->sub_710127F6F4(actor_name, game_data_name, initialize);
}

void EventMgr1::sub_7100E4908C(const sead::SafeString& name) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mGetCounters.size(); ++i) {
        auto* counter = mGetCounters[i];
        if (counter->mActorName == name)
            counter->sub_710127F6C8();
    }
}

void EventMgr1::sub_7100E491D4(const sead::SafeString& name) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mGetCounters.size(); ++i) {
        auto* counter = mGetCounters[i];
        if (counter->mActorName == name)
            counter->sub_710127F668(1);
    }
}
