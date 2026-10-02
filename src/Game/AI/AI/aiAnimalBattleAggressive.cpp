#include "Game/AI/AI/aiAnimalBattleAggressive.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::ai {

AnimalBattleAggressive::AnimalBattleAggressive(const InitArg& arg) : EnemyBattle(arg) {}

AnimalBattleAggressive::~AnimalBattleAggressive() = default;

bool AnimalBattleAggressive::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AnimalBattleAggressive::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void AnimalBattleAggressive::leave_() {
    EnemyBattle::leave_();
}

void AnimalBattleAggressive::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mForceAttackTimer_s, "ForceAttackTimer");
    getStaticParam(&mCounterAttackTimer_s, "CounterAttackTimer");
    getStaticParam(&mForceAttackRange_s, "ForceAttackRange");
    getStaticParam(&mCounterAttackRange_s, "CounterAttackRange");
    getAITreeVariable(&mAnimalEnableCounterFlag_a, "AnimalEnableCounterFlag");
}

void AnimalBattleAggressive::m37() {
    _b8 = ksys::Timer(*mForceAttackTimer_s, *mForceAttackTimer_s);
    EnemyBattle::m37();
}

bool AnimalBattleAggressive::m40() {
    if (!EnemyBattle::m40())
        return false;
    auto* actor = mActor;
    return sub_710072E154(actor, sub_71005D9330(actor), nullptr, -1);
}

}  // namespace uking::ai
