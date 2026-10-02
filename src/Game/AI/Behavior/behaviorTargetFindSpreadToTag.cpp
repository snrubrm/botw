#include "Game/AI/Behavior/behaviorTargetFindSpreadToTag.h"

namespace uking::behavior {

TargetFindSpreadToTag::TargetFindSpreadToTag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

TargetFindSpreadToTag::~TargetFindSpreadToTag() = default;

bool TargetFindSpreadToTag::m6(sead::Heap* heap) {
    return true;
}

void TargetFindSpreadToTag::m7() {}

void TargetFindSpreadToTag::m9() {}

void TargetFindSpreadToTag::loadParams() {
    getStaticParam(&mTagName_s, "TagName");
}

}  // namespace uking::behavior
