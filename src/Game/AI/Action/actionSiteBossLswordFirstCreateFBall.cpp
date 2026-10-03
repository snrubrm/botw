#include "Game/AI/Action/actionSiteBossLswordFirstCreateFBall.h"

namespace uking::action {

SiteBossLswordFirstCreateFBall::SiteBossLswordFirstCreateFBall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordFirstCreateFBall::~SiteBossLswordFirstCreateFBall() = default;

bool SiteBossLswordFirstCreateFBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordFirstCreateFBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordFirstCreateFBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordFirstCreateFBall::loadParams_() {
    getStaticParam(&mParams.mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mParams.mAttackPower_s, "AttackPower");
    getStaticParam(&mParams.mCreateNum_s, "CreateNum");
    getStaticParam(&mParams.mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mParams.mFireBallScale_s, "FireBallScale");
    getStaticParam(&mParams.mThrowActorName_s, "ThrowActorName");
    getStaticParam(&mParams.mASName_s, "ASName");
    getStaticParam(&mParams.mBindPosOffset_s, "BindPosOffset");
}

void SiteBossLswordFirstCreateFBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
