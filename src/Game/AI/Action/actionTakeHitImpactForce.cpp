#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: regalloc (keeps &_68 in x20 across the memset)
TakeHitImpactForce::TakeHitImpactForce(const InitArg& arg) : ActionEx(arg) {}

void TakeHitImpactForce::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void TakeHitImpactForce::loadParams_() {
    getStaticParam(&mParams.mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mParams.mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mParams.mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mParams.mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mParams.mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mParams.mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mParams.mVelReduce_s, "VelReduce");
    getStaticParam(&mParams.mHighSpeedY_s, "HighSpeedY");
    getStaticParam(&mParams.mVelReduceY_s, "VelReduceY");
}

void TakeHitImpactForce::calc_() {
    ActionEx::calc_();
}

bool TakeHitImpactForce::isChangeable() const {
    return true;
}

void TakeHitImpactForce::m32(sead::Vector3f* dir, ksys::act::Actor* actor,
                             uking::dmg::DamageManager* mgr) {
    sub_71005E2318(dir, actor, mgr);
}

bool TakeHitImpactForce::m33(sead::Vector3f* dir, uking::dmg::DamageManager* mgr) {
    if (!mgr)
        return false;
    return mgr->m30(dir);
}

void TakeHitImpactForce::m35() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f vel;
    controller->sub_7100F5F598(&vel);
    vel = vel * (1.0f / 30.0f);
    if (*mParams.mHighSpeedY_s > 0.0f && vel.y >= *mParams.mHighSpeedY_s) {
        const f32 y = vel.y * *mParams.mVelReduceY_s;
        vel.y = y;
        sead::Vector3f out = _68.value;
        out.y = y;
        sub_7100737710(controller, out);
    } else {
        sead::Vector3f dir = _68.value;
        const f32 len = dir.normalize();
        sub_710073770C(controller, len, dir);
    }
}

}  // namespace uking::action
