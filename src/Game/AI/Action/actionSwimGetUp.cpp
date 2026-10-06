#include "Game/AI/Action/actionSwimGetUp.h"
#include "KingSystem/ActorSystem/actActor.h"

// The source namespace and pointer constness are inferred from controller utility callers.
bool sub_71006F564C(ksys::phys::CharacterController* controller);
void sub_71006F54EC(ksys::phys::CharacterController* controller);
void sub_7100737710(ksys::phys::CharacterController* controller, const sead::Vector3f& vel);
// Name and signature are inferred from the call sites; the six params are passed in the order of
// the static params below.
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 a, f32 b, f32 c, f32 d, f32 e);

namespace uking::action {

SwimGetUp::SwimGetUp(const InitArg& arg) : GetUp(arg) {}

SwimGetUp::~SwimGetUp() = default;

void SwimGetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUp::enter_(params);
    _190.sub_710072AD1C(mActor->getCharacterController());
}

void SwimGetUp::leave_() {
    GetUp::leave_();
    _190.resetMotionType(mActor->getCharacterController());
}

void SwimGetUp::loadParams_() {
    GetUp::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mUnderWaterDepth_s, "UnderWaterDepth");
}

void SwimGetUp::sub_7100289858() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sub_71006F54EC(controller);
    const f32 velY = mActor->getVelocity().y;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    f32 y;
    sub_71005DF820(&y, velY, depth, *mFloatDepth_s, *mInWaterDepth_s,
                   *mFloatRadius_s, *mFloatCycleTime_s, *mChangeDepthSpeed_s);
    sead::Vector3f vel = mActor->getVelocity();
    vel.y = y;
    sub_7100737710(controller, vel);
}

void SwimGetUp::calc_() {
    GetUp::calc_();
    if (sub_71006F564C(mActor->getCharacterController()))
        return;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    if (depth >= *mUnderWaterDepth_s)
        sub_7100289858();
}

}  // namespace uking::action
