#include "Game/Actor/actGuardian.h"
#include "Game/Actor/actGuardianRegistry.h"
#include <prim/seadScopedLock.h>
#include "Game/Damage/dmgInfoManager.h"

Unk_710243c250::Unk_710243c250(ksys::act::Actor* owner)
    : sead::TListNode<Unk_710243c250*>(this) {
    _28.acquire(owner, false);
    // The original initializes all four state bytes to 0xff after acquiring the owner.
    _40 = {0xff, 0xff, 0xff, 0xff};
}

Unk_710243c250::~Unk_710243c250() = default;

// NON_MATCHING: vtable and first bucket list stores are scheduled differently.
Unk_710243c280::Unk_710243c280() = default;

Unk_710243c280::~Unk_710243c280() = default;

Unk_710243c2a0::~Unk_710243c2a0() = default;

void Unk_710243c250::sub_710066E134(s32 controller_type, bool enabled) {
    _40.mControllerType = controller_type;
    _40.mEnabled = enabled;
    uking::dmg::DamageInfoMgr::instance()->getGuardianRegistry().sub_710066E548(this);
}

// NON_MATCHING: the registry removal body is inlined instead of tail-called.
void Unk_710243c250::sub_710066E15C() {
    uking::dmg::DamageInfoMgr::instance()->getGuardianRegistry().sub_710066E648(this);
}

// NON_MATCHING: the bucket sequence load and address calculation are scheduled later.
void Unk_710243c280::sub_710066E548(Unk_710243c250* entry) {
    auto& bucket = mBuckets[entry->_40.mControllerType];
    entry->_3c = 0;
    auto lock = sead::makeScopedLock(bucket.mLock);
    bucket.mEntries.pushBack(entry);
    auto* prev = bucket.mEntries.prev(entry);
    if (prev && prev->mData)
        entry->_3c = prev->mData->_3c + 1;
    entry->_40.mSequence = mSequence;
    entry->_40.mBucketSequence = bucket.mSequence;
    ++mSequence;
    ++bucket.mSequence;
}

// NON_MATCHING: rank decrement uses subtraction instead of adding 255.
void Unk_710243c280::sub_710066E648(Unk_710243c250* entry) {
    const s32 type = entry->_40.mControllerType;
    if (type >= mBuckets.size())
        return;
    auto& bucket = mBuckets[type];
    auto lock = sead::makeScopedLock(bucket.mLock);
    for (auto* node = bucket.mEntries.next(entry); node && node->mData;
         node = bucket.mEntries.next(node)) {
        --node->mData->_3c;
    }
    bucket.mEntries.erase(entry);
}

// NON_MATCHING: count comparisons and filtered-list null/flag branches are simplified.
f32 Unk_710243c280::getNearestDistance(bool include_enabled) {
    f32 nearest = std::numeric_limits<f32>::max();
    for (auto& bucket : mBuckets) {
        auto lock = sead::makeScopedLock(bucket.mLock);
        auto* node = bucket.mEntries.front();
        if (!include_enabled) {
            while (node && node->mData && node->mData->_40.mEnabled)
                node = bucket.mEntries.next(node);
        }
        if (node && node->mData)
            nearest = sead::Mathf::min(node->mData->_38, nearest);
    }
    return nearest;
}
