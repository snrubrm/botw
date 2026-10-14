#include "Game/Actor/Action/actionWaterFloatWaitEx.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyAccessor.h"
#include "KingSystem/System/VFR.h"
#include <cmath>

namespace uking::action {

WaterFloatWaitEx::WaterFloatWaitEx(const InitArg& arg) : WaterFloatWait(arg) {}

WaterFloatWaitEx::~WaterFloatWaitEx() = default;

bool WaterFloatWaitEx::init_(sead::Heap* heap) {
    return WaterFloatWait::init_(heap);
}

// NON_MATCHING: the stores of _d0 are paired (y, z) + x in the original and the 0.6f constant load is
// scheduled earlier; the original copies the angular velocity into _dc with one 8 + 4 byte copy.
void WaterFloatWaitEx::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatWait::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sead::Vector3f velocity;
    controller->sub_7100F635C4()->getLinearVelocity(&velocity);
    _d0 = sead::Vector3f(velocity.x, 0.0f, velocity.z);
    const f32 speed = _d0.normalize();
    const f32 clamped_speed = sead::Mathf::clamp(speed, 0.0f, *mAdditionalVelocityMax_s * 30.0f);
    const auto& mtx = mActor->getMtx();
    const f32 ratio = sead::Mathf::clamp(
        (mtx.m[0][2] * _d0.x + mtx.m[1][2] * _d0.y + mtx.m[2][2] * _d0.z + 1.0f) * 0.6f, 0.0f,
        1.0f);
    const f32 length = _d0.length();
    if (length > 0.0f)
        _d0 *= clamped_speed * ratio / length;
    controller->sub_7100F635BC(&velocity);
    _dc = velocity;
}

void WaterFloatWaitEx::leave_() {
    WaterFloatWait::leave_();
}

void WaterFloatWaitEx::loadParams_() {
    WaterFloatWait::loadParams_();
    getStaticParam(&mAdditionalPosReduceRatio_s, "AdditionalPosReduceRatio");
    getStaticParam(&mAdditionalAngleReduceRatio_s, "AdditionalAngleReduceRatio");
    getStaticParam(&mAdditionalVelocityMax_s, "AdditionalVelocityMax");
    getStaticParam(&mWaterEffectSpeedRate_s, "WaterEffectSpeedRate");
}

// NON_MATCHING: register allocation of the vector sums (the original loads the velocity z before _d0).
// Applies the remaining push from enter_ (decaying with AdditionalPosReduceRatio / AdditionalAngleReduceRatio per
// frame) and, deep enough in the water, the water current scaled by WaterEffectSpeedRate.
void WaterFloatWaitEx::calc_() {
    WaterFloatWait::calc_();
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    {
        const f32 delta = ksys::VFR::instance()->getDeltaFrame();
        _d0 *= std::pow(*mAdditionalPosReduceRatio_s, delta);
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        velocity = velocity + _d0;
        controller->sub_7100F5F6FC(velocity);

        _dc *= std::pow(*mAdditionalAngleReduceRatio_s, delta);
        controller->sub_7100F635BC(&velocity);
        velocity = velocity + _dc;
        controller->sub_7100F5FB24(velocity);
    }

    auto* actor = mActor;
    if (!actor->get68f())
        return;
    const f32 y = actor->getMtx().m[1][3];
    if (actor->get6f0() - y >= *mInWaterDepth_s && *mWaterEffectSpeedRate_s > sead::Mathf::epsilon()) {
        if (controller->_18c == 1 || controller->_116 & 0x10) {
            controller->sub_7100F60398(sead::Vector3f(0.0f, -0.1f, 0.0f) *
                                       controller->sub_7100F60370());
        }
        controller->sub_7100F60398(controller->_180 * ksys::VFR::instance()->getDeltaFrame() *
                                   controller->sub_7100F60370() * *mWaterEffectSpeedRate_s);
    }
}

}  // namespace uking::action
