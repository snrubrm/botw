#include "Game/AI/AI/aiUnarmedWeaponEquipableEnemyAct.h"

namespace uking::ai {

UnarmedWeaponEquipableEnemyAct::UnarmedWeaponEquipableEnemyAct(const InitArg& arg)
    : UnarmedEnemySearchWeapon(arg) {}

UnarmedWeaponEquipableEnemyAct::~UnarmedWeaponEquipableEnemyAct() = default;

bool UnarmedWeaponEquipableEnemyAct::init_(sead::Heap* heap) {
    return UnarmedEnemySearchWeapon::init_(heap);
}

void UnarmedWeaponEquipableEnemyAct::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearchWeapon::enter_(params);
    _6e8 = false;
}

void UnarmedWeaponEquipableEnemyAct::calc_() {
    if (!_6e8)
        UnarmedEnemySearchWeapon::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("見まわす"))
            setFinished();
    }
}

void UnarmedWeaponEquipableEnemyAct::leave_() {
    UnarmedEnemySearchWeapon::leave_();
}

void UnarmedWeaponEquipableEnemyAct::loadParams_() {
    UnarmedEnemySearchWeapon::loadParams_();
}

}  // namespace uking::ai
