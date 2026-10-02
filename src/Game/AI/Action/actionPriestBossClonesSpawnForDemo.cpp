#include "Game/AI/Action/actionPriestBossClonesSpawnForDemo.h"

namespace uking::action {

// NON_MATCHING: zero-store merging of _54-_5c (the original merges _58/_5c, ours _54/_58)
PriestBossClonesSpawnForDemo::PriestBossClonesSpawnForDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PriestBossClonesSpawnForDemo::~PriestBossClonesSpawnForDemo() = default;

bool PriestBossClonesSpawnForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossClonesSpawnForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossClonesSpawnForDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossClonesSpawnForDemo::loadParams_() {
    getDynamicParam(&mDurationFrame_d, "DurationFrame");
    getDynamicParam(&mDecelerationFrame_d, "DecelerationFrame");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mOffset_d, "Offset");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void PriestBossClonesSpawnForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

int PriestBossClonesSpawnForDemo::m32() {
    return 1;
}

}  // namespace uking::action
