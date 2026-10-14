#include "Game/Actor/Action/actionFollowIgniteToSelfPos.h"

namespace uking::action {

FollowIgniteToSelfPos::FollowIgniteToSelfPos(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

FollowIgniteToSelfPos::~FollowIgniteToSelfPos() = default;

bool FollowIgniteToSelfPos::init_(sead::Heap* heap) {
    if (!ASPlayRotateTurnToTarget::init_(heap))
        return false;
    return _78.init(heap);
}

void FollowIgniteToSelfPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
    _78.enter(params);
}

void FollowIgniteToSelfPos::leave_() {
    ASPlayRotateTurnToTarget::leave_();
    _78.leave();
}

void FollowIgniteToSelfPos::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    _78.loadParams();
}

void FollowIgniteToSelfPos::calc_() {
    ASPlayRotateTurnToTarget::calc_();
    _78.calc();
}

bool FollowIgniteToSelfPos::handleMessage_(const ksys::Message* message) {
    return _78.handleMessage(*message);
}

}  // namespace uking::action
