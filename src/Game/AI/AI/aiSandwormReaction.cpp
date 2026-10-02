#include "Game/AI/AI/aiSandwormReaction.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

SandwormReaction::SandwormReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

SandwormReaction::~SandwormReaction() = default;

bool SandwormReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void SandwormReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
    sub_71007A3800(mActor);
}

void SandwormReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void SandwormReaction::leave_() {
    EnemyDefaultReaction::leave_();
    sub_71007A397C(mActor);
}

void SandwormReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
