#include "Game/AI/AI/aiOnCliffEnemyBattle.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OnCliffEnemyBattle::OnCliffEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffEnemyBattle::~OnCliffEnemyBattle() = default;

bool OnCliffEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    const int counter = *mLostCounter_s;
    const int counter2 = counter * 1.1f;
    _6c = sead::Mathi::min(counter, counter2);
    _70 = sead::Mathi::max(counter, counter2);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D960C(mActor), "TargetPos", -1);
    changeChild("追跡", &pack);
}

void OnCliffEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffEnemyBattle::loadParams_() {
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mAttackDist_s, "AttackDist");
    getStaticParam(&mAttackAngleH_s, "AttackAngleH");
    getStaticParam(&mAttackAngleVMax_s, "AttackAngleVMax");
    getStaticParam(&mAttackAngleVMin_s, "AttackAngleVMin");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
}

}  // namespace uking::ai
