#include "Game/AI/Action/actionFloatWait.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

FloatWait::FloatWait(const InitArg& arg) : WaterFloatBase(arg) {}

FloatWait::~FloatWait() = default;

bool FloatWait::init_(sead::Heap* heap) {
    return WaterFloatBase::init_(heap);
}

void FloatWait::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatBase::enter_(params);
    mFlags.reset(Flag::Changeable);
    if (auto* controller = mActor->getCharacterController()) {
        auto* actor = mActor;
        bool in_water = false;
        if (actor->get68f()) {
            const f32 y = actor->getMtx().m[1][3];
            in_water = actor->get6f0() - y >= *mInWaterDepth_s;
        }
        if (in_water)
            controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        else
            controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5E7F0(0.0f);
    }
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), true, 0, 0, -1.0f);
}

void FloatWait::leave_() {
    WaterFloatBase::leave_();
}

void FloatWait::loadParams_() {
    WaterFloatBase::loadParams_();
    getStaticParam(&mWaterEffectSpeedRate_s, "WaterEffectSpeedRate");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void FloatWait::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    auto* actor = mActor;
    bool in_water = false;
    if (actor->get68f()) {
        const f32 y = actor->getMtx().m[1][3];
        in_water = actor->get6f0() - y >= *mInWaterDepth_s;
    }
    if (in_water) {
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        if (controller->get18c() == 1 || controller->isBit4Of116()) {
            const f32 value = controller->sub_7100F60370();
            controller->sub_7100F60398(sead::Vector3f(0.0f, -0.1f, 0.0f) * value);
        } else {
            WaterFloatBase::calc_();
        }
        const f32 delta_frame = ksys::VFR::instance()->getDeltaFrame();
        const sead::Vector3f velocity = delta_frame * controller->get180();
        controller->sub_7100F60398(velocity * controller->sub_7100F60370() * *mWaterEffectSpeedRate_s);
        sub_7100737C0C(controller, 0.9f, -sead::Vector3f::ey);
        sub_7100738660(controller, 0.8f);
    } else {
        if (controller->sub_7100F5F0E4() == ksys::act::MotionType::Hover)
            controller->sub_7100F5F458(ksys::act::MotionType::_1);
        sub_7100737C0C(controller, 0.8f, -sead::Vector3f::ey);
        sub_7100738660(controller, 0.8f);
        controller->sub_7100F5E7F0(0.0f);
        sub_710072C1B4(controller, mActor->getMtx().getBase(2));
    }
}

}  // namespace uking::action
