#include "Game/AI/Action/actionOnetimeMoveASPlay.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

OnetimeMoveASPlay::OnetimeMoveASPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeMoveASPlay::~OnetimeMoveASPlay() = default;

void OnetimeMoveASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    _50.value = 0;
    _50.prev_value = 0;
    mActor->getMtx().getBase(_5c, 2);
    if (*mIsChangable_s)
        mFlags.set(Flag::Changeable);
}

void OnetimeMoveASPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void OnetimeMoveASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIsChangable_s, "IsChangable");
}

void OnetimeMoveASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
