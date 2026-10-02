#include "Game/AI/AI/aiStalEnemyReaction.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

StalEnemyReaction::StalEnemyReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

StalEnemyReaction::~StalEnemyReaction() = default;

bool StalEnemyReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void StalEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void StalEnemyReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void StalEnemyReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void StalEnemyReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

void StalEnemyReaction::m40(ksys::act::ai::InlineParamPack* params) {
    sub_71005D7014(mActor);
    changeChild("ふっとび", params);
}

}  // namespace uking::ai
