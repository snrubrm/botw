#include "Game/AI/Action/actionGrabAndShoot.h"

namespace uking::action {

GrabAndShoot::GrabAndShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GrabAndShoot::~GrabAndShoot() = default;

void GrabAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GrabAndShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void GrabAndShoot::loadParams_() {
    getStaticParam(&mParams.mGrabIdx_s, "GrabIdx");
    getStaticParam(&mParams.mShootSpeed_s, "ShootSpeed");
    getStaticParam(&mParams.mShootAng_s, "ShootAng");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mBlurMax_s, "BlurMax");
}

void GrabAndShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GrabAndShoot::isChangeable() const {
    return false;
}

}  // namespace uking::action
