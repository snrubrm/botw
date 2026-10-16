#include "Game/Actor/Action/actionEnemyChangeWeapon.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
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

// NON_MATCHING: the Enemy cast keeps a null check before the first virtual call, and the _74 / _70 test
// before the drop request is evaluated in the opposite order.
void EnemyChangeWeapon::sub_71001066EC() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(
        enemy->getWeapons()->mWeapons[0].link.getProc(nullptr, nullptr));
    if (!weapon) {
        _70 = -1;
    } else if (!weapon->isCalc() || weapon->get920() != 0xff || weapon->get921()) {
        return;
    }

    if (enemy->_c38[0].hasProcById(weapon))
        _70 = 0;
    else
        _70 = enemy->_c38[1].hasProcById(weapon) ? 1 : -1;

    if (_74 == _70) {
        setFinished();
        _78 = 0;
        return;
    }

    if (u32(_74) >= 2 || _70 != -1) {
        if (enemy->getWeapons()->getEquippedWeapon(0))
            enemy->sub_7100007ADC(0, sUnk_71025c8d04, nullptr);
    }
    _78 = 2;
}

void EnemyChangeWeapon::sub_71001068DC() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (_70 != -1) {
        auto* weapon = sead::DynamicCast<act::Weapon>(enemy->_c38[_70].getProc(nullptr, nullptr));
        if (weapon) {
            if (weapon->isParentEqualToById(mActor))
                return;
            weapon->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }

    if (u32(_74) < 2) {
        auto& link = enemy->_c38[_74];
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&link, &accessor)) {
            sead::Matrix34f mtx;
            mtx.makeIdentity();
            mtx.setTranslation(sUnk_71025c8d04);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
        }
        _78 = 3;
    } else {
        _70 = _74;
        setFinished();
        _78 = 0;
    }
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

void EnemyChangeWeapon::sub_7100106D24(s32 index) {
    if (index == -1)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    auto* weapon = sead::DynamicCast<act::Weapon>(enemy->_c38[index].getProc(nullptr, nullptr));
    if (!weapon || weapon->isSleep() || weapon->isParentEqualToById(mActor))
        return;
    auto* body = weapon->getMainBody();
    if (!body)
        return;

    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    sead::Vector3f impulse;
    body->computeLinearVelocity(&impulse, sUnk_71025c8d04,
                                ksys::phys::TakeAngularVelocityIntoAccount(false));
    impulse -= velocity;
    impulse *= body->getMass();
    _30[index].sub_7100D3D3C4(0, &impulse, nullptr, 0);
    _30[index].sub_7100D3D40C(mActor, weapon, false);
}

}  // namespace uking::action
