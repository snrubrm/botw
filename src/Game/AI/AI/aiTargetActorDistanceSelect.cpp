#include "Game/AI/AI/aiTargetActorDistanceSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

TargetActorDistanceSelect::TargetActorDistanceSelect(const InitArg& arg)
    : TargetDistanceSelect(arg) {}

TargetActorDistanceSelect::~TargetActorDistanceSelect() = default;

bool TargetActorDistanceSelect::init_(sead::Heap* heap) {
    return TargetDistanceSelect::init_(heap);
}

void TargetActorDistanceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetDistanceSelect::enter_(params);
}

void TargetActorDistanceSelect::leave_() {
    TargetDistanceSelect::leave_();
}

void TargetActorDistanceSelect::loadParams_() {
    TargetDistanceSelect::loadParams_();
}

void TargetActorDistanceSelect::calc_() {
    if (!sub_71005D94AC(mActor).hasProc())
        setFailed();
    TargetDistanceSelect::calc_();
}

}  // namespace uking::ai
