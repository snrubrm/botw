#include "Game/AI/AI/aiViewWaitWithInstDynActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ViewWaitWithInstDynActor::ViewWaitWithInstDynActor(const InitArg& arg) : ViewWait(arg) {}

ViewWaitWithInstDynActor::~ViewWaitWithInstDynActor() = default;

bool ViewWaitWithInstDynActor::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitWithInstDynActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitWithInstDynActor::calc_() {
    ViewWait::calc_();
}

void ViewWaitWithInstDynActor::leave_() {
    ViewWait::leave_();
}

void ViewWaitWithInstDynActor::loadParams_() {
    ViewWait::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void ViewWaitWithInstDynActor::m39(ksys::act::ai::InlineParamPack* params) {
    params->addActor(*mTargetActor_d, "TargetActor", -1);
}

}  // namespace uking::ai
