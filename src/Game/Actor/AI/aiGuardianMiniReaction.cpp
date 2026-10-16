#include "Game/Actor/AI/aiGuardianMiniReaction.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

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

void sub_7100428358(ksys::act::Actor* actor, bool enabled, s32 slot);

// NON_MATCHING: stack slots of the child name temporaries in the second shock-name test.
void GuardianMiniReaction::calc_() {
    if (getCurrentChild()->isFinishedOrFailed() &&
        (isCurrentChild("弾かれ") || isCurrentChild("左手弾かれ"))) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_4);
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() &&
        (isCurrentChild("超ショック") || isCurrentChild("左手超ショック") ||
         isCurrentChild("後ろ手超ショック") || isCurrentChild("ショック") ||
         isCurrentChild("左手ショック") || isCurrentChild("後ろ手ショック"))) {
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("チャンス")) {
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("武器切替")) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
        setFinished();
        return;
    }

    if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("ガード")) {
        setRootAiFlag(ksys::act::ai::RootAiFlag::_1);
    } else {
        if (getCurrentChild()->isFinishedOrFailed() && isCurrentChild("ふっとび") &&
            *mGuardianMiniChanceTimeState_a == 2) {
            changeToDying();
            *mGuardianMiniChanceTimeState_a = -1;
            return;
        }
        if (*mIsChangeWeapon_s && !sub_71005D8B60(mActor) &&
            getCurrentChild()->isFinishedOrFailed() && isCurrentChild("ふっとび")) {
            auto* actor = mActor;
            if (actor && actor->getModel() && actor->getASList()) {
                actor->getASList()->sub_710115C11C();
                actor->getASList()->sub_710115BED4(true);
            }
            changeChild("武器切替");
            return;
        }
    }

    if (_fc >= 0 && (isCurrentChild("超ショック") || isCurrentChild("左手超ショック") ||
                     isCurrentChild("後ろ手超ショック"))) {
        auto* as_list = mActor->getASList();
        if (as_list && as_list->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_7100428358(mActor, false, _fc);
            if (_100.hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&_100, &accessor);
                sead::Vector3f dir;
                accessor.getActorMtx().getBase(dir, 0);
                getCurrentChild()->setDynamicParam(dir, "DropDir");
            }
        }
    }

    if (isCurrentChild("チャンス"))
        getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");

    EnemyDefaultReaction::calc_();
}

void GuardianMiniReaction::changeToChance() {
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

void GuardianMiniReaction::changeToDying() {
    auto* actor = mActor;
    if (actor->getModel() && actor->getASList()) {
        actor->getASList()->sub_710115C11C();
        actor->getASList()->sub_710115BED4(true);
        actor = mActor;
    }
    actor->getASList()->sub_710115B140("ChanceWaitShader", 0, 0, 1, 1);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("瀕死", &params);
}

void GuardianMiniReaction::m40(ksys::act::ai::InlineParamPack* params) {
    if (*mGuardianMiniChanceTimeState_a == 1) {
        sub_71005D7014(mActor);
        changeToChance();
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
