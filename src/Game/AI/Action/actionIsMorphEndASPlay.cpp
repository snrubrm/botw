#include "Game/AI/Action/actionIsMorphEndASPlay.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

IsMorphEndASPlay::IsMorphEndASPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IsMorphEndASPlay::~IsMorphEndASPlay() = default;

bool IsMorphEndASPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IsMorphEndASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IsMorphEndASPlay::leave_() {
    OnetimeStopASPlay::leave_();
    if (auto* as_list = mActor->getASList())
        as_list->sub_710115CD0C();
}

void IsMorphEndASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void IsMorphEndASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

bool IsMorphEndASPlay::isFinished() const {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return false;
    return as_list->mSlots[0]._8._c >= 1.0f || ksys::act::ai::Action::isFinished() ||
           isFinishedAS(0, 0);
}

}  // namespace uking::action
