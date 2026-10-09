#include "Game/AI/AI/aiPriestBossActorNormalMode.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100742478.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"

// Declaration only; the original source namespace is unknown.
s32 sub_710071E288(ksys::act::Actor* actor);

namespace uking::ai {

// 0x710050b7a8: the second unit lookup's result is discarded natively.
bool PriestBossActorNormalMode::sub_710050B7A8() {
    if (!sub_7100505BE4())
        return false;
    sub_7100505BE4();
    if (_e4 == 2 || u32(_e4 - 2) > 8)
        return false;
    if (!sub_7100505BE4())
        return false;
    dmg::Unk_7100671794_Entry entry;
    entry.mLink.acquire(mActor, false);
    entry.mDistance = 10000.0f;
    auto* limiter = &dmg::DamageInfoMgr::instance()->get4f8();
    return limiter->sub_7100671A74(&entry, sub_7100505BE4()->_98);
}

// 0x710050bb0c
// NON_MATCHING: compiler reverses the two phase-test branches.
void PriestBossActorNormalMode::sub_710050BB0C() {
    if (!sub_7100505BE4())
        return;
    _e4 = sub_7100505BE4()->sub_7100719534(mActor);
    auto* unit = sub_7100505BE4();
    if (unit->_3c == Unk_7102450fa8::Phase::_3) {
        sub_710050BDCC();
    } else if (unit->_3c == Unk_7102450fa8::Phase::_1) {
        sub_710050BBC0();
    } else {
        _12c = *mReturnFromBananaMode_a ? 1 : 2;
        _130 = sub_710050B6CC();
        sub_710050AE6C(_12c);
    }
    _b0 = sub_7100505BE4()->_3c;
    *mReturnFromBananaMode_a = false;
}

// NON_MATCHING: the original uses separate scalar stores where the natural constructor merges them.
PriestBossActorNormalMode::PriestBossActorNormalMode(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossActorNormalMode::~PriestBossActorNormalMode() {
    if (_120) {
        delete _120;
        _120 = nullptr;
    }
}

bool PriestBossActorNormalMode::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

// NON_MATCHING: the two vector copies use different load and store scheduling.
void PriestBossActorNormalMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    _d8 = 0;
    *mEquipWeaponBufIndex_a = sub_710071E288(mActor);
    const auto& target = sub_71005D9330(mActor);
    _c0 = target;
    _cc = target;
    _b4.value = *mFramesRestrictEarthRelease_s;
    _b4.previous_value = *mFramesRestrictEarthRelease_s;
    sub_710050BB0C();
}

void PriestBossActorNormalMode::leave_() {
    if (sub_7100505BE4()) {
        sub_7100505BE4();
        if (_e4 != 2 && u32(_e4 - 2) < 9)
            dmg::DamageInfoMgr::instance()->get4f8().sub_7100671F78(mActor);
    }
    if (auto* unit = sub_7100505BE4())
        unit->sub_7100719D5C(mActor);
    PriestBossMode::leave_();
}

void PriestBossActorNormalMode::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mApproachWarpRate_s, "ApproachWarpRate");
    getStaticParam(&mApproachStartDistance_s, "ApproachStartDistance");
    getStaticParam(&mLeaveStartDistance_s, "LeaveStartDistance");
    getStaticParam(&mLeaveStartTime_s, "LeaveStartTime");
    getStaticParam(&mWaitMinTime_s, "WaitMinTime");
    getStaticParam(&mWaitMaxTime_s, "WaitMaxTime");
    getStaticParam(&mSecondHalfLifePercent_s, "SecondHalfLifePercent");
    getStaticParam(&mFramesRestrictEarthRelease_s, "FramesRestrictEarthRelease");
    getStaticParam(&mWarpPosDistFromPlayer_s, "WarpPosDistFromPlayer");
    getStaticParam(&mStageMarginRateForEarthRelease_s, "StageMarginRateForEarthRelease");
    getStaticParam(&mIsManagedBtlMgr_s, "IsManagedBtlMgr");
    getDynamicParam(&mFromSyncMode_d, "FromSyncMode");
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

f32 PriestBossActorNormalMode::m35() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m36() {
    if (!sub_7100505BE4())
        return 1.0f;
    return sub_7100505BE4()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_11)) ? 1.0f :
                                                                                         0.01f;
}

f32 PriestBossActorNormalMode::m37() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m38() {
    return 0.0f;
}

// NON_MATCHING: the original evaluates the `std::pow` argument before loading `GlobalRandom::instance()` (powf, then
// the instance load, then getU32); ours loads the instance first (C++17 object-first order). A named local for the
// pow expression (`const f32 max = ...; return instance()->getF32Range(0.5f, max);`) matches exactly (borderline, not
// applied).
f32 PriestBossActorNormalMode::getWeight(Attack attack) {
    return sead::GlobalRandom::instance()->getF32Range(
        0.5f, std::pow(0.9f, f32(_e8[attack])) * 0.5f + 0.5f);
}

