#include "Game/AI/AI/aiStalGiantEnemyReaction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

StalGiantEnemyReaction::StalGiantEnemyReaction(const InitArg& arg) : ForestGiantReaction(arg) {}

StalGiantEnemyReaction::~StalGiantEnemyReaction() = default;

bool StalGiantEnemyReaction::init_(sead::Heap* heap) {
    return ForestGiantReaction::init_(heap);
}

void StalGiantEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ForestGiantReaction::enter_(params);
}

void StalGiantEnemyReaction::calc_() {
    ForestGiantReaction::calc_();
}

void StalGiantEnemyReaction::leave_() {
    ForestGiantReaction::leave_();
}

void StalGiantEnemyReaction::loadParams_() {
    ForestGiantReaction::loadParams_();
}

bool StalGiantEnemyReaction::m37() {
    if (isCurrentChild("ふっとび")) {
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed()) {
            auto* life = mActor->getLife();
            if (life && *life < 1)
                return true;
        }
    }
    return EnemyDefaultReaction::m37();
}

}  // namespace uking::ai
