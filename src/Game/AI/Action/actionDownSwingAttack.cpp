#include "Game/AI/Action/actionDownSwingAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DownSwingAttack::DownSwingAttack(const InitArg& arg) : ActionEx(arg) {}

DownSwingAttack::~DownSwingAttack() = default;

void DownSwingAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void DownSwingAttack::leave_() {
    sub_71005DA114(mActor, &_80);
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    if (auto* spine = mActor->sub_71011D8A10()) {
        spine->_8c &= 0xffcf;
        spine->_d4 &= ~0x40;
    }
}

void DownSwingAttack::loadParams_() {
    if (!mActor->getParam())
        return;
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mParams.mJustAvoidCheckLength_s, "JustAvoidCheckLength");
    getStaticParam(&mParams.mJustAvoidCheckAngle_s, "JustAvoidCheckAngle");
    getStaticParam(&mParams.mLoopTime_s, "LoopTime");
    getStaticParam(&mParams.mLoopTimeRand_s, "LoopTimeRand");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mIsSpecialAttack_s, "IsSpecialAttack");
    getStaticParam(&mParams.mSpecialAttackRadius_s, "SpecialAttackRadius");
    getStaticParam(&mParams.mSpineControlOffsetY_s, "SpineControlOffsetY");
}

void DownSwingAttack::calc_() {
    ActionEx::calc_();
}

bool DownSwingAttack::isChangeable() const {
    return false;
}

}  // namespace uking::action
