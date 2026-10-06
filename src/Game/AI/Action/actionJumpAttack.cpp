#include "Game/AI/Action/actionJumpAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
JumpAttack::JumpAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}


void JumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpAttack::leave_() {
    sub_71005D79AC(mActor, *mParams.mWeaponIdx_s, act::Unk_71002edaec(1));
    sub_71005DA114(mActor, &_60);
}

void JumpAttack::loadParams_() {
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mParams.mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mParams.mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mParams.mIsForceGuardBreak_s, "IsForceGuardBreak");
}

void JumpAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

bool JumpAttack::isChangeable() const {
    return false;
}

void JumpAttack::m32(f32 a, f32 b) {
    auto* controller = mActor->getCharacterController();
    if (controller) {
        controller->sub_7100F5E7F0(a);
        controller->sub_7100F62B70(b);
    }
}

f32 JumpAttack::m33() {
    return 0.978f;
}

// NON_MATCHING: scheduling / register allocation of the ray start / end component math (calls and constants match).
bool JumpAttack::sub_71001C3964() {
    auto* controller = mActor->getCharacterController();
    if (controller && controller->mFlags.isOnBit(0))
        return false;
    if (isBgGroundHit(mActor, false))
        return true;

    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    sead::Vector3f end = start;
    const sead::Vector3f up = getUpDir(mActor);
    end.x = end.x - up.x * 0.2f;
    end.y = end.y - up.y * 0.2f;
    end.z = end.z - up.z * 0.2f;
    start.y += 0.1f;
    bool hit = sub_710072E928(start, end, nullptr, nullptr, nullptr, 0.0f);
    if (controller && !hit) {
        sead::BoundBox3f aabb;
        controller->sub_7100F61A34()->getAabbInLocal(&aabb);
        const f32 depth = aabb.getMax().z * 0.9f;
        start.x = start.x + mActor->getMtx().m[0][2] * depth;
        start.y = mActor->getMtx().m[1][2] * depth + start.y;
        start.z = mActor->getMtx().m[2][2] * depth + start.z;
        end.x = start.x - up.x * 0.2f;
        end.y = start.y - up.y * 0.2f;
        end.z = start.z - up.z * 0.2f;
        hit = sub_710072E928(start, end, nullptr, nullptr, nullptr, 0.0f);
    }
    return hit;
}

}  // namespace uking::action
