#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void WaterFloatBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
