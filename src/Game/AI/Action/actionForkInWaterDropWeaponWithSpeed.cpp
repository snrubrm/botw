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

// NON_MATCHING: the original loads the Y translation before get6f0() (ReflectThrown::isFinished matches with a once-used
// `const f32 y = mActor->getMtx().m[1][3];` local; not applied here)
void ForkInWaterDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
    f32 depth;
    if (mActor->get68f())
        depth = mActor->get6f0() - mActor->getMtx().m[1][3];
    else
        depth = 0.0f;
    if (depth > *mInWaterDepth_s) {
        if (!_58)
            sub_710014CE28();
        _58 = true;
    } else if (depth <= *mOutWaterDepth_s) {
        _58 = false;
    }
}

}  // namespace uking::action
