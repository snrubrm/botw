#include "Game/AI/Behavior/behaviorLowCeilingController.h"

namespace uking::behavior {

LowCeilingController::LowCeilingController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
LowCeilingController::~LowCeilingController() {
    ;
}

void LowCeilingController::loadParams() {
    getStaticParam(&mChangeFrame_s, "ChangeFrame");
    getStaticParam(&mReverseFrame_s, "ReverseFrame");
    getStaticParam(&mShapeName_s, "ShapeName");
}

}  // namespace uking::behavior
