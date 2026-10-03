#include "Game/AI/AI/aiAssassinBattleRange.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinBattleRange::AssassinBattleRange(const InitArg& arg) : EnemyBattle(arg) {}

AssassinBattleRange::~AssassinBattleRange() = default;

bool AssassinBattleRange::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AssassinBattleRange::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    _b8 = *mScapeGoatCheckInterval_s;
    _bc = *mServiceCheckInterval_s;
}

void AssassinBattleRange::leave_() {
    EnemyBattle::leave_();
}

void AssassinBattleRange::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mScapeGoatCheckInterval_s, "ScapeGoatCheckInterval");
    getStaticParam(&mServiceCheckInterval_s, "ServiceCheckInterval");
    getStaticParam(&mServicePer_s, "ServicePer");
    getStaticParam(&mScapeGoatPer_s, "ScapeGoatPer");
    getStaticParam(&mServiceDist_s, "ServiceDist");
}

bool AssassinBattleRange::isChangeable() const {
    if (isCurrentChild("戦闘攻撃") || isCurrentChild("変わり身"))
        return false;
    return getCurrentChild()->isChangeable();
}

bool AssassinBattleRange::sub_7100313B64() {
    if (sead::GlobalRandom::instance()->getF32() * 100.0f < *mScapeGoatPer_s) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("変わり身", &pack);
        return true;
    }
    _b8 = *mScapeGoatCheckInterval_s;
    return false;
}

}  // namespace uking::ai
