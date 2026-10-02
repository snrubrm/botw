#include "Game/AI/Action/actionJumpAttack.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: store scheduling (the damage callback member's zero stores are ordered differently)
JumpAttack::JumpAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpAttack::~JumpAttack() = default;

void JumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void JumpAttack::leave_() {
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
    sub_71005DA114(mActor, &_60);
}

void JumpAttack::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
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

}  // namespace uking::action
