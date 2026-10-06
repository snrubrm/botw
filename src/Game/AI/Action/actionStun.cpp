#include "Game/AI/Action/actionStun.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

Stun::Stun(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Stun::~Stun() = default;

void Stun::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Stun", true, 0, 0, -1.0f);
    _40 = ksys::Timer(f32(*mTime_s), f32(*mTime_s));
    if (!sub_7100281144()) {
        sead::Vector3f direction = mActor->getVelocity();
        if (auto* controller = mActor->getCharacterController()) {
            const f32 speed = direction.normalize();
            _4c.value = speed;
            _4c.prev_value = speed;
            sub_710072C1B4(controller, direction);
        }
        _58.value = mActor->getAngVelocity();
        _58.prev_value = mActor->getAngVelocity();
    }
    _7c = 0;
    mFlags.set(Flag::Changeable);
}

void Stun::leave_() {
    ksys::act::ai::Action::leave_();
}

void Stun::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
}

// NON_MATCHING: the original tests the weapon type with two separate compares (`== 1`, `== 2`) and reads the
// direction vector after the force; ours uses an unsigned range check and a different load order.
bool Stun::sub_7100281144() {
    auto* manager = sub_710072BA90(mActor);
    if (!manager || !sub_7100732AD0(manager->getField54()))
        return false;
    sead::Vector3f direction = sead::Vector3f::zero;
    if (!manager->m30(&direction))
        return false;
    manager = sub_710072BA90(mActor);
    const f32* const* force_param;
    if (!manager) {
        force_param = &mHitImpactForceSmallSwordS_s;
    } else {
        const s32 weapon_type = manager->getField50();
        if (weapon_type == 1 || weapon_type == 2)
            force_param = &mHitImpactForceSpearS_s;
        else
            force_param = &mHitImpactForceSmallSwordS_s;
    }
    const f32 force = **force_param;
    auto* actor = mActor;
    direction = direction * force + actor->getVelocity();
    if (auto* controller = actor->getCharacterController()) {
        const f32 speed = direction.normalize();
        _4c.value = speed;
        _4c.prev_value = speed;
        sub_710072C1B4(controller, direction);
    }
    _58.value = mActor->getAngVelocity();
    _58.prev_value = mActor->getAngVelocity();
    return true;
}

void Stun::calc_() {
    switch (_7c) {
    case 0:
        if (!sub_7100281144())
            _4c *= 0.75f;
        _58 *= 0.75f;
        _40.update();
        if (_40.value <= sead::Mathf::epsilon()) {
            playAS("StunRecover", false, 0, 0, -1.0f);
            _7c = 1;
        }
        break;
    case 1:
        _58 *= 0.75f;
        _4c *= 0.78f;
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    default:
        setFailed();
        break;
    }
    _58.updateStats();
    _4c.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_4c.value * 30.0f);
        controller->sub_7100F5FB24(_58.value * 30.0f);
    }
}

}  // namespace uking::action
