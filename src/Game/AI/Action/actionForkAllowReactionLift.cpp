#include "Game/AI/Action/actionForkAllowReactionLift.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ForkAllowReactionLift::ForkAllowReactionLift(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAllowReactionLift::~ForkAllowReactionLift() = default;

bool ForkAllowReactionLift::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAllowReactionLift::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    *mIsAllowReactionLift_a = true;
    if (ksys::act::isAttClientEnabled(mActor, "Grab")) {
        _28 = true;
    } else {
        _28 = false;
        ksys::act::enableAttClient(mActor, "Grab");
    }
}

void ForkAllowReactionLift::leave_() {
    *mIsAllowReactionLift_a = false;
    if (!_28)
        ksys::act::disableAttClient(mActor, "Grab");
}

void ForkAllowReactionLift::loadParams_() {
    getAITreeVariable(&mIsAllowReactionLift_a, "IsAllowReactionLift");
}

void ForkAllowReactionLift::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
