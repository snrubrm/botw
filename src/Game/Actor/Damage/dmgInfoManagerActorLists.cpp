#include "Game/Actor/Damage/dmgInfoManager.h"
#include <atomic>
#include <prim/seadScopedLock.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/World/worldManager.h"

namespace uking::act {

bool DamageInfoMgr::Unk790::sub_71006726DC(s32 weather) {
    auto* wm = ksys::world::Manager::instance();
    if (!wm)
        return false;
    const auto climate = wm->getCurrentClimate();
    switch (weather) {
    case 0:
        return wm->getWeatherRainRate(climate) > 0 || wm->getWeatherHeavyRainRate(climate) > 0 ||
               wm->getWeatherStormRate(climate) > 0;
    case 1:
        return wm->getWeatherBlueskyRate(climate) > 0 || wm->getWeatherCloudyRate(climate) > 0;
    case 2:
        return wm->getWeatherRainRate(climate) > 0 || wm->getWeatherHeavyRainRate(climate) > 0;
    default:
        return false;
    }
}

bool DamageInfoMgr::Unk790::sub_7100672B00(ksys::act::Actor* actor) const {
    return mStatus == 2 && mLink.hasProcById(actor);
}

bool DamageInfoMgr::Unk790::sub_7100672B1C(ksys::act::Actor* actor) const {
    return mStatus == 1 && mLink.hasProcById(actor);
}

bool DamageInfoMgr::Unk790::tryAcquireWizzrobeWeatherRequest(ksys::act::BaseProc* proc, s32 weather) {
    while (mLock.load() == 1) {
    }
    while (!mLock.compareExchange(0, 1)) {
    }

    bool acquired;
    if (mLink.hasProc()) {
        acquired = false;
    } else {
        _4 = weather;
        mLink.acquire(proc, false);
        mStatus = 1;
        acquired = true;
    }

    std::atomic_thread_fence(std::memory_order_seq_cst);
    while (!mLock.compareExchange(1, 0)) {
    }
    return acquired;
}

void DamageInfoMgr::Unk790::sub_7100672888(ksys::act::Actor* actor) {
    while (mLock.load() == 1) {
    }
    while (!mLock.compareExchange(0, 1)) {
    }

    if (mLink.hasProcById(actor)) {
        mLink.reset();
        mStatus = 0;
        _4 = -1;
        _20.sub_7100710DE4();
        mParams.mActorName = "";
        mParams.mIgniteRotSpd = 0.0f;
        mParams.mOffsetY = 6.0f;
        mParams.mCenterOffsetXZ = 5.0f;
        mParams.mRandRadius = 12.0f;
        mParams.mIntervalMax = 20.0f;
        mParams.mIntervalMin = 15.0f;
        _20.sub_7100710890(s32(mParams.mIntervalMin), s32(mParams.mIntervalMax));
    }

    std::atomic_thread_fence(std::memory_order_seq_cst);
    while (!mLock.compareExchange(1, 0)) {
    }
}

bool DamageInfoMgr::Unk790::sub_710067298C(ksys::act::BaseProc* proc, const Unk790Params& params) {
    if (!mLink.hasProcById(proc))
        return false;
    mParams.mActorName = params.mActorName;
    mParams.mIgniteRotSpd = params.mIgniteRotSpd;
    mParams.mOffsetY = params.mOffsetY;
    mParams.mCenterOffsetXZ = params.mCenterOffsetXZ;
    mParams.mRandRadius = params.mRandRadius;
    mParams.mIntervalMax = params.mIntervalMax;
    mParams.mIntervalMin = params.mIntervalMin;
    _20.sub_7100710DE4();
    _20.sub_7100710890(s32(mParams.mIntervalMin), s32(mParams.mIntervalMax));
    _20._1c = mParams.mIgniteRotSpd;
    _20._38 = mParams.mRandRadius;
    _20._30 = mParams.mCenterOffsetXZ;
    _20._34 = mParams.mOffsetY;
    mStatus = 2;
    return true;
}

bool DamageInfoMgr::Unk_710243c3a0::m1(sead::Vector3f* out) {
    if (!mOwner)
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&mOwner->mLink, &accessor))
        return false;
    accessor.getActorMtx().getTranslation(*out);
    return true;
}

bool DamageInfoMgr::Unk_710243c3a0::m2(sead::BufferedSafeString* out) {
    if (!mOwner)
        return false;
    out->copy(mOwner->mParams.mActorName);
    return !out->isEmpty();
}

void DamageInfoMgr::Unk_710243c3a0::m3(ksys::act::Actor* actor) {
    if (!actor || !mOwner)
        return;
    auto* link = &mOwner->mLink;
    sub_7100738CB0(actor, link);
    sub_7100738D50(actor, link);
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
