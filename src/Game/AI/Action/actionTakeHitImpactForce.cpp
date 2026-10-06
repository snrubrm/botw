#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: regalloc (keeps &_68 in x20 across the memset)
TakeHitImpactForce::TakeHitImpactForce(const InitArg& arg) : ActionEx(arg) {}

// NON_MATCHING: stack layout matches (velocity, dir, out declared in this order); the original materialises the
// `Vector3f::zero` / `ez` copies per path (after the manager test, not hoisted to the top) and loads the velocity
// components in a different order.
void TakeHitImpactForce::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f velocity;
    sead::Vector3f dir = sead::Vector3f::ez;
    sead::Vector3f out = sead::Vector3f::zero;
    auto* manager = sub_710072BA90(mActor);
    ksys::act::Actor* actor;
    if (manager) {
        if (m36() && manager->isSlowTime())
            return;
        m32(&dir, mActor, manager);
        actor = mActor;
    } else {
        actor = mActor;
        dir = -actor->getMtx().getBase(2);
    }
    sub_71005E22D4(&out, actor, dir, sub_71001C9444());
    _68.value = out;
    _68.prev_value = out;
    if (!mActor->getCharacterController()) {
        const f32 force = sub_71001C9444();
        if (auto* body = mActor->getMainBody()) {
            const f32 y = force * dir.y;
            velocity.set(force * dir.x, y < 0.0f ? -y : y, force * dir.z);
            velocity *= 30.0f;
            body->setLinearVelocity(velocity);
        }
    }
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

// NON_MATCHING: same logic; the original lays out the blocks differently (the slow-time / velocity-reduce arms first)
// and the impact block is the same as enter_'s (inlined in both).
void TakeHitImpactForce::calc_() {
    sead::Vector3f velocity;
    sead::Vector3f dir;
    auto* manager = sub_710072BA90(mActor);
    if (manager && sub_7100732AD0(manager->getField54()) && m33(&dir, manager)) {
        if (!manager->isSlowTime()) {
            auto* actor = mActor;
            sead::Vector3f out = sead::Vector3f::zero;
            sub_71005E22D4(&out, actor, dir, sub_71001C9444());
            _68.value = out;
            _68.prev_value = out;
            if (!mActor->getCharacterController()) {
                const f32 force = sub_71001C9444();
                if (auto* body = mActor->getMainBody()) {
                    const f32 y = force * dir.y;
                    velocity.set(force * dir.x, y < 0.0f ? -y : y, force * dir.z);
                    velocity *= 30.0f;
                    body->setLinearVelocity(velocity);
                }
            }
        }
        m34();
    } else {
        _68 *= *mParams.mVelReduce_s;
    }
    _68.updateStats();
    m35();
    if (m37())
        setFinished();
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

f32 TakeHitImpactForce::sub_71001C9444() {
    auto* manager = sub_710072BA90(mActor);
    if (!manager)
        return *mParams.mHitImpactForceSmallSwordS_s;

    const float* const* force;
    switch (manager->getField50()) {
    case 2:
        if (sub_7100736B68(manager->getField54()))
            force = &mParams.mHitImpactForceSpearL_s;
        else
            force = &mParams.mHitImpactForceSpearS_s;
        break;
    case 1:
        if (sub_7100736B68(manager->getField54()))
            force = &mParams.mHitImpactForceLargeSwordL_s;
        else
            force = &mParams.mHitImpactForceLargeSwordS_s;
        break;
    default:
        if (sub_7100736B68(manager->getField54()))
            force = &mParams.mHitImpactForceSmallSwordL_s;
        else
            force = &mParams.mHitImpactForceSmallSwordS_s;
        break;
    }
    return **force * manager->sub_71006D8DE8();
}

}  // namespace uking::action
