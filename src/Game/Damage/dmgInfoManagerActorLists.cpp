#include "Game/Damage/dmgInfoManager.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

bool DamageInfoMgr::Unk790::sub_7100672B00(ksys::act::Actor* actor) const {
    return mStatus == 2 && mLink.hasProcById(actor);
}

bool DamageInfoMgr::Unk790::sub_7100672B1C(ksys::act::Actor* actor) const {
    return mStatus == 1 && mLink.hasProcById(actor);
}

void DamageInfoMgr::Unk28::sub_710065CB68() {}
void DamageInfoMgr::Unk450::sub_710065D134() {}

DamageInfoMgr::Unk28::Unk28() = default;
DamageInfoMgr::Unk28::~Unk28() = default;

// NON_MATCHING: the native entry array lacks the original insertion bounds fallback and uses a different loop branch.
void DamageInfoMgr::Unk28::sub_710065CE14(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    s32 free_index = -1;
    for (s32 i = 0; i < 32; ++i) {
        auto& entry = mEntries[i];
        if (entry.mLink.hasProcById(actor)) {
            entry.mRemove = false;
            return;
        }
        if (free_index < 0 && !entry.mLink.hasProc())
            free_index = i;
    }
    if (free_index >= 0) {
        auto& entry = mEntries[free_index];
        entry.mLink.reset();
        entry.mCountdown = 0.0f;
        entry.mRank = -1;
        entry.mRemove = false;
        entry.mLink.acquire(actor, false);
    }
}

// NON_MATCHING: the removal loop is unrolled instead of the original counted pointer loop.
void DamageInfoMgr::Unk28::sub_710065CF08(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    for (auto& entry : mEntries) {
        if (entry.mLink.hasProcById(actor)) {
            entry.mRemove = true;
            entry.mCountdown = 10.0f;
            break;
        }
    }
}

DamageInfoMgr::Unk450::Unk450() = default;
DamageInfoMgr::Unk450::~Unk450() = default;

// NON_MATCHING: adjacent zero and actor-ID stores are coalesced differently.
void DamageInfoMgr::Unk450::sub_710065D0A8() {
    for (auto& entry : mEntries) {
        entry.mLink.reset();
        entry._10 = 0;
        entry._14 = 0;
        entry.mActorId = -1;
        entry._1c = 0;
        entry._20 = 0;
        entry._24 = false;
        entry._25 = false;
        entry.mRemove = false;
    }
}

// NON_MATCHING: selected-slot bounds checks and index registers differ after the unrolled search.
void DamageInfoMgr::Unk450::sub_710065D428(ksys::act::Actor* actor, const s32& value) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    s32 index = -1;
    s32 free_index = -1;
    for (s32 i = 0; i < 4; ++i) {
        auto& entry = mEntries[i];
        if (entry.mLink.hasProcById(actor)) {
            index = i;
            break;
        }
        if (free_index < 0 && !entry.mLink.hasProc())
            free_index = i;
    }
    if (index >= 0) {
        mEntries[index].mRemove = false;
    } else if (free_index >= 0) {
        index = free_index;
        auto& entry = mEntries[index];
        entry.mLink.reset();
        entry._10 = 0;
        entry._14 = 0;
        entry.mActorId = -1;
        entry._1c = 0;
        entry._20 = 0;
        entry._24 = false;
        entry._25 = false;
        entry.mRemove = false;
        entry.mLink.acquire(actor, false);
        entry._10 = value;
        entry.mActorId = actor->getId();
    }
    if (index >= 0)
        mEntries[index]._20 = ++_a4;
}

void DamageInfoMgr::Unk450::sub_710065D5D4(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    for (auto& entry : mEntries) {
        if (actor->getId() == entry.mActorId) {
            entry.mRemove = true;
            break;
        }
    }
}

void DamageInfoMgr::Unk450::sub_710065D674(ksys::act::Actor* actor, s32 a, bool b, bool c, s32 d) {
    for (auto& entry : mEntries) {
        if (actor->getId() == entry.mActorId) {
            entry._25 = c;
            entry._1c = a;
            entry._14 = d;
            entry._24 = b;
            break;
        }
    }
}

}  // namespace uking::act
