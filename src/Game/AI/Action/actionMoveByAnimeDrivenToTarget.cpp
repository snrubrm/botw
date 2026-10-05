#include "Game/AI/Action/actionMoveByAnimeDrivenToTarget.h"

namespace uking::action {

MoveByAnimeDrivenToTarget::MoveByAnimeDrivenToTarget(const InitArg& arg) : MoveByAnimeDriven(arg) {}

MoveByAnimeDrivenToTarget::~MoveByAnimeDrivenToTarget() = default;

bool MoveByAnimeDrivenToTarget::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void MoveByAnimeDrivenToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
    _68.sub_710000102C(0.0f);
}

bool MoveByAnimeDrivenToTarget::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!MoveByAnimeDriven::reenter_(other, true))
        return false;
    auto* action = sead::DynamicCast<MoveByAnimeDrivenToTarget>(other);
    if (!action)
        return false;
    _68.sub_710000103C(action->_68);
    return true;
}

void MoveByAnimeDrivenToTarget::leave_() {
    MoveByAnimeDriven::leave_();
}

void MoveByAnimeDrivenToTarget::loadParams_() {
    MoveByAnimeDriven::loadParams_();
    getStaticParam(&mAnimRotateMax_s, "AnimRotateMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MoveByAnimeDrivenToTarget::calc_() {
    MoveByAnimeDriven::calc_();
}

}  // namespace uking::action
