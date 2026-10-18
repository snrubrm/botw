#include "KingSystem/ActorSystem/actReactionSLinkLimiter.h"
#include <aal/aalListener.h>
#include <aal/aalListenerMgr.h>
#include <aal/aalSystemAccessor.h>
#include <prim/seadScopedLock.h>

namespace ksys::act {

const Unk_71024f02a8::Config sReactionLimiterConfig[13] = {
    {4, 0, 80.0f, 1, -1}, {4, 1, 80.0f, 0, 5}, {4, 1, 80.0f, 0, 5},
    {6, 0, 80.0f, 1, 10}, {6, 0, 80.0f, 1, 10}, {16, 0, 15.0f, 15, 60},
    {6, 0, 40.0f, 1, 10}, {4, 0, 40.0f, 3, 10}, {4, 0, 40.0f, 1, 10},
    {4, 0, 40.0f, 3, 15}, {6, 0, 40.0f, 1, 15}, {4, 0, 40.0f, 5, 10},
    {4, 0, 80.0f, 1, -1},
};

Unk_71024f02a8::Unk_71024f02a8() = default;

// NON_MATCHING: array iteration and list cleanup use different induction variables.
Unk_71024f02a8::~Unk_71024f02a8() {
    for (auto& list : mLists)
        list.freeBuffer();
}

// NON_MATCHING: capacity sign-extension and buffer setup scheduling differ.
void Unk_71024f02a8::init(sead::Heap* heap) {
    for (s32 i = 0; i < 13; ++i)
        mLists[i].tryAllocBuffer(sReactionLimiterConfig[i].capacity, heap);
}

// NON_MATCHING: the compiler folds the configuration flags in the unrolled loop.
void Unk_71024f02a8::calc() {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < 13; ++i)
        sub_7100EC9C3C(mLists[i], sReactionLimiterConfig[i].flags);
    ++mFrame;
}

// NON_MATCHING: index spills, list-sort control flow and handle-fade scheduling differ.
bool Unk_71024f02a8::sub_7100EC9D84(s32 type, const sead::Vector3f& position, bool force) {
    f32 distance = 0.0f;
    if (auto* manager = aal::SystemAccessor::getListenerMgr()) {
        if (auto* listener = manager->getListener(0))
            distance = listener->calcLocalDistance(position);
    }
    const auto& config = sReactionLimiterConfig[type];
    if (config.maxDistance > 0.0f && distance > config.maxDistance)
        return false;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    auto& list = mLists[type];
    if (list.isEmpty())
        return true;
    list.insertionSort([](const Entry* a, const Entry* b) { return a->frame < b->frame; });
    if (auto* recent = list.front()) {
        if (config.minFrames > 0 && !force && recent->frame != mFrame &&
            mFrame - recent->frame <= u32(config.minFrames))
            return false;
        if (recent->frame == mFrame) {
            if (!force) {
                if (distance >= recent->distance)
                    return false;
                recent->handle.fade(0);
                list.erase(recent);
                return true;
            }
            if (list.isFull()) {
                // The original sorts distances after converting them to signed integers.
                list.insertionSort([](const Entry* a, const Entry* b) {
                    return s32(a->distance) > s32(b->distance);
                });
                if (auto* last = list.back()) {
                    if (distance >= last->distance)
                        return false;
                }
            }
        }
    }
    if (list.isFull()) {
        // The same integer-distance ordering is used for eviction.
        list.insertionSort([](const Entry* a, const Entry* b) {
            return s32(a->distance) > s32(b->distance);
        });
        auto* last = list.back();
        if (!last)
            return false;
        last->handle.fade(config.fadeFrames);
        list.erase(last);
    }
    return true;
}

// NON_MATCHING: the list index remains in a register instead of a stack word.
void Unk_71024f02a8::sub_7100ECA2A0(s32 type, const sead::Vector3f& position,
                                  const xlink2::HandleSLink& handle) {
    f32 distance = 0.0f;
    if (auto* manager = aal::SystemAccessor::getListenerMgr()) {
        if (auto* listener = manager->getListener(0))
            distance = listener->calcLocalDistance(position);
    }
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (auto* entry = mLists[type].emplaceBack()) {
        entry->distance = distance;
        entry->handle = handle;
        entry->frame = mFrame;
    }
}

}  // namespace ksys::act
