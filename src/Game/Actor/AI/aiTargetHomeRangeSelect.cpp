#include "Game/Actor/AI/aiTargetHomeRangeSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TargetHomeRangeSelect::TargetHomeRangeSelect(const InitArg& arg) : NewRangeSelect(arg) {}

TargetHomeRangeSelect::~TargetHomeRangeSelect() = default;

bool TargetHomeRangeSelect::init_(sead::Heap* heap) {
    return NewRangeSelect::init_(heap);
}

void TargetHomeRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    NewRangeSelect::enter_(params);
}

void TargetHomeRangeSelect::calc_() {
    NewRangeSelect::calc_();
}

void TargetHomeRangeSelect::leave_() {
    NewRangeSelect::leave_();
}

void TargetHomeRangeSelect::loadParams_() {
    NewRangeSelect::loadParams_();
}

f32 TargetHomeRangeSelect::m38() {
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    return sead::Mathf::sqrt(ksys::util::sqXZDistance(home_pos, mActor->getMtx().getTranslation()));
}

}  // namespace uking::ai
