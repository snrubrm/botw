#include "Game/AI/Action/actionNoCountDead.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NoCountDead::NoCountDead(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NoCountDead::~NoCountDead() = default;

bool NoCountDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NoCountDead::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsFadeout_s)
        mActor->deleteEx(ksys::act::Actor::DeleteType::_5, ksys::act::BaseProc::DeleteReason::_0);
    else
        mActor->deleteAndEmit(2);
}

void NoCountDead::leave_() {
    ksys::act::ai::Action::leave_();
}

void NoCountDead::loadParams_() {
    getStaticParam(&mIsFadeout_s, "IsFadeout");
}

void NoCountDead::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
