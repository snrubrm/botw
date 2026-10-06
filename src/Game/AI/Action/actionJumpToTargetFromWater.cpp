#include "Game/AI/Action/actionJumpToTargetFromWater.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

// Source owner and namespace are unknown.
void sub_71006F54EC(ksys::phys::CharacterController* controller);
void sub_71006F5538(ksys::phys::CharacterController* controller);
void sub_7100737710(ksys::phys::CharacterController* controller, const sead::Vector3f& vel);
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 floatDepth, f32 inWaterDepth,
                    f32 floatRadius, f32 floatCycleTime, f32 changeDepthSpeed);

namespace uking::action {

JumpToTargetFromWater::JumpToTargetFromWater(const InitArg& arg) : JumpTo(arg) {}

JumpToTargetFromWater::~JumpToTargetFromWater() = default;

bool JumpToTargetFromWater::init_(sead::Heap* heap) {
    return JumpTo::init_(heap);
}

void JumpToTargetFromWater::enter_(ksys::act::ai::InlineParamPack* params) {
    _e8.sub_710072AD1C(mActor->getCharacterController());
    JumpTo::enter_(params);
}

void JumpToTargetFromWater::leave_() {
    JumpTo::leave_();
    _e8.resetMotionType(mActor->getCharacterController());
}

void JumpToTargetFromWater::loadParams_() {
    JumpTo::loadParams_();
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mPreJumpAS_s, "PreJumpAS");
    getStaticParam(&mJumpAS_s, "JumpAS");
    getStaticParam(&mLandAS_s, "LandAS");
}

void JumpToTargetFromWater::calc_() {
    JumpTo::calc_();
}

void JumpToTargetFromWater::m32() {
    playAS(mPreJumpAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTargetFromWater::m33() {
    playAS(mJumpAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTargetFromWater::m34() {
    playAS(mLandAS_s.cstr(), false, 0, 0, -1.0f);
}

void JumpToTargetFromWater::m40() {
    if (!sub_71001C72A8()) {
        JumpTo::m40();
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const f32 velY = mActor->getVelocity().y;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    f32 velY2;
    sub_71005DF820(&velY2, velY, depth, *mFloatDepth_s, *mParams.mInWaterDepth_s, *mFloatRadius_s,
                   *mFloatCycleTime_s, -1.0f);
    _58 *= *mParams.mPosReduceRatioOnGround_s;
    _58.updateStats();
    sead::Vector3f vel = _88 * _58.value;
    vel.y = velY2;
    sub_7100737710(controller, vel);
}

void JumpToTargetFromWater::m42() {
    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    const f32 jump_height = *mParams.mJumpHeight_s;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    const f32 height = jump_height + depth;
    const sead::Vector3f gravity = getGravity(mActor) * (1.0f / 900.0f);
    f32 speed;
    f32 time;
    // discarded result: the original ignores whether a solution exists
    sub_710072CD88(height, &speed, &time, &start, mParams.mTargetPos_d, &gravity);
    const f32 up_speed = sub_710072D068(&gravity, height);
    _58.value = _58.prev_value = speed;
    _58.updateStats();
    const sead::Vector3f vel{speed * _88.x, up_speed, speed * _88.z};
    if (auto* controller = mActor->getCharacterController()) {
        sub_71006F5538(controller);
        sub_7100737710(controller, vel);
    }
}

void JumpToTargetFromWater::m43() {
    if (sub_71001C72A8()) {
        if (auto* controller = mActor->getCharacterController())
            sub_71006F54EC(controller);
    }
}

}  // namespace uking::action
