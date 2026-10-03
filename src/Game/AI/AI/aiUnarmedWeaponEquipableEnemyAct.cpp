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

bool UnarmedWeaponEquipableEnemyAct::m43(sead::Vector3f* out) {
    if (getStateMaybe() == 1) {
        sead::Vector3f target;
        if (sub_71004B6370(&target)) {
            sead::Vector3f pos;
            if (sub_71004B62FC(&pos)) {
                const f32 dx = target.x - pos.x;
                const f32 dz = target.z - pos.z;
                if (sead::Mathf::sqrt(dx * dx + dz * dz) >= getReachDistanceMaybe())
                    return false;
            }
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

void UnarmedWeaponEquipableEnemyAct::leave_() {
    UnarmedEnemySearchWeapon::leave_();
}

void UnarmedWeaponEquipableEnemyAct::loadParams_() {
    UnarmedEnemySearchWeapon::loadParams_();
}

}  // namespace uking::ai
