#include "Game/AI/AI/aiGanonWeaponAttackOnFloor.h"

namespace uking::ai {

GanonWeaponAttackOnFloor::GanonWeaponAttackOnFloor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonWeaponAttackOnFloor::~GanonWeaponAttackOnFloor() = default;

bool GanonWeaponAttackOnFloor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonWeaponAttackOnFloor::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003F1E0C();
}

void GanonWeaponAttackOnFloor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonWeaponAttackOnFloor::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool GanonWeaponAttackOnFloor::isFinished() const {
    if (isCurrentChild("攻撃")) {
        auto* child = getCurrentChild();
        if (child->isFinished())
            return true;
        if (child->isFailed())
            return true;
    }
    return false;
}

}  // namespace uking::ai
