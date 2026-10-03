#include "Game/AI/AI/aiGuardianMiniReaction.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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
    auto* actor = mActor;
    if (actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(false);
        actor = mActor;
    }
    if (actor->getASList()) {
        if (actor->getASList()->x_1(0, 0) == "ChanceWaitShader")
            mActor->getASList()->sub_710115B140("WaitBattleShader", 0, 0, 1, 1);
    }
    _100.reset();
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

void GuardianMiniReaction::sub_7100420E7C() {
    auto* actor = mActor;
    if (actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
        actor = mActor;
    }
    actor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("チャンス", &params);
}

bool GuardianMiniReaction::m36(int damage_type) {
    if (isCurrentChild("チャンス") || isCurrentChild("ショック") || isCurrentChild("超ショック") ||
        isCurrentChild("左手ショック") || isCurrentChild("左手超ショック") ||
        isCurrentChild("後ろ手ショック") || isCurrentChild("後ろ手超ショック")) {
        changeChild("小ダメージ");
        return true;
    }
    return false;
}

void GuardianMiniReaction::m39(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::m39(params);
}

void GuardianMiniReaction::m40(ksys::act::ai::InlineParamPack* params) {
    if (*mGuardianMiniChanceTimeState_a == 1) {
        sub_71005D7014(mActor);
        sub_7100420E7C();
        *mGuardianMiniChanceTimeState_a = -1;
    } else {
        EnemyDefaultReaction::m40(params);
    }
}

void GuardianMiniReaction::m42(ksys::act::ai::InlineParamPack* params) {
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
    EnemyDefaultReaction::m42(params);
}

}  // namespace uking::ai
