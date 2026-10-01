#include "Game/AI/AI/aiSwitchDistance.h"

namespace uking::ai {

SwitchDistance::SwitchDistance(const InitArg& arg) : SwitchAI(arg) {}

SwitchDistance::~SwitchDistance() = default;

bool SwitchDistance::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchDistance::leave_() {
    SwitchAI::leave_();
}

void SwitchDistance::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mOnDis_s, "OnDis");
    getStaticParam(&mOffsetDis_s, "OffsetDis");
    getStaticParam(&mChangeSeq_s, "ChangeSeq");
}

void SwitchDistance::calc_() {
    SwitchAI::calc_();
}

bool SwitchDistance::m37() {
    auto* child = getCurrentChild();
    return isCurrentChild("オン") && child->isFinished();
}

bool SwitchDistance::m38() {
    auto* child = getCurrentChild();
    return isCurrentChild("オフ") && child->isFinished();
}

}  // namespace uking::ai
