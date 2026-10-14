#include "Game/Actor/Action/actionFollowAttack.h"

namespace uking::action {

FollowAttack::FollowAttack(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

FollowAttack::~FollowAttack() = default;

bool FollowAttack::init_(sead::Heap* heap) {
    if (!ASPlayRotateTurnToTarget::init_(heap))
        return false;
    _78.init(heap);
    return true;
}

void FollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
    m35();
    _78._89 = *mIsRodDirHosei_s;
    _78.enter(params);
}

void FollowAttack::leave_() {
    ASPlayRotateTurnToTarget::leave_();
    _78.leave();
}

void FollowAttack::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    _78.loadParams();
    getStaticParam(&mForceKillMode_s, "ForceKillMode");
    getStaticParam(&mIsRodDirHosei_s, "IsRodDirHosei");
}

void FollowAttack::calc_() {
    ASPlayRotateTurnToTarget::calc_();
    _78.calc();
}

void FollowAttack::m35() {
    _78._58 = *mForceKillMode_s ? 0x40000001 : 1;
}

}  // namespace uking::action
