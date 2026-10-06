#include "Game/AI/Action/actionFlyingCharacterDamageBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FlyingCharacterDamageBase::FlyingCharacterDamageBase(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
FlyingCharacterDamageBase::~FlyingCharacterDamageBase() {
    ;
}

bool FlyingCharacterDamageBase::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterDamageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir = sead::Vector3f::ez;
        auto* mgr = sub_710072BA90(mActor);
        sub_71005E2318(&dir, mActor, mgr);
        sub_7100130868(controller, dir);
    }
}

void FlyingCharacterDamageBase::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterDamageBase::loadParams_() {
    FlyingCharacterReaction::loadParams_();
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mLastSpeedRatio_s, "LastSpeedRatio");
    getStaticParam(&mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mIsCheckFallASFinished_s, "IsCheckFallASFinished");
    getStaticParam(&mIsIgnoreSameAS4Fall_s, "IsIgnoreSameAS4Fall");
    getStaticParam(&mIsIgnoreSameAS4OnGround_s, "IsIgnoreSameAS4OnGround");
    getStaticParam(&mFallAS_s, "FallAS");
    getStaticParam(&mOnGroundAS_s, "OnGroundAS");
}

void FlyingCharacterDamageBase::calc_() {
    FlyingCharacterReaction::calc_();
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive))
        return;
    auto* mgr = sub_710072BA90(mActor);
    if (!mgr)
        return;
    if (!sub_7100732AD0(mgr->getField54()))
        return;
    sead::Vector3f dir;
    if (!mgr->getAttackPos(&dir))
        return;
    sub_71005E2318(&dir, mActor, mgr);
    sub_7100130868(controller, dir);
}

void FlyingCharacterDamageBase::m33() {
    if (!mFallAS_s.isEmpty())
        playAS(mFallAS_s.cstr(), *mIsIgnoreSameAS4Fall_s, 0, 0, -1.0f);
}

void FlyingCharacterDamageBase::m34(ksys::phys::CharacterController* controller) {
    if (*mIsCheckFallASFinished_s && isFinishedAS(0, 0)) {
        setFinished();
        return;
    }
    FlyingCharacterReaction::m34(controller);
}

void FlyingCharacterDamageBase::m36() {
    if (!mOnGroundAS_s.isEmpty())
        playAS(mOnGroundAS_s.cstr(), *mIsIgnoreSameAS4OnGround_s, 0, 0, -1.0f);
}

void FlyingCharacterDamageBase::m37(ksys::phys::CharacterController* controller) {
    if (isFinishedAS(0, 0))
        setFinished();

    if (*mIsControlRotation_s) {
        sub_710073FA94(&_40, mActor);
        sead::Vector3f normal;
        if (controller->sub_7100F5F234(&normal)) {
            sub_7100740118(&_40, normal, 0.8f, 2 * sead::Mathf::pi(), 0.0f);
        } else {
            const sead::Vector3f dir = -controller->get7c();
            sub_7100740118(&_40, dir, 0.8f, 2 * sead::Mathf::pi(), 0.0f);
        }
        sub_7100740E04(_40, controller);
    } else {
        sub_7100738660(controller, *mRotReduceRatioOnGround_s);
    }
    sub_7100737C0C(controller, *mPosReduceRatioOnGround_s, -sead::Vector3f::ey);
    FlyingCharacterReaction::m37(controller);
}

// NON_MATCHING: the original keeps three separate branches (one sub_7100736B68 call each) where ours selects
// the parameter address with csel.
f32 FlyingCharacterDamageBase::sub_7100130AA4() {
    auto* manager = sub_710072BA90(mActor);
    if (!manager)
        return *mHitImpactForceSmallSwordS_s;
    const s32 kind = manager->getField54();
    const s32 size = manager->getField50();
    const f32* const* param;
    if (size == 1) {
        param = sub_7100736B68(kind) ? &mHitImpactForceSpearL_s : &mHitImpactForceSpearS_s;
    } else if (size != 2) {
        param = sub_7100736B68(kind) ? &mHitImpactForceSmallSwordL_s : &mHitImpactForceSmallSwordS_s;
    } else {
        param = sub_7100736B68(kind) ? &mHitImpactForceSpearL_s : &mHitImpactForceSpearS_s;
    }
    return **param * manager->sub_71006D8DE8();
}

}  // namespace uking::action
