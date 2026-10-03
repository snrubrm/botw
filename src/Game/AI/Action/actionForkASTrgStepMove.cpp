#include "Game/AI/Action/actionForkASTrgStepMove.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASTrgStepMove::ForkASTrgStepMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgStepMove::~ForkASTrgStepMove() = default;

bool ForkASTrgStepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _84 = mActor->getVelocity();
    _84.y = 0;
    const f32 speed = _84.normalize();
    _50.value = speed;
    _50.prev_value = speed;
    _5c = -1.0f;
    sub_710073FA90(&_60, mActor);
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
