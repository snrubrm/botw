#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

void sub_7100737710(ksys::phys::CharacterController* controller, const sead::Vector3f& vel);
// Name and signature are inferred from the call sites.
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 a, f32 b, f32 c, f32 d, f32 e);

namespace uking::action {

WaterFloatBase::WaterFloatBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool WaterFloatBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterFloatBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }
    mCCAccessor.changeMotionType(cc, ksys::act::MotionType::Hover);
    _50 = mActor->getVelocity().y * 30.0f;
}

void WaterFloatBase::leave_() {
    auto* actor = mActor;
    mCCAccessor.resetRigidBodyMotion(actor);
    mCCAccessor.resetMotionType(actor->getCharacterController());
}

void WaterFloatBase::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mIsCheckWaterFall_s, "IsCheckWaterFall");
}

// NON_MATCHING: the velocity scaling is scheduled differently (the original loads x,y with one ldp
// and keeps the scaled values in registers; the pointer to y is formed after the scaling).
void WaterFloatBase::sub_71002B50B4() {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }
    sead::Vector3f vel;
    cc->sub_7100F5F598(&vel);
    vel = vel * (1.0f / 30.0f);
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    sub_71005DF820(&vel.y, vel.y, depth, *mFloatDepth_s, *mInWaterDepth_s, *mFloatRadius_s,
                   *mFloatCycleTime_s, *mChangeDepthSpeed_s);
    if (*mIsCheckWaterFall_s && (cc->_116 & 0x10))
        vel.y = 0.0f;
    sub_7100737710(cc, vel);
    _50 = vel.y * 30.0f;
}

void WaterFloatBase::sub_71002B51B8() {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }
    f32 speed;
    {
        sead::Vector3f velocity;
        cc->sub_7100F5F598(&velocity);
        speed = velocity.y / 30.0f;
    }
    f32 out = speed;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    sub_71005DF820(&out, speed, depth, *mFloatDepth_s, *mInWaterDepth_s, *mFloatRadius_s,
                   *mFloatCycleTime_s, *mChangeDepthSpeed_s);
    if (*mIsCheckWaterFall_s && (cc->_116 & 0x10))
        out = 0.0f;
    _50 = out * 30.0f;
}

void WaterFloatBase::calc_() {
    sub_71002B50B4();
}

}  // namespace uking::action
