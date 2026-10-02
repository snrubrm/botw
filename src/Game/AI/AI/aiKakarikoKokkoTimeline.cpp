#include "Game/AI/AI/aiKakarikoKokkoTimeline.h"

namespace uking::ai {

KakarikoKokkoTimeline::KakarikoKokkoTimeline(const InitArg& arg) : AnimalTimelineAI(arg) {}

// The SafeString members make the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
KakarikoKokkoTimeline::~KakarikoKokkoTimeline() { ; }

bool KakarikoKokkoTimeline::init_(sead::Heap* heap) {
    return AnimalTimelineAI::init_(heap);
}

void KakarikoKokkoTimeline::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalTimelineAI::enter_(params);
}

void KakarikoKokkoTimeline::calc_() {
    sub_7100450D14();
    AnimalTimelineAI::calc_();
}

void KakarikoKokkoTimeline::leave_() {
    AnimalTimelineAI::leave_();
}

void KakarikoKokkoTimeline::loadParams_() {
    AnimalTimelineAI::loadParams_();
    getStaticParam(&mForceChangeChildKeyName_s, "ForceChangeChildKeyName");
    getStaticParam(&mStartForceChangeFlagName_s, "StartForceChangeFlagName");
    getStaticParam(&mEndForceChangeFlagName_s, "EndForceChangeFlagName");
    getMapUnitParam(&mCheckGatheredFlagName_m, "CheckGatheredFlagName");
}

}  // namespace uking::ai
