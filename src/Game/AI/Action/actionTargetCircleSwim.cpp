#include "Game/AI/Action/actionTargetCircleSwim.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

void sub_71006F54EC(ksys::phys::CharacterController* controller);
bool sub_71006F564C(ksys::phys::CharacterController* controller);
// Name and signature are inferred from the call sites (also used by SwimGetUp and others).
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth,
                    f32 floatRadius, f32 floatCycleTime, f32 changeDepthSpeed);

namespace uking::action {

TargetCircleSwim::TargetCircleSwim(const InitArg& arg) : TargetCircle(arg) {}

TargetCircleSwim::~TargetCircleSwim() = default;

void TargetCircleSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircle::enter_(params);
    playAS("SideSwim", false, 0, 0, -1.0f);
    _a8.sub_710072AD1C(mActor->getCharacterController());
}

void TargetCircleSwim::leave_() {
    TargetCircle::leave_();
    _a8.resetMotionType(mActor->getCharacterController());
}

void TargetCircleSwim::loadParams_() {
    TargetCircle::loadParams_();
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
}

// NON_MATCHING: the two argument register copies at entry (speed, dir) are emitted in the opposite order.
void TargetCircleSwim::m33(ksys::phys::CharacterController* controller, f32 speed,
                           const sead::Vector3f& dir) {
    sub_71006F54EC(controller);
    f32 out = 0.0f;
    const f32 velY = mActor->getVelocity().y;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    sub_71005DF820(&out, velY, depth, *mFloatDepth_s, *mInWaterDepth_s, 0.1f, 30.0f, -1.0f);
    sead::Vector3f vel = dir;
    vel.x *= speed;
    vel.z *= speed;
    vel.y = out;
    if (sub_71006F564C(controller))
        sub_710073770C(controller, speed, dir);
    else
        sub_7100737710(controller, vel);
}

}  // namespace uking::action
