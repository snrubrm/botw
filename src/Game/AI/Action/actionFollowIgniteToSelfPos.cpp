#include "Game/AI/Action/actionFollowIgniteToSelfPos.h"

namespace uking::action {

FollowIgniteToSelfPos::FollowIgniteToSelfPos(const InitArg& arg) : RotateTurnToTarget(arg) {}

FollowIgniteToSelfPos::~FollowIgniteToSelfPos() = default;

bool FollowIgniteToSelfPos::init_(sead::Heap* heap) {
    if (!RotateTurnToTarget::init_(heap))
        return false;
    return _78.init(heap);
}

void FollowIgniteToSelfPos::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
    _78.enter(params);
}

void FollowIgniteToSelfPos::leave_() {
    RotateTurnToTarget::leave_();
    _78.leave();
}

void FollowIgniteToSelfPos::loadParams_() {
    RotateTurnToTarget::loadParams_();
    _78.loadParams();
}

void FollowIgniteToSelfPos::calc_() {
    RotateTurnToTarget::calc_();
    _78.calc();
}

bool FollowIgniteToSelfPos::handleMessage_(const ksys::Message* message) {
    return _78.handleMessage(*message);
}

}  // namespace uking::action
