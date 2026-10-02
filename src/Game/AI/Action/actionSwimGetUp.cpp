#include "Game/AI/Action/actionSwimGetUp.h"
#include "KingSystem/ActorSystem/actActor.h"

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

void SwimGetUp::calc_() {
    GetUp::calc_();
}

}  // namespace uking::action
