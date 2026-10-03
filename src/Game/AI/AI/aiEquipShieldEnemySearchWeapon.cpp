#include "Game/AI/AI/aiEquipShieldEnemySearchWeapon.h"

namespace uking::ai {

EquipShieldEnemySearchWeapon::EquipShieldEnemySearchWeapon(const InitArg& arg)
    : UnarmedEnemySearchWeapon(arg) {}

EquipShieldEnemySearchWeapon::~EquipShieldEnemySearchWeapon() = default;

void EquipShieldEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    _6e8 = false;
    UnarmedEnemySearchWeapon::enter_(params);
}

void EquipShieldEnemySearchWeapon::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("盾捨て")) {
            m45();
            return;
        }
    }
    if (_6e8) {
        child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (isCurrentChild("見まわす"))
                setFinished();
        }
    } else {
        UnarmedEnemySearchWeapon::calc_();
    }
}

void EquipShieldEnemySearchWeapon::m44() {
    if (isCurrentChild("盾捨て"))
        UnarmedEnemySearchWeapon::m44();
    else
        changeChild("盾捨て");
}

void EquipShieldEnemySearchWeapon::m45() {
    if (isCurrentChild("見まわす")) {
        UnarmedEnemySearchWeapon::m45();
    } else {
        _6e8 = true;
        sub_71004B5FB8();
    }
}

void EquipShieldEnemySearchWeapon::leave_() {
    UnarmedEnemySearchWeapon::leave_();
}

void EquipShieldEnemySearchWeapon::loadParams_() {
    UnarmedEnemySearchWeapon::loadParams_();
}

}  // namespace uking::ai
