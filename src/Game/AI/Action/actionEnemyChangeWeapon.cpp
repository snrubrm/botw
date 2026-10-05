#include "Game/AI/Action/actionEnemyChangeWeapon.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

EnemyChangeWeapon::EnemyChangeWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyChangeWeapon::~EnemyChangeWeapon() = default;

bool EnemyChangeWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyChangeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    _74 = *mEquipWeaponBufIndex_a;
    _78 = 1;
}

// NON_MATCHING: the runtime cast keeps a null check and actor-link loads are scheduled later.
void EnemyChangeWeapon::leave_() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy->getWeapons()->getEquippedWeapon(0) && _74 != -1) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&enemy->_c38[_74], &accessor))
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void EnemyChangeWeapon::loadParams_() {
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void EnemyChangeWeapon::calc_() {
    if (!isFinished() && !isFailed()) {
        switch (_78) {
        case 1:
            sub_71001066EC();
            break;
        case 2:
            sub_71001068DC();
            break;
        case 3:
            sub_7100106AF8();
            break;
        }
    }
    sub_7100106D24(_70);
    sub_7100106D24(_74);
}

}  // namespace uking::action
