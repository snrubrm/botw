#include "Game/AI/Behavior/behaviorSandwormTeraShapeChanger.h"

namespace uking::behavior {

SandwormTeraShapeChanger::SandwormTeraShapeChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SandwormTeraShapeChanger::~SandwormTeraShapeChanger() = default;

bool SandwormTeraShapeChanger::m6(sead::Heap* heap) {
    return true;
}

void SandwormTeraShapeChanger::m7() {}

void SandwormTeraShapeChanger::loadParams() {
    getStaticParam(&mEnterShapeIdx_s, "EnterShapeIdx");
    getStaticParam(&mLeaveShapeIdx_s, "LeaveShapeIdx");
    getStaticParam(&mIsSetCurrentShape_s, "IsSetCurrentShape");
}

}  // namespace uking::behavior
