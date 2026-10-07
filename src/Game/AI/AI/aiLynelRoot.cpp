#include "Game/AI/AI/aiLynelRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/AI/aiUnk_PartsActorDelete.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

void Unk_7102406048::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (mDamageManager->mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
        return;
    if (u32(*a5 - 3) > 25)
        return;
    auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6);
    if (info && (info->mFlags & 1))
        *a5 = 2;
}

LynelRoot::LynelRoot(const InitArg& arg) : EnemyRoot(arg) {}

LynelRoot::~LynelRoot() {
    if (auto* parts = mActor->m101()) {
        if (!mBreathActorName_s.isEmpty()) {
            deleteActorParts(parts, mBreathPartsKey0_s);
            deleteActorParts(parts, mBreathPartsKey1_s);
            deleteActorParts(parts, mBreathPartsKey2_s);
        }
        if (!mRoarFlameActorName_s.isEmpty())
            deleteActorParts(parts, mRoarFlamePartsKey_s);
    }
}

bool LynelRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

// NON_MATCHING: the original reloads `mActor` at the top of each iteration of the weapon loop and once more after it;
// we load it once at the end of the loop body (loop rotation + load merging)
void LynelRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _2c8.sub_710070F350(mActor);
    sub_71005DDA44(mActor);
    ksys::act::disableAttClient(mActor, "HornAttackRide");
    ksys::act::disableAttClient(mActor, "Ride");
    if (mActor->getRootAi()->getI() != 5 && *mIsNearCreate_m)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);

    const s32 count = sub_71005D7854(mActor);
    for (s32 i = 0; i < count; ++i)
        sub_71005DB6D0(mActor, i);

    {
        if (auto* controller = mActor->getCharacterController()) {
            if (auto* as_list = mActor->getASList()) {
                sead::Vector3f velocity;
                if (!controller->sub_7100F5F234(&velocity))
                    velocity = sead::Vector3f::ey;
                as_list->sub_710115F024(velocity, 0);
            }
        }
    }
    if (auto* body = mActor->getMainBody())
        body->clearEntityMotionFlag10(false);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F631B8(true);
    sub_7100721670(&_4a0, mActor, "BodyFrontLeg");
    EnemyRoot::enter_(params);
}

void LynelRoot::leave_() {
    EnemyRoot::leave_();
    if (_478.mDamageManager)
        sub_71005DA114(mActor, &_478);
    _2c8.sub_710070F398(mActor);
}

void LynelRoot::m37() {
    if (mActor->getVelocity().y > 0) {
        if (auto* controller = mActor->getCharacterController()) {
            sead::Vector3f vel;
            controller->sub_7100F5F598(&vel);
            vel.y = 0;
            controller->sub_7100F5F6FC(vel);
        }
    }
    EnemyRoot::m37();
}

void LynelRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mBowIdx_s, "BowIdx");
    getStaticParam(&mBoneStandAddRatio_s, "BoneStandAddRatio");
    getStaticParam(&mRoarFlameActorName_s, "RoarFlameActorName");
    getStaticParam(&mRoarFlamePartsKey_s, "RoarFlamePartsKey");
    getStaticParam(&mBreathActorName_s, "BreathActorName");
    getStaticParam(&mBreathPartsKey0_s, "BreathPartsKey0");
    getStaticParam(&mBreathPartsKey1_s, "BreathPartsKey1");
    getStaticParam(&mBreathPartsKey2_s, "BreathPartsKey2");
    getStaticParam(&mStandBoneName_s, "StandBoneName");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
    getAITreeVariable(&mLynelMoveParam_a, "LynelMoveParam");
    _278.sub_710070F83C(this);
}

}  // namespace uking::ai
