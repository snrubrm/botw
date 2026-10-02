#include "Game/AI/Action/actionAnimMatrixDriven.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

AnimMatrixDriven::AnimMatrixDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimMatrixDriven::~AnimMatrixDriven() = default;

bool AnimMatrixDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimMatrixDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimMatrixDriven::leave_() {
    if (_58) {
        _58 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void AnimMatrixDriven::loadParams_() {
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mStartFrame_d, "StartFrame");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
}

void AnimMatrixDriven::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
