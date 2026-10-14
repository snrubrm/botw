#include "Game/Actor/Action/actionArrowChargeAndShoot.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

ArrowChargeAndShoot::ArrowChargeAndShoot(const InitArg& arg) : ShootArrow(arg) {}

ArrowChargeAndShoot::~ArrowChargeAndShoot() = default;

bool ArrowChargeAndShoot::init_(sead::Heap* heap) {
    return ShootArrow::init_(heap);
}

void ArrowChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootArrow::enter_(params);
}

void ArrowChargeAndShoot::leave_() {
    if (sub_71005D8514(mActor, *mWeaponIdx_s))
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void ArrowChargeAndShoot::loadParams_() {
    ShootArrow::loadParams_();
}

void ArrowChargeAndShoot::calc_() {
    ShootArrow::calc_();
    if (sub_71005DD780(mActor, 55, nullptr, 0, 0))
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

}  // namespace uking::action
