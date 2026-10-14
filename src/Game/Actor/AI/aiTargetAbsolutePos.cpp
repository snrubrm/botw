#include "Game/Actor/AI/aiTargetAbsolutePos.h"

namespace uking::ai {

TargetAbsolutePos::TargetAbsolutePos(const InitArg& arg) : TargetActorPos(arg) {}

TargetAbsolutePos::~TargetAbsolutePos() = default;

bool TargetAbsolutePos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetAbsolutePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetAbsolutePos::calc_() {
    TargetActorPos::calc_();
}

void TargetAbsolutePos::leave_() {
    TargetActorPos::leave_();
}

void TargetAbsolutePos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mTargetPos_s, "TargetPos");
}

void TargetAbsolutePos::m35(sead::Vector3f* pos) {
    *pos = *mTargetPos_s;
}

}  // namespace uking::ai