// NON_MATCHING: same getWeight() tail difference as m41
f32 PriestBossActorNormalMode::m39() {
    if (sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0 &&
        sub_7100505BE4()->_40 <= *mSecondHalfLifePercent_s) {
        return 0.0f;
    }
    if (!(sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0)) {
        if (sub_7100505BE4()) {
            sub_7100505BE4();
            if (_e4 != 2 && u32(_e4 - 2) < 9) {
                if (u32(_130 - 4) < 5)
                    return 0.0f;
                if (!dmg::DamageInfoMgr::instance()->get4f8().sub_7100671ED8(mActor))
                    return 0.0f;
            }
        }
        if (*mEquipWeaponBufIndex_a == 0)
            return 0.0f;
    }
    if (!sub_7100742588(nullptr, mActor->m45(), &sub_71005D9330(mActor), 10.0f))
        return 0.0f;
    return getWeight(Attack::_4);
}

// NON_MATCHING: same getWeight() tail difference as m41
f32 PriestBossActorNormalMode::m40() {
    if (sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0 &&
        sub_7100505BE4()->_40 <= *mSecondHalfLifePercent_s) {
        return 0.0f;
    }
    if (!(sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0)) {
        if (sub_7100505BE4()) {
            sub_7100505BE4();
            if (_e4 != 2 && u32(_e4 - 2) < 9) {
                if (u32(_130 - 4) < 5)
                    return 0.0f;
                if (!dmg::DamageInfoMgr::instance()->get4f8().sub_7100671ED8(mActor))
                    return 0.0f;
            }
        }
        const s32 buf_index = *mEquipWeaponBufIndex_a;
        if (buf_index == 1)
            return 0.0f;
        if (buf_index == -1) {
            if (auto* unit = sub_7100505BE4()) {
                if (!unit->sub_7100719B88(mActor))
                    return 0.0f;
            }
        }
    }
    return getWeight(Attack::_5);
}

// NON_MATCHING: the original evaluates the `std::pow` argument before loading `GlobalRandom::instance()`
f32 PriestBossActorNormalMode::m41() {
    if (sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0 &&
        sub_7100505BE4()->_40 <= *mSecondHalfLifePercent_s) {
        return 0.0f;
    }
    if (!(sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0)) {
        if (sub_7100505BE4()) {
            sub_7100505BE4();
            if (_e4 != 2 && u32(_e4 - 2) < 9) {
                if (_130 >= 4 && _130 <= 8)
                    return 0.0f;
                if (!dmg::DamageInfoMgr::instance()->get4f8().sub_7100671ED8(mActor))
                    return 0.0f;
            }
        }
        if (*mEquipWeaponBufIndex_a == 0)
            return 0.0f;
    }
    return getWeight(Attack::_6);
}

f32 PriestBossActorNormalMode::m42() {
    f32 weight = 0.0f;
    if (sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0 &&
        sub_7100505BE4()->_40 <= *mSecondHalfLifePercent_s) {
        weight = 0.5f;
    }
    return weight;
}

// NON_MATCHING: the original computes the squared distance before the radius (the loads of the 50.0f constant and the
// margin parameter come after the three distance multiplications); a named `dist_sq` local for the squared distance
// matches exactly (borderline, not applied).
f32 PriestBossActorNormalMode::m43() {
    f32 weight = 0.0f;
    if (sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0 &&
        sub_7100505BE4()->_40 <= *mSecondHalfLifePercent_s && _b4.value <= sead::Mathf::epsilon() &&
        !sub_7100505C74()) {
        const f32 dx = mActor->getMtx().getTranslation().x - sUnk_71025c8cf8.x;
        const f32 dz = mActor->getMtx().getTranslation().z - sUnk_71025c8cf8.z;
        const f32 radius = sUnk_7102450fa0 * *mStageMarginRateForEarthRelease_s;
        if (dx * dx + dz * dz < radius * radius) {
            if (sub_7100742588(nullptr, mActor->m45(), &sub_71005D9330(mActor), 10.0f))
                weight = 1.0f;
        }
    }
    return weight;
}

f32 PriestBossActorNormalMode::m44() {
    f32 weight = 0.0f;
    if (!(sub_7100505BE4() && sub_7100505BE4()->_3c == Unk_7102450fa8::Phase::_0) && _12c != 9 &&
        sub_7100505BE4() && _e4 == 2) {
        if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_3))
            weight = 1.0f;
    }
    return weight;
}

f32 PriestBossActorNormalMode::m45() {
    return 0.0f;
}

f32 PriestBossActorNormalMode::m46() {
    return 0.0f;
}

}  // namespace uking::ai
