#include "Game/AI/AI/aiGuardianMiniFinalBattle.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMini.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniFinalBattle::GuardianMiniFinalBattle(const InitArg& arg) : EnemyBattle(arg) {}

GuardianMiniFinalBattle::~GuardianMiniFinalBattle() = default;

void GuardianMiniFinalBattle::sub_710041BA0C() {
    if (auto* as_list = mActor->getASList()) {
        as_list->startAnimationMaybe(-1.0f, -1.0f, "FlashShader", 0, 1, true);
        if (auto* mini = mActor->getParam()->getRes().mGParamList->getGuardianMini()) {
            if (mini->mColorType.ref())
                as_list->startAnimationMaybe(-1.0f, -1.0f, "FinalModeGrudgeColor", 0, 2, true);
            else
                as_list->startAnimationMaybe(-1.0f, -1.0f, "FinalModeColor", 0, 2, true);
        }
    }
}

void GuardianMiniFinalBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsPreAttackMove_s)
        changeToMoveBattleSign();
    else
        sub_710041B3D4();
}

bool GuardianMiniFinalBattle::isChangeable() const {
    return false;
}

void GuardianMiniFinalBattle::leave_() {
    sub_71005DA114(mActor, &_e0);
    sub_71005DA114(mActor, &_110);
    EnemyBattle::leave_();
}

void GuardianMiniFinalBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mAttackHitNum_s, "AttackHitNum");
    getStaticParam(&mIsPreAttackMove_s, "IsPreAttackMove");
    getStaticParam(&mRotNeckRate_s, "RotNeckRate");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

void GuardianMiniFinalBattle::changeToMoveBattleSign() {
    mActor->getHomePos(&_c8);
    _c8.y = mActor->getMtx().m[1][3];
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘予兆移動", &pack);
}

void GuardianMiniFinalBattle::sub_710041B978() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (!actor->getModel())
        return;
    if (!actor->getASList())
        return;
    actor->getASList()->sub_710115B01C(*mASSlotRight_s, 0, true);
    actor->getASList()->sub_710115B01C(*mASSlotLeft_s, 0, true);
    actor->getASList()->sub_710115B01C(*mASSlotBack_s, 0, true);
    actor->getASList()->sub_710115C11C();
    actor->getASList()->sub_710115BED4(true);
}

// Discarded call: `mActor->getDamageMgr();` before each setDamageCallbackTiming (present in the target asm).
void GuardianMiniFinalBattle::sub_710041B3D4() {
    sub_710041B978();
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 4, &_e0);
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 5, &_110);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘予兆開始", &pack);
}

void GuardianMiniFinalBattle::m38() {
    _d8 = true;
    sub_710041B978();
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 4, &_e0);
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 5, &_110);
    _d4 = 0;
    if (auto* parts = sub_71005DB0EC(mActor)) {
        parts->sub_7100D8A9D0(*mRotNeckRate_s);
        parts->sub_7100D8A9EC(*mRotNeckRate_s);
    }
    EnemyBattle::m38();
}

bool GuardianMiniFinalBattle::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000043)
        ++_d4;
    return false;
}

}  // namespace uking::ai

void Unk_71023f86d8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == -1)
        return;

    if (mOwner == nullptr)
        *a5 = 2;
    else if (mOwner->isCurrentChild("戦闘予兆点滅") || mOwner->isCurrentChild("戦闘攻撃"))
        *a5 = 1;
    else
        *a5 = 2;
}

void Unk_71023f8710::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 < 9 || *a4 > 11)
        return;

    *a2 = 0;
    if (mOwner == nullptr)
        *a5 = 2;
    else if (mOwner->isCurrentChild("戦闘予兆点滅") || mOwner->isCurrentChild("戦闘攻撃"))
        *a5 = 1;
    else
        *a5 = 2;
}
