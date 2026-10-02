#include "Game/AI/AI/aiGuardianMiniReaction.h"

namespace uking::ai {

GuardianMiniReaction::GuardianMiniReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GuardianMiniReaction::~GuardianMiniReaction() = default;

bool GuardianMiniReaction::init_(sead::Heap* heap) {
    _fa = false;
    _f8 = false;
    _f9 = false;
    return true;
}

void GuardianMiniReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _fc = -1;
    _100.reset();
    EnemyDefaultReaction::enter_(params);
}

void GuardianMiniReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void GuardianMiniReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mPreAttackASRight_s, "PreAttackASRight");
    getStaticParam(&mPreAttackASLeft_s, "PreAttackASLeft");
    getStaticParam(&mJustGuardNumForBreak_s, "JustGuardNumForBreak");
    getStaticParam(&mIsChangeWeapon_s, "IsChangeWeapon");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

void GuardianMiniReaction::m39(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m39(params);
}

}  // namespace uking::ai
