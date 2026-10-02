#include "Game/AI/AI/aiPriestBossShadowCloneEnemyRoot.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossShadowCloneEnemyRoot::PriestBossShadowCloneEnemyRoot(const InitArg& arg)
    : PriestBossActorEnemyRoot(arg) {}

PriestBossShadowCloneEnemyRoot::~PriestBossShadowCloneEnemyRoot() = default;

bool PriestBossShadowCloneEnemyRoot::init_(sead::Heap* heap) {
    return PriestBossActorEnemyRoot::init_(heap);
}

void PriestBossShadowCloneEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorEnemyRoot::enter_(params);
}

void PriestBossShadowCloneEnemyRoot::calc_() {
    PriestBossActorEnemyRoot::calc_();
}

void PriestBossShadowCloneEnemyRoot::leave_() {
    PriestBossActorEnemyRoot::leave_();
    sub_710052D6E8();
    mActor->getDamageMgr()->removeDamageCallback(&_230);
}

void PriestBossShadowCloneEnemyRoot::loadParams_() {
    PriestBossActorEnemyRoot::loadParams_();
}

bool PriestBossShadowCloneEnemyRoot::m45() {
    return m35();
}

}  // namespace uking::ai
