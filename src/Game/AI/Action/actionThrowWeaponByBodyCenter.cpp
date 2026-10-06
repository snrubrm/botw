#include "Game/AI/Action/actionThrowWeaponByBodyCenter.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ThrowWeaponByBodyCenter::ThrowWeaponByBodyCenter(const InitArg& arg) : ThrowWeapon(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ThrowWeaponByBodyCenter::~ThrowWeaponByBodyCenter() {
    ;
}

bool ThrowWeaponByBodyCenter::init_(sead::Heap* heap) {
    return ThrowWeapon::init_(heap);
}

void ThrowWeaponByBodyCenter::enter_(ksys::act::ai::InlineParamPack* params) {
    ThrowWeapon::enter_(params);
}

void ThrowWeaponByBodyCenter::leave_() {
    ThrowWeapon::leave_();
}

void ThrowWeaponByBodyCenter::loadParams_() {
    ThrowWeapon::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ThrowWeaponByBodyCenter::calc_() {
    ThrowWeapon::calc_();
}

void ThrowWeaponByBodyCenter::m32(sead::Vector3f* pos, uking::act::Enemy* enemy, int weapon_idx) {
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(
            enemy->_c38[weapon_idx].getProc(nullptr, mActor))) {
        if (auto* body = weapon->getMainBody()) {
            sead::BoundBox3f aabb;
            body->getAabbInWorld(&aabb);
            aabb.getCenter(pos);
            return;
        }
    }
    ThrowWeapon::m32(pos, enemy, weapon_idx);
}

void ThrowWeaponByBodyCenter::m33() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
