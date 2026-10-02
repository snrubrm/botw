#include "Game/AI/Action/actionBackStepAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

BackStepAttack::BackStepAttack(const InitArg& arg) : BackStepBase(arg) {}

BackStepAttack::~BackStepAttack() = default;

void BackStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    BackStepBase::enter_(params);
    _138 = -1;
    setDamageCallbackTiming(mActor, 4, &_d8);
}

void BackStepAttack::leave_() {
    BackStepBase::leave_();
    sub_71005DA114(mActor, &_d8);
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
}

void BackStepAttack::loadParams_() {
    BackStepBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
}

void BackStepAttack::calc_() {
    BackStepBase::calc_();
}

void BackStepAttack::m34() {
    playAS("BackStepStart", false, 0, 0, -1.0f);
}

void BackStepAttack::m35() {
    playAS("BackStep", false, 0, 0, -1.0f);
}

void BackStepAttack::m36() {
    playAS("BackStepPreLand", false, 0, 0, -1.0f);
}

void BackStepAttack::m37() {
    playAS("AttackStep", false, 0, 0, -1.0f);
}

}  // namespace uking::action
