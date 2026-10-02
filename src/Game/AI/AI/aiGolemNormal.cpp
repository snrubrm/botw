#include "Game/AI/AI/aiGolemNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
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

void GolemNormal::m34() {
    if (mActor->getRootAi()->getI() == 5)
        EnemyNormal::m34();
    else
        changeChild("初期待機");
}

void GolemNormal::m37() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    EnemyNormal::m37();
}

void GolemNormal::m38() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    EnemyNormal::m38();
}

s32 GolemNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 9, 1, 2, 3, 4, 5, 6, 7, 8};
    return sTable[idx];
}

void GolemNormal::m58(s32 a1) {
    if (a1 == 9)
        m40();
}

bool GolemNormal::m54() {
    if (EnemyNormal::m54())
        return true;
    return isCurrentChild("初期待機");
}

}  // namespace uking::ai
