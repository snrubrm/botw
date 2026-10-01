#include "Game/AI/AI/aiTargetBeatGetDrop.h"

namespace uking::ai {

TargetBeatGetDrop::TargetBeatGetDrop(const InitArg& arg) : TargetBeatCheck(arg) {}

TargetBeatGetDrop::~TargetBeatGetDrop() = default;

bool TargetBeatGetDrop::init_(sead::Heap* heap) {
    return TargetBeatCheck::init_(heap);
}

void TargetBeatGetDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetBeatCheck::enter_(params);
    _6c = false;
}

void TargetBeatGetDrop::leave_() {
    TargetBeatCheck::leave_();
}

void TargetBeatGetDrop::loadParams_() {
    TargetBeatCheck::loadParams_();
    getStaticParam(&mSearchDist_s, "SearchDist");
}

bool TargetBeatGetDrop::isChangeable() const {
    if (isCurrentChild("ドロップ取得") && !_6c)
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
