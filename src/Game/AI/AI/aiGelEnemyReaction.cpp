#include "Game/AI/AI/aiGelEnemyReaction.h"
#include "Game/AI/aiUnk_71006F5B14.h"
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

void GelEnemyReaction::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        const int element = sub_71006F5694(mActor);
        if (element != 0 && !sub_71006F594C(element, mActor->getChemicalStuff())) {
            if (!isCurrentChild("ケミカル鎮静") && !isCurrentChild("死亡")) {
                changeChild("ケミカル鎮静");
                return;
            }
        }
    } else {
        child->isChangeable();
    }
    EnemyDefaultReaction::calc_();
}

void GelEnemyReaction::leave_() {
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor))
        gel->_1678 &= ~1;
    EnemyDefaultReaction::leave_();
}

bool GelEnemyReaction::m36(int damage_type) {
    switch (damage_type) {
    case -1:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return false;
    default:
        changeChild("小ダメージ");
        return true;
    }
}

void GelEnemyReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
}

}  // namespace uking::ai
