#include "Game/AI/Action/actionWaterFloatImmobile.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

WaterFloatImmobile::WaterFloatImmobile(const InitArg& arg) : WaterFloatBase(arg) {}

bool WaterFloatImmobile::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void WaterFloatImmobile::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
}

void WaterFloatImmobile::leave_() {
    WaterFloatBase::leave_();
}

void WaterFloatImmobile::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngleReduceRatio_s, "AngleReduceRatio");
}

void WaterFloatImmobile::calc_() {
    sub_71002B51B8();
    if (auto* controller = mActor->getCharacterController()) {
        const f32 delta = ksys::VFR::instance()->getDeltaFrame();
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        const f32 pos_factor = std::pow(*mPosReduceRatio_s, delta);
        velocity.x *= pos_factor;
        velocity.z *= pos_factor;
        velocity.y = _50;
        controller->sub_7100F5F6FC(velocity);
        sead::Vector3f angular_velocity;
        controller->sub_7100F635BC(&angular_velocity);
        angular_velocity *= std::pow(*mAngleReduceRatio_s, delta);
        controller->sub_7100F5FB24(angular_velocity);
    }
}

}  // namespace uking::action
