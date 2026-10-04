#include "Game/AI/Action/actionPriestBossClonesSpawn.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PriestBossClonesSpawn::PriestBossClonesSpawn(const InitArg& arg)
    : PriestBossClonesSpawnForDemo(arg) {}

PriestBossClonesSpawn::~PriestBossClonesSpawn() = default;

bool PriestBossClonesSpawn::init_(sead::Heap* heap) {
    return PriestBossClonesSpawnForDemo::init_(heap);
}

void PriestBossClonesSpawn::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossClonesSpawnForDemo::enter_(params);
}

void PriestBossClonesSpawn::leave_() {
    PriestBossClonesSpawnForDemo::leave_();
    sub_71002218D8();
}

void PriestBossClonesSpawn::loadParams_() {
    PriestBossClonesSpawnForDemo::loadParams_();
    getStaticParam(&mASNameForAITree_s, "ASNameForAITree");
    getDynamicParam(&mDelayFrame_d, "DelayFrame");
}

void PriestBossClonesSpawn::calc_() {
    if (_d9 && _5c >= 1.0f) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        _d9 = false;
    }
    PriestBossClonesSpawnForDemo::calc_();
    if (sub_7100066884())
        sub_71002218D8();
}

}  // namespace uking::action
