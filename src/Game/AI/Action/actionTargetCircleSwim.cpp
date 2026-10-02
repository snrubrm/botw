#include "Game/AI/Action/actionTargetCircleSwim.h"
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace uking::action
