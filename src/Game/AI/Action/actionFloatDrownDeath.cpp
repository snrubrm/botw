#include "Game/AI/Action/actionFloatDrownDeath.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include <cmath>

// Name and signature are inferred from the call sites (see actionSwimGetUp.cpp).
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth,
                    f32 floatRadius, f32 floatCycleTime, f32 changeDepthSpeed);

namespace uking::action {

FloatDrownDeath::FloatDrownDeath(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FloatDrownDeath::~FloatDrownDeath() = default;

bool FloatDrownDeath::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FloatDrownDeath::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_71005D8748(mActor, sead::Vector3f::zero, true, false, nullptr, false);
    if (auto* cc = mActor->getCharacterController())
        _40.changeMotionType(cc, ksys::act::MotionType::Hover);
}

void FloatDrownDeath::leave_() {
    _40.resetMotionType(_40.sub_710072ACF8(mActor));
}

void FloatDrownDeath::loadParams_() {
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatSpeed_s, "FloatSpeed");
    getStaticParam(&mASName_s, "ASName");
}

void FloatDrownDeath::calc_() {
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f vel;
        controller->sub_7100F5F598(&vel);
        vel.x *= std::pow(0.65f, ksys::VFR::instance()->getDeltaFrame());
        f32 out = vel.y / 30.0f;
        f32 depth = 0.0f;
        if (mActor->get68f().load()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        }
        sub_71005DF820(&out, out, depth, *mFloatDepth_s, 0.0f, 0.1f, 30.0f, *mFloatSpeed_s);
        vel.y = out * 30.0f;
        vel.z *= std::pow(0.65f, ksys::VFR::instance()->getDeltaFrame());
        controller->sub_7100F5F6FC(vel);
        sub_7100738660(controller, 0.85f);
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
