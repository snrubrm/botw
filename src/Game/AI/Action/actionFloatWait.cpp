#include "Game/AI/Action/actionFloatWait.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"

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
    WaterFloatBase::calc_();
}

}  // namespace uking::action
