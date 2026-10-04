#include "Game/AI/Behavior/behaviorFadeLeaf.h"

namespace uking::behavior {

FadeLeaf::FadeLeaf(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

FadeLeaf::~FadeLeaf() = default;

bool FadeLeaf::m6(sead::Heap* heap) {
    for (s32& idx : _38)
        idx = -1;
    return true;
}

void FadeLeaf::m9() {}

void FadeLeaf::loadParams() {
    getStaticParam(&mAlphaLower_s, "AlphaLower");
    getStaticParam(&mAlphaSpeed_s, "AlphaSpeed");
}

void FadeLeaf::m7() {
    sub_7100622AB0();
}

}  // namespace uking::behavior
