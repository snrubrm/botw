#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"
#include "Game/AI/aiUnk_710071edf8.h"

namespace uking::ai {

PriestBossActorEnemyRoot::PriestBossActorEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

PriestBossActorEnemyRoot::~PriestBossActorEnemyRoot() = default;

bool PriestBossActorEnemyRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void PriestBossActorEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void PriestBossActorEnemyRoot::calc_() {
    if (sub_710071E208())
        return;

    m48();
    m49();
    m50();
    if (m51() || m53())
        return;

    EnemyRoot::calc_();
}

void PriestBossActorEnemyRoot::leave_() {
    EnemyRoot::leave_();
    sub_7100507440(false);
    sub_710071EDD0(mActor, _22c);
}

void PriestBossActorEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mIsReactionOnDead_s, "IsReactionOnDead");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

bool PriestBossActorEnemyRoot::handleMessage_(const ksys::Message& message) {
    EnemyRoot::handleMessage_(message);
    return false;
}

bool PriestBossActorEnemyRoot::m45() {
    return false;
}

bool PriestBossActorEnemyRoot::m46() {
    return false;
}

bool PriestBossActorEnemyRoot::m47() {
    return true;
}

}  // namespace uking::ai
