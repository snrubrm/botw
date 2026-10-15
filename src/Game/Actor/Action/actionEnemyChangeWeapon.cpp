#include "Game/Actor/Action/actionEnemyChangeWeapon.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/XLink/xlinkXLink.h"

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
        ksys::act::ActorLinkConstDataAccess accessor;
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

void EnemyChangeWeapon::sub_7100106AF8() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    auto& link = enemy->_c38[_74];
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&link, &accessor) || !accessor.isStateCalc())
        return;
    // The original performs this runtime query and discards its result.
    sead::DynamicCast<act::Weapon>(link.getProc(nullptr, nullptr));
    // The native equip request bypasses Enemy's override.
    if (enemy->PlayerOrEnemy::m164(
            0, sead::DynamicCast<act::Weapon>(link.getProc(nullptr, nullptr)), false, false)) {
        if (auto* weapon = enemy->getWeapons()->getEquippedWeapon(0)) {
            weapon->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            weapon->getXLink()->setMask(ksys::xlink::XLink::MaskBit::_1);
            setFinished();
            _78 = 0;
        }
    }
}

}  // namespace uking::action
