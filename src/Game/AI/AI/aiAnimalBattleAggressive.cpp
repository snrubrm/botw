#include "Game/AI/AI/aiAnimalBattleAggressive.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

AnimalBattleAggressive::AnimalBattleAggressive(const InitArg& arg) : EnemyBattle(arg) {}

AnimalBattleAggressive::~AnimalBattleAggressive() = default;

bool AnimalBattleAggressive::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AnimalBattleAggressive::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100381ED4();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = -1.0f;
    _b8 = ksys::Timer(*mForceAttackTimer_s, *mForceAttackTimer_s);
    _c4 = ksys::Timer(*mCounterAttackTimer_s, *mCounterAttackTimer_s);
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        m44();
    else if (m40() && m41())
        m38();
    else
        m37();
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

void AnimalBattleAggressive::m44() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = 0;
    const f32 time = *mCounterAttackTimer_s * 0.5f;
    _c4 = ksys::Timer(time, time);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("ダメージ後", &pack);
}

void AnimalBattleAggressive::m45() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e68.rate = 0;
    const f32 time = *mCounterAttackTimer_s;
    _c4 = ksys::Timer(time, time);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("カウンター攻撃", &pack);
}

}  // namespace uking::ai
