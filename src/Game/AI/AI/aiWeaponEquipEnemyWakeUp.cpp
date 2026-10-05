#include "Game/AI/AI/aiWeaponEquipEnemyWakeUp.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

WeaponEquipEnemyWakeUp::WeaponEquipEnemyWakeUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipEnemyWakeUp::~WeaponEquipEnemyWakeUp() = default;

bool WeaponEquipEnemyWakeUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponEquipEnemyWakeUp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_71000198E4(sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr)));
    }
    changeChild("起きる", nullptr);
}

void WeaponEquipEnemyWakeUp::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019C58(sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr)));
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mWeaponIdx_s));
    }
}

void WeaponEquipEnemyWakeUp::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mWeaponGetRange_s, "WeaponGetRange");
}

}  // namespace uking::ai
