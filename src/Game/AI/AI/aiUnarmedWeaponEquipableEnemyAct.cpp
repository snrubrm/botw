#include "Game/AI/AI/aiUnarmedWeaponEquipableEnemyAct.h"
#include <cmath>

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

bool UnarmedWeaponEquipableEnemyAct::m43(sead::Vector3f* out) {
    if (getStateMaybe() == 1) {
        sead::Vector3f a;
        sead::Vector3f b;
        if (sub_71004B6370(&a) && sub_71004B62FC(&b)) {
            const f32 dx = a.x - b.x;
            const f32 dz = a.z - b.z;
            if (std::sqrt(dx * dx + dz * dz) >= getReachDistanceMaybe())
                return false;
        }
    }
    return UnarmedEnemySearch::m43(out);
}

void UnarmedWeaponEquipableEnemyAct::m44() {
    if (!isCurrentChild("見まわす"))
        changeToLookAround();
}

void UnarmedWeaponEquipableEnemyAct::m45() {
    changeToLookAround();
    _6e8 = true;
}

}  // namespace uking::ai
