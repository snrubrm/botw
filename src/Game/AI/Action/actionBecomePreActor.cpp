#include "Game/AI/Action/actionBecomePreActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BecomePreActor::BecomePreActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BecomePreActor::~BecomePreActor() = default;

bool BecomePreActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BecomePreActor::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->becomePreActor(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
}

void BecomePreActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void BecomePreActor::loadParams_() {}

void BecomePreActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
