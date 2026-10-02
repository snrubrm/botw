#include "Game/AI/Action/actionForkDisableContactOnAtHitPlayer.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkDisableContactOnAtHitPlayer::ForkDisableContactOnAtHitPlayer(const InitArg& arg)
    : ForkDisableContact(arg) {}

ForkDisableContactOnAtHitPlayer::~ForkDisableContactOnAtHitPlayer() = default;

bool ForkDisableContactOnAtHitPlayer::init_(sead::Heap* heap) {
    return ForkDisableContact::init_(heap);
}

void ForkDisableContactOnAtHitPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
}

void ForkDisableContactOnAtHitPlayer::leave_() {
    ForkDisableContact::leave_();
}

void ForkDisableContactOnAtHitPlayer::loadParams_() {
    ForkDisableContact::loadParams_();
}

void ForkDisableContactOnAtHitPlayer::calc_() {
    ForkDisableContact::calc_();
}

bool ForkDisableContactOnAtHitPlayer::m33() {
    return sub_71005DD7B0(mActor, nullptr, 0, 0);
}

}  // namespace uking::action
