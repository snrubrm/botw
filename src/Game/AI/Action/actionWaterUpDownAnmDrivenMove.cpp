#include "Game/AI/Action/actionWaterUpDownAnmDrivenMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WaterUpDownAnmDrivenMove::WaterUpDownAnmDrivenMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaterUpDownAnmDrivenMove::~WaterUpDownAnmDrivenMove() = default;

bool WaterUpDownAnmDrivenMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownAnmDrivenMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterUpDownAnmDrivenMove::leave_() {
    _54.resetMotionType(_54.sub_710072ACF8(mActor));
}

void WaterUpDownAnmDrivenMove::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mTargetDepth_s, "TargetDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void WaterUpDownAnmDrivenMove::calc_() {
    ksys::act::ai::Action::calc_();
}

void WaterUpDownAnmDrivenMove::m32(ksys::phys::CharacterController* controller) {
    sub_7100738AA8(mActor, *mRotReduceRatio_s);
}

}  // namespace uking::action
