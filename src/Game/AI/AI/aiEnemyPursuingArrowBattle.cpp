#include "Game/AI/AI/aiEnemyPursuingArrowBattle.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyPursuingArrowBattle::EnemyPursuingArrowBattle(const InitArg& arg) : BokoblinArrowBattle(arg) {}

EnemyPursuingArrowBattle::~EnemyPursuingArrowBattle() = default;

void EnemyPursuingArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BokoblinArrowBattle::enter_(params);
}

void EnemyPursuingArrowBattle::loadParams_() {
    BokoblinArrowBattle::loadParams_();
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartDist_s, "PursuingAttackStartDist");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

// NON_MATCHING: the original stores the timer value / previous value separately (no stp), in the order rate, value, previous
void EnemyPursuingArrowBattle::sub_71003A8A44() {
    const s32 rand = *mPursuingAttackIntervalRand_s;
    const f32 random_part = rand * -0.5f;
    const f32 interval = *mPursuingAttackInterval_s;
    _148.reset(s32(interval + random_part) + s32(sead::GlobalRandom::instance()->getU32(rand)));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追撃ち", &pack);
}

}  // namespace uking::ai
