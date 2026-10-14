#include "Game/Actor/AI/aiTargetTargetPos.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::ai {

TargetTargetPos::TargetTargetPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetTargetPos::~TargetTargetPos() = default;

bool TargetTargetPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetTargetPos::calc_() {
    TargetActorPos::calc_();
}

void TargetTargetPos::leave_() {
    TargetActorPos::leave_();
}

void TargetTargetPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mAddSpeed_s, "AddSpeed");
}

void TargetTargetPos::m35(sead::Vector3f* pos) {
    *pos = sub_71005D9330(mActor);
    *pos += sub_71005D9548(mActor) * *mAddSpeed_s;
}

}  // namespace uking::ai
