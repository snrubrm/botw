#include "Game/AI/AI/aiWillBallFollowAttackWithDynAng.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WillBallFollowAttackWithDynAng::WillBallFollowAttackWithDynAng(const InitArg& arg)
    : WillBallFollowAttack(arg) {}

WillBallFollowAttackWithDynAng::~WillBallFollowAttackWithDynAng() = default;

bool WillBallFollowAttackWithDynAng::init_(sead::Heap* heap) {
    return WillBallFollowAttack::init_(heap);
}

void WillBallFollowAttackWithDynAng::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallFollowAttack::enter_(params);
}

void WillBallFollowAttackWithDynAng::calc_() {
    WillBallFollowAttack::calc_();
}

void WillBallFollowAttackWithDynAng::leave_() {
    WillBallFollowAttack::leave_();
}

void WillBallFollowAttackWithDynAng::loadParams_() {
    WillBallFollowAttack::loadParams_();
    getDynamicParam(&mAngle_d, "Angle");
}

void WillBallFollowAttackWithDynAng::m34(ksys::act::ai::InlineParamPack* params) {
    params->addVec3(*mAngle_d, "Angle", -1);
}

}  // namespace uking::ai
