#include "Game/AI/Action/actionElectricAttack.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <algorithm>

namespace uking::action {

ElectricAttack::ElectricAttack(const InitArg& arg) : TimeredASPlay(arg) {}

ElectricAttack::~ElectricAttack() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(sead::SafeString(mElectricActorKey_s.cstr()));
}

bool ElectricAttack::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap) && sub_7100103040(heap);
}

void ElectricAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
    const f32 max_keep_time = static_cast<f32>(std::max(*mMaxKeepTimer_s, 1));
    _a4 = ksys::Timer(max_keep_time, max_keep_time);
    const f32 hit_after_time = static_cast<f32>(*mHitAfterTime_s);
    _b0 = ksys::Timer(hit_after_time, hit_after_time);
    _bc = false;
    sub_71001034E0();
}

void ElectricAttack::leave_() {
    sub_7100103830();
    TimeredASPlay::leave_();
}

void ElectricAttack::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mHitAfterTime_s, "HitAfterTime");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricAttack::calc_() {
    TimeredASPlay::calc_();
    if (sub_7100103684()) {
        if (!_bc)
            _bc = true;
        _b0.update();
    } else if (_bc) {
        _b0.update();
    }
    _a4.update();
    if (_a4.value <= sead::Mathf::epsilon() || _b0.value <= sead::Mathf::epsilon()) {
        sub_7100103830();
        setFinished();
    }
}

}  // namespace uking::action
