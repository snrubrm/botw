#include "Game/AI/AI/aiGelEnemyReaction.h"
#include "Game/Actor/actGelEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

GelEnemyReaction::GelEnemyReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

GelEnemyReaction::~GelEnemyReaction() = default;

bool GelEnemyReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void GelEnemyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor))
        gel->_1678 |= 1;

    if (!m37())
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    auto& weapon = enemy->getActorPartsActor("EatWeapon");
    if (!weapon.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&weapon, &accessor);
    const sead::Vector3f vel(0, 0.2f, 0);
    accessor.setProperties(mActor->getMtx(), &vel, nullptr, nullptr, false, 0, -1);
}

void GelEnemyReaction::leave_() {
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor))
        gel->_1678 &= ~1;
    EnemyDefaultReaction::leave_();
}

void GelEnemyReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
