#include "Game/Actor/Action/actionHorseRideShoot.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Camera/CameraMgr.h"

namespace uking::action {

HorseRideShoot::HorseRideShoot(const InitArg& arg) : HorseRideBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
HorseRideShoot::~HorseRideShoot() {
    ;
}

bool HorseRideShoot::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
    sub_71001AD8A0(mASName_s.cstr(), true);
    sub_71001ADAA0(*mTargetPos_d);
    _78 = false;
}

void HorseRideShoot::leave_() {
    sub_71005DB3B8(mActor);
    sub_71001ADAA8();
    HorseRideBase::leave_();
}

void HorseRideShoot::loadParams_() {
    HorseRideBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseRideShoot::calc_() {
    if (sub_71005DD734(mActor, 44, nullptr, 0, 0))
        sub_71005DB3B8(mActor);
    else if (sub_71005DD5B0(mActor, 44, nullptr, 0, 0))
        sub_71001ADAA8();

    if (sub_71005DD798(mActor, 44, nullptr, 0, 0))
        sub_71005DB110(mActor, *mTargetPos_d);
    else
        sub_71001ADAA0(*mTargetPos_d);

    HorseRideBase::calc_();

    if (sub_71005DD780(mActor, 71, nullptr, 0, 0)) {
        sead::Vector3f target;
        sub_71001B0E38(&target);
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->sub_7100016494();
        sub_71005D80FC(mActor, *mWeaponIdx_s, target, 0, 1.0f, nullptr, nullptr);
        _78 = true;
    } else if (!_78) {
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
    }

    if (sub_71001ADA78())
        setFinished();
}

// NON_MATCHING: the original normalizes with fcsel after loading the params and the position (branch here).
void HorseRideShoot::sub_71001B0E38(sead::Vector3f* out) {
    if (!out)
        return;

    sead::Vector3f dir = *mTargetPos_d - mActor->getMtx().getTranslation();
    const f32 dist = dir.length();
    const f32 inv = 1.0f / dist;
    f32 min = *mOffsetRangeMin_s;
    f32 max = *mOffsetRangeMax_s;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (dist > 0.0f)
        dir *= inv;
    const sead::Vector3f side = dir.cross(sead::Vector3f::ey);

    if (ksys::sub_7100D8C4F8(pos)) {
        const f32 rate = dist * *mOffsetRateByDist_s;
        min *= rate;
        max *= rate;
    } else {
        min = *mOffsetRangeMinOutOfScreen_s;
        max = *mOffsetRangeMaxOutOfScreen_s;
    }

    const f32 offset = sead::GlobalRandom::instance()->getF32Range(min, max);
    const f32 sign = f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1);
    *out = *mTargetPos_d + side * (sign * offset);
}

}  // namespace uking::action
