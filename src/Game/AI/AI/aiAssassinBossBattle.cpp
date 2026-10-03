#include "Game/AI/AI/aiAssassinBossBattle.h"

namespace uking::ai {

AssassinBossBattle::AssassinBossBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
AssassinBossBattle::~AssassinBossBattle() {
    ;
}

bool AssassinBossBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinBossBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool AssassinBossBattle::handleMessage_(const ksys::Message& message) {
    return false;
}

void AssassinBossBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBossBattle::loadParams_() {
    getStaticParam(&mRetFrmDmgAtkTimer_s, "RetFrmDmgAtkTimer");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
    getStaticParam(&mHomeDist_s, "HomeDist");
    getStaticParam(&mBattleDist_s, "BattleDist");
    getStaticParam(&mDyingLifeRatio_s, "DyingLifeRatio");
    getStaticParam(&mBattleDistSecond_s, "BattleDistSecond");
    getStaticParam(&mAnchorName_s, "AnchorName");
    getStaticParam(&mReturnHeight_s, "ReturnHeight");
}

}  // namespace uking::ai
