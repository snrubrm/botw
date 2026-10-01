#include "Game/AI/Action/actionFollowAttack.h"

namespace uking::action {

FollowAttack::FollowAttack(const InitArg& arg) : RotateTurnToTarget(arg) {}

FollowAttack::~FollowAttack() = default;

bool FollowAttack::init_(sead::Heap* heap) {
    if (!RotateTurnToTarget::init_(heap))
        return false;
    _78.init(heap);
    return true;
}

void FollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
    m35();
    _78._89 = *mIsRodDirHosei_s;
    _78.enter(params);
}

void FollowAttack::leave_() {
    RotateTurnToTarget::leave_();
    _78.leave();
}

void FollowAttack::loadParams_() {
    RotateTurnToTarget::loadParams_();
    _78.loadParams();
    getStaticParam(&mForceKillMode_s, "ForceKillMode");
    getStaticParam(&mIsRodDirHosei_s, "IsRodDirHosei");
}

void FollowAttack::calc_() {
    RotateTurnToTarget::calc_();
    _78.calc();
}

void FollowAttack::m35() {
    _78._58 = *mForceKillMode_s ? 0x40000001 : 1;
}

}  // namespace uking::action
