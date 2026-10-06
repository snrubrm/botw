#include "Game/AI/AI/aiHiddenOctarockNormal.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

HiddenOctarockNormal::HiddenOctarockNormal(const InitArg& arg) : EnemyNormal(arg) {}

HiddenOctarockNormal::~HiddenOctarockNormal() = default;

bool HiddenOctarockNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void HiddenOctarockNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
    _410 = false;
    const s32 delay = *mOptionHitReactionDelay_s;
    _418 = delay;
    _41c = delay;
    _414 = delay;
    if (!*mIsHitGround_s) {
        if (auto* controller = mActor->getCharacterController()) {
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        }
    }
    sead::DynamicCast<uking::act::Enemy>(mActor);
}

void HiddenOctarockNormal::leave_() {
    auto* controller = mActor->getCharacterController();
    if (controller && *mIsHitGround_s)
        controller->sub_7100F60604();
    if (!*mIsHitGround_s) {
        if (auto* controller2 = mActor->getCharacterController())
            controller2->sub_7100F60604();
    }
    sead::DynamicCast<uking::act::Enemy>(mActor);
    EnemyNormal::leave_();
}

void HiddenOctarockNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mOptionHitReactionDelay_s, "OptionHitReactionDelay");
    getStaticParam(&mIsSitDown_s, "IsSitDown");
    getStaticParam(&mIsHitGround_s, "IsHitGround");
    getStaticParam(&mIsReactionByWigHit_s, "IsReactionByWigHit");
    getStaticParam(&mIsHide_s, "IsHide");
    getStaticParam(&mIsIvalidateSight_s, "IsIvalidateSight");
    getStaticParam(&mIsSealHearing_s, "IsSealHearing");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
}

bool HiddenOctarockNormal::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() && !isCurrentChild("攻撃反応");
}

s32 HiddenOctarockNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 2};
    return sTable[idx];
}

void HiddenOctarockNormal::m37() {
    EnemyNormal::m37();
    if (*mIsIvalidateSight_s) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7EAE4(0);
    }
}

void HiddenOctarockNormal::m49(Unk1* out, s32 idx) {
    if (isCurrentChild("カツラ反応") || isCurrentChild("攻撃反応") ||
        (m52(idx) == 2 && *mIsSealHearing_s)) {
        out->_0 = -1;
        return;
    }
    EnemyNormal::m49(out, idx);
}

ksys::act::Unk_7100d78e50* HiddenOctarockNormal::m47(ksys::act::AwarenessInstance* awareness,
                                                     ksys::act::Unk_71024dccf8* filter, s32 a3) {
    auto* entry = EnemyNormal::m47(awareness, filter, a3);
    if (entry && entry->_a0 != 0)
        return entry;

    filter->_8 = -1;
    while (awareness->_260[3]) {
        entry = ksys::act::sub_7100D7EEE8(&awareness->_260[3]->_8, filter);
        if (!entry)
            return nullptr;
        if (m46(entry->_88, entry->_0.mLink))
            return entry;
    }
    return nullptr;
}

void HiddenOctarockNormal::m60(Unk3* out) {
    if (!isCurrentChild("攻撃反応") || !sub_71005D9050(mActor))
        out->_0 = -1;
}

void HiddenOctarockNormal::m61(Unk3* out) {
    if (isCurrentChild("プレイヤー発見") && sub_710039DB34(true)) {
        auto* target = sub_71005D9050(mActor);
        if (target && ksys::act::isPlayerProfile(target))
            out->_4 |= 2;
        out->_0 = 2;
    }
}

void HiddenOctarockNormal::m69(Unk2* target) {
    EnemyNormal::m69(target);
    _410 = false;
    if (*mIsIvalidateSight_s) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7E9BC(0);
    }
    sub_71005D8E9C(mActor);
}

void HiddenOctarockNormal::m34() {
    if (*mIsHide_s && (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
                       testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
                       testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4))) {
        _3ac.reset(8);
        if (*mIsSitDown_s)
            sub_7100432294();
        changeChild("隠れる");
        return;
    }
    if (*mIsSitDown_s)
        sub_7100432294();
    EnemyNormal::m34();
}

// NON_MATCHING: only the placement of `add x21, sp, #0x18` (the pack address kept for the destructor loop), which the
// original emits after sub_71005D8E9C instead of before addVec3.
void HiddenOctarockNormal::changeToWigReaction() {
    s32 delay = _418;
    _410 = false;
    if (_41c != _418)
        delay = sead::GlobalRandom::instance()->getS32Range(_418, _41c);
    _414 = delay;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D8F28(mActor) ? sub_71005D9330(mActor) : getPlayerPosition(), "TargetPos", -1);
    sub_71005D8E9C(mActor);
    changeChild("カツラ反応", &pack);
    if (*mIsIvalidateSight_s) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7E9BC(0);
    }
}

void HiddenOctarockNormal::sub_7100432294() {
    auto* controller = mActor->getCharacterController();
    if (!controller || !*mIsHitGround_s)
        return;
    controller->sub_7100F605F0();
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityTree);
}

}  // namespace uking::ai
