#include "Game/AI/AI/aiHiddenOctarockNormal.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
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

}  // namespace uking::ai
