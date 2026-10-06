#include "Game/AI/Action/actionForkInWaterDropWeaponWithSpeed.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkInWaterDropWeaponWithSpeed::ForkInWaterDropWeaponWithSpeed(const InitArg& arg)
    : ForkDropWeapon(arg) {}

ForkInWaterDropWeaponWithSpeed::~ForkInWaterDropWeaponWithSpeed() = default;

bool ForkInWaterDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeapon::init_(heap);
}

void ForkInWaterDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeapon::enter_(params);
    _58 = false;
}

void ForkInWaterDropWeaponWithSpeed::leave_() {
    ForkDropWeapon::leave_();
}

void ForkInWaterDropWeaponWithSpeed::loadParams_() {
    ForkDropWeapon::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutWaterDepth_s, "OutWaterDepth");
}

void ForkInWaterDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
    f32 depth = 0.0f;
    if (mActor->get68f()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    if (depth > *mInWaterDepth_s) {
        if (!_58)
            sub_710014CE28();
        _58 = true;
    } else if (depth <= *mOutWaterDepth_s) {
        _58 = false;
    }
}

}  // namespace uking::action
