#include "Game/AI/AI/aiTargetTargetPos.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

TargetTargetPos::TargetTargetPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetTargetPos::~TargetTargetPos() = default;

bool TargetTargetPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetTargetPos::calc_() {
    TargetPosAI::calc_();
}

void TargetTargetPos::leave_() {
    TargetPosAI::leave_();
}

void TargetTargetPos::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

void TargetTargetPos::m35(sead::Vector3f* pos) {
    *pos = sub_71005D9330(mActor);
    *pos += sub_71005D9548(mActor) * *mAddSpeed_s;
}

}  // namespace uking::ai
