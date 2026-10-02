#include "Game/AI/AI/aiDungeonRemainsFire.h"

namespace uking::ai {

DungeonRemainsFire::DungeonRemainsFire(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The SafeString member makes the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
DungeonRemainsFire::~DungeonRemainsFire() { ; }

bool DungeonRemainsFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRemainsFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRemainsFire::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRemainsFire::loadParams_() {
    getStaticParam(&mRailName_s, "RailName");
}

}  // namespace uking::ai
