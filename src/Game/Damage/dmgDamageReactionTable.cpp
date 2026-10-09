#include <utility/aglParameter.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/System/Timer.h"
#include "Game/Damage/dmgInfoManager.h"

namespace uking::dmg {

void DamageReactionTable::sub_71006681D4() {}

void DamageReactionTable::stubbed() {}

bool DamageReactionTable::isReady() {
    return true;
}

s32 DamageReactionTable::sub_71006681E4(const sead::SafeString& name) const {
    const u32 hash = agl::utl::ParameterBase::calcHash(name);
    for (s32 i = 0; i < mItems.size(); ++i) {
        if (mItems[i].mField_0 == s32(hash))
            return i;
    }
    return -1;
}

DamageInfoMgr::Unk868::Unk868() = default;
DamageInfoMgr::Unk868::~Unk868() = default;
void DamageInfoMgr::Unk868::sub_71006682C0() {
    Entry entry;
    mBuckets[0].fill(entry);
    mBuckets[1].fill(entry);
}

void DamageInfoMgr::Unk868::sub_71006685C0() {}

void DamageInfoMgr::Unk868::sub_7100668468() {
    for (auto& bucket : mBuckets) {
        for (auto& entry : bucket) {
            if (!entry.mLink.hasProcInCalcState()) {
                entry.mLink.reset();
                continue;
            }
            ksys::act::acc::Weapon accessor;
            ksys::act::acquireActor(&entry.mLink, &accessor);
            if (accessor.sub_71002EF980() || !(entry.mCountdown > 0.0f))
                entry.mLink.reset();
            else
                ksys::Timer::update(&entry.mCountdown, -1.0f);
        }
    }
}

// NON_MATCHING: clang sinks the origin loads and duplicates bounds-selection/loop tails.
bool DamageInfoMgr::Unk868::sub_71006686D0(s32 group, const ksys::act::BaseProcLink& link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    const auto origin = accessor.getActorMtx().getTranslation();
    f32 distance_squared = -1.0f;
    if (auto* params = ksys::act::GlobalParameter::instance()) {
        if (auto* global = params->getGlobalParam()) {
            const f32 distance = global->mEnemyWeaponPickAllowDist.ref();
            distance_squared = distance * distance;
        }
    }
    auto& bucket = mBuckets[group];
    if (!(distance_squared > 0.0f)) {
        for (auto& entry : bucket) {
            if (entry.mLink.hasProc() && entry.mLink == link)
                return true;
        }
    } else {
        for (auto& entry : bucket) {
            if (!entry.mLink.hasProc())
                continue;
            if (entry.mLink == link)
                return true;
            f32 dx, dz;
            {
                ksys::act::ActorConstDataAccess other;
                ksys::act::acquireActor(&entry.mLink, &other);
                const auto pos = other.getActorMtx().getTranslation();
                dx = pos.x - origin.x;
                dz = pos.z - origin.z;
            }
            if (dx * dx + dz * dz < distance_squared)
                return true;
        }
    }
    return false;
}

bool DamageInfoMgr::Unk868::sub_71006685C4(s32 group, const ksys::act::BaseProcLink& link,
                                        f32 countdown) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    if (sub_71006686D0(group, link))
        return false;
    for (auto& entry : mBuckets[group]) {
        if (!entry.mLink.hasProc()) {
            entry.mLink = link;
            entry.mCountdown = countdown;
            break;
        }
    }
    return true;
}

bool DamageInfoMgr::Unk868::sub_710066885C(s32 group, const ksys::act::BaseProcLink& link) {
    sead::ScopedLock<sead::JobQueueLock> lock(&mLock);
    return sub_71006686D0(group, link);
}

}  // namespace uking::dmg
