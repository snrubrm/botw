#include "Game/AI/AI/aiTargetAbsolutePos.h"

namespace uking::ai {

TargetAbsolutePos::TargetAbsolutePos(const InitArg& arg) : TargetPosAI(arg) {}

TargetAbsolutePos::~TargetAbsolutePos() = default;

bool TargetAbsolutePos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetAbsolutePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetAbsolutePos::calc_() {
    TargetPosAI::calc_();
}

void TargetAbsolutePos::leave_() {
    TargetPosAI::leave_();
}

void TargetAbsolutePos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mTargetPos_s, "TargetPos");
}

void TargetAbsolutePos::m35(sead::Vector3f* pos) {
    *pos = *mTargetPos_s;
}

}  // namespace uking::ai
