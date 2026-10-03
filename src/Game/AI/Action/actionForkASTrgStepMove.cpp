#include "Game/AI/Action/actionForkASTrgStepMove.h"

namespace uking::action {

ForkASTrgStepMove::ForkASTrgStepMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgStepMove::~ForkASTrgStepMove() = default;

bool ForkASTrgStepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgStepMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgStepMove::loadParams_() {
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mCloseDist_s, "CloseDist");
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinishDist_s, "FinishDist");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void ForkASTrgStepMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
