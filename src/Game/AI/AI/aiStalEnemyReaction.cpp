#include "Game/AI/AI/aiStalEnemyReaction.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

StalEnemyReaction::StalEnemyReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

StalEnemyReaction::~StalEnemyReaction() = default;

bool StalEnemyReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void StalEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(2);
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

// NON_MATCHING: the original keeps the first isCurrentChild result in a (dead) register and folds
// `!isFinished && !isFailed` into a value before the life test; same control flow
bool StalEnemyReaction::m37() {
    if (isCurrentChild("ふっとび") || isCurrentChild("突風")) {
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed()) {
            auto* life = mActor->getLife();
            if (life && *life < 1)
                return true;
        }
    }
    return EnemyDefaultReaction::m37();
}

void StalEnemyReaction::m40(ksys::act::ai::InlineParamPack* params) {
    sub_71005D7014(mActor);
    changeChild("ふっとび", params);
}

}  // namespace uking::ai
