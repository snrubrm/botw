#include "Game/AI/AI/aiSpotBgmTrigger.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SpotBgmTrigger::SpotBgmTrigger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SpotBgmTrigger::~SpotBgmTrigger() {
    ;
}

bool SpotBgmTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpotBgmTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack child_params;
    child_params.addInt(0, "SoundDelay", -1);
    child_params.addString(mSound_m, "Sound", -1);
    child_params.addString("SpotBgm", "SLinkInst", -1);
    changeChild("再生", &child_params);
}

void SpotBgmTrigger::calc_() {}

void SpotBgmTrigger::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SpotBgmTrigger::loadParams_() {
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

}  // namespace uking::ai
