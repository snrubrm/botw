#include "Game/AI/AI/aiGolemNormal.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

GolemNormal::GolemNormal(const InitArg& arg) : EnemyNormal(arg) {}

GolemNormal::~GolemNormal() = default;

bool GolemNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void GolemNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void GolemNormal::leave_() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e90 = 4;
    EnemyNormal::leave_();
}

void GolemNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

}  // namespace uking::ai
