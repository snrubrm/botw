#include "Game/AI/Action/actionForkAnimDriveFreeMoving.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

ForkAnimDriveFreeMoving::ForkAnimDriveFreeMoving(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimDriveFreeMoving::~ForkAnimDriveFreeMoving() = default;

bool ForkAnimDriveFreeMoving::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimDriveFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAnimDriveFreeMoving::leave_() {
    if (_30) {
        _30 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void ForkAnimDriveFreeMoving::loadParams_() {}

void ForkAnimDriveFreeMoving::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
