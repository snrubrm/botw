#include "Game/AI/AI/aiTargetHomeRangeSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TargetHomeRangeSelect::TargetHomeRangeSelect(const InitArg& arg) : RangeSelect(arg) {}

TargetHomeRangeSelect::~TargetHomeRangeSelect() = default;

bool TargetHomeRangeSelect::init_(sead::Heap* heap) {
    return RangeSelect::init_(heap);
}

void TargetHomeRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void TargetHomeRangeSelect::calc_() {
    RangeSelect::calc_();
}

void TargetHomeRangeSelect::leave_() {
    RangeSelect::leave_();
}

void TargetHomeRangeSelect::loadParams_() {
    RangeSelect::loadParams_();
}

f32 TargetHomeRangeSelect::m38() {
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    return sead::Mathf::sqrt(ksys::util::sqXZDistance(home_pos, mActor->getMtx().getTranslation()));
}

}  // namespace uking::ai
