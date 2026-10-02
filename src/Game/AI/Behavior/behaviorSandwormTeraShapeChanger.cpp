#include "Game/AI/Behavior/behaviorSandwormTeraShapeChanger.h"
#include "Game/Actor/actSandworm.h"

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

// NON_MATCHING: the original keeps a jump table with per-case stores (ours: a lookup table)
void SandwormTeraShapeChanger::m8() {
    const int idx = *mEnterShapeIdx_s;
    auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(mActor);
    if (!sandworm)
        return;
    _40 = sandworm->_163c;
    switch (idx) {
    case 0:
        sandworm->_163c = 4;
        break;
    case 1:
        sandworm->_163c = 1;
        break;
    case 2:
        sandworm->_163c = 0;
        break;
    case 3:
        sandworm->_163c = 2;
        break;
    case 4:
        sandworm->_163c = 3;
        break;
    }
}

// NON_MATCHING: the original keeps a jump table with per-case stores (ours: a lookup table)
void SandwormTeraShapeChanger::m9() {
    const int idx = *mLeaveShapeIdx_s;
    auto* sandworm = sead::DynamicCast<uking::act::Sandworm>(mActor);
    if (!sandworm)
        return;
    if (*mIsSetCurrentShape_s) {
        sandworm->_163c = _40;
        return;
    }
    switch (idx) {
    case 0:
        sandworm->_163c = 4;
        break;
    case 1:
        sandworm->_163c = 1;
        break;
    case 2:
        sandworm->_163c = 0;
        break;
    case 3:
        sandworm->_163c = 2;
        break;
    case 4:
        sandworm->_163c = 3;
        break;
    }
}

}  // namespace uking::behavior
