#include "Game/AI/Action/actionChargeAndShoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

ChargeAndShoot::ChargeAndShoot(const InitArg& arg) : ShootArrow(arg) {}

ChargeAndShoot::~ChargeAndShoot() = default;

bool ChargeAndShoot::init_(sead::Heap* heap) {
    return ShootArrow::init_(heap);
}

void ChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootArrow::enter_(params);
}

void ChargeAndShoot::leave_() {
    if (sub_71005D8514(mActor, *mWeaponIdx_s))
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void ChargeAndShoot::loadParams_() {
    ShootArrow::loadParams_();
}

void ChargeAndShoot::calc_() {
    ShootArrow::calc_();
    if (sub_71005DD780(mActor, 55, nullptr, 0, 0))
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
}

}  // namespace uking::action
