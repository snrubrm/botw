#include "Game/AI/AI/aiArrowChargeAndShoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

ArrowChargeAndShoot::ArrowChargeAndShoot(const InitArg& arg) : SeqTwoAction(arg) {}

ArrowChargeAndShoot::~ArrowChargeAndShoot() = default;

bool ArrowChargeAndShoot::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void ArrowChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void ArrowChargeAndShoot::calc_() {
    SeqTwoAction::calc_();
}

void ArrowChargeAndShoot::leave_() {
    if (sub_71005D8514(mActor, *mWeaponIdx_s))
        sub_71005D787C(mActor, *mWeaponIdx_s, uking::act::Unk_71002eda38(5));
}

void ArrowChargeAndShoot::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
