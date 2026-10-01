#include "Game/AI/Action/actionForkSimpleGrabBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkSimpleGrabBase::ForkSimpleGrabBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSimpleGrabBase::~ForkSimpleGrabBase() = default;

bool ForkSimpleGrabBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSimpleGrabBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = false;
}

void ForkSimpleGrabBase::leave_() {
    if (!_30)
        mActor->resetConnectedCalcChild(true);
}

void ForkSimpleGrabBase::loadParams_() {
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mIsNoGrabSuccess_s, "IsNoGrabSuccess");
}

void ForkSimpleGrabBase::calc_() {
    ksys::act::ai::Action::calc_();
}

int ForkSimpleGrabBase::m32() {
    return 0;
}

}  // namespace uking::action
