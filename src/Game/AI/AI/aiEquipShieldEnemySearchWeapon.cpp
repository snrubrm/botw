#include "Game/AI/AI/aiEquipShieldEnemySearchWeapon.h"

namespace uking::ai {

EquipShieldEnemySearchWeapon::EquipShieldEnemySearchWeapon(const InitArg& arg)
    : UnarmedEnemySearchWeapon(arg) {}

EquipShieldEnemySearchWeapon::~EquipShieldEnemySearchWeapon() = default;

void EquipShieldEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    _6e8 = false;
    UnarmedEnemySearchWeapon::enter_(params);
}

void EquipShieldEnemySearchWeapon::leave_() {
    UnarmedEnemySearchWeapon::leave_();
}

void EquipShieldEnemySearchWeapon::loadParams_() {
    UnarmedEnemySearchWeapon::loadParams_();
}

void EquipShieldEnemySearchWeapon::m44() {
    if (isCurrentChild("盾捨て"))
        UnarmedEnemySearchWeapon::m44();
    else
        changeChild("盾捨て");
}

}  // namespace uking::ai
