#include "Game/AI/AI/aiWeaponTrueFormSelect.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WeaponTrueFormSelect::WeaponTrueFormSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponTrueFormSelect::~WeaponTrueFormSelect() = default;

bool WeaponTrueFormSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponTrueFormSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (weapon && weapon->isTrueFormMasterSword())
        changeChild("真の姿");
    else
        changeChild("仮の姿");
}

void WeaponTrueFormSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;

    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (weapon && weapon->isTrueFormMasterSword()) {
        if (!isCurrentChild("真の姿"))
            changeChild("真の姿");
    } else if (!isCurrentChild("仮の姿")) {
        changeChild("仮の姿");
    }
}

void WeaponTrueFormSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponTrueFormSelect::loadParams_() {}

}  // namespace uking::ai
