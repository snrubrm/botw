#include "Game/AI/Behavior/behaviorSetBoneControlNoSlow.h"

namespace uking::behavior {

SetBoneControlNoSlow::SetBoneControlNoSlow(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetBoneControlNoSlow::~SetBoneControlNoSlow() = default;

bool SetBoneControlNoSlow::m6(sead::Heap* heap) {
    return true;
}

void SetBoneControlNoSlow::m7() {}

void SetBoneControlNoSlow::loadParams() {

}

}  // namespace uking::behavior
