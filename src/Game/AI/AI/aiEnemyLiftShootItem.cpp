#include "Game/AI/AI/aiEnemyLiftShootItem.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyLiftShootItem::EnemyLiftShootItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyLiftShootItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLiftShootItem::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710039760C();
}

void EnemyLiftShootItem::leave_() {
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
}

void EnemyLiftShootItem::loadParams_() {
    getStaticParam(&mShootAngle_s, "ShootAngle");
    getStaticParam(&mShootDist_s, "ShootDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mShootItem_d, "ShootItem");
}

}  // namespace uking::ai
