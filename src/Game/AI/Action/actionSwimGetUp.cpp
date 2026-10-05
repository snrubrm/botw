#include "Game/AI/Action/actionSwimGetUp.h"
#include "KingSystem/ActorSystem/actActor.h"

// The source namespace and pointer constness are inferred from controller utility callers.
bool sub_71006F564C(ksys::phys::CharacterController* controller);

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

// NON_MATCHING: the surface-height and position-height loads are scheduled in the opposite order.
void SwimGetUp::calc_() {
    GetUp::calc_();
    if (sub_71006F564C(mActor->getCharacterController()))
        return;
    f32 depth = 0.0f;
    if (mActor->get68f().load())
        depth = mActor->get6f0() - mActor->getMtx().m[1][3];
    if (depth >= *mUnderWaterDepth_s)
        sub_7100289858();
}

}  // namespace uking::action
