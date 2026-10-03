#include "Game/AI/Action/actionLargeAttack.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
LargeAttack::LargeAttack(const InitArg& arg) : ActionEx(arg) {}

LargeAttack::~LargeAttack() = default;

void LargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_8c, mActor);
    _b0 = 0;
    playAS("LargeAttack", false, 0, 0, -1.0f);
    setDamageCallbackTiming(mActor, 4, &_58);
}

void LargeAttack::leave_() {
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    ksys::act::disableAttClient(mActor, "Counter");
    sub_71005DA114(mActor, &_58);
}

void LargeAttack::loadParams_() {
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mAttackRatio_s, "AttackRatio");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mParams.mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mParams.mJustAvoidAngle_s, "JustAvoidAngle");
}

void LargeAttack::calc_() {
    ActionEx::calc_();
}

bool LargeAttack::isChangeable() const {
    return false;
}

}  // namespace uking::action
