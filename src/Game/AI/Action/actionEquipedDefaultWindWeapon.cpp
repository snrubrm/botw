#include "Game/AI/Action/actionEquipedDefaultWindWeapon.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EquipedDefaultWindWeapon::EquipedDefaultWindWeapon(const InitArg& arg) : EquipedAction(arg) {}

bool EquipedDefaultWindWeapon::init_(sead::Heap* heap) {
    _40 = heap;
    return true;
}

void EquipedDefaultWindWeapon::loadParams_() {
    EquipedAction::loadParams_();
    getStaticParam(&mWindRadius_s, "WindRadius");
    getStaticParam(&mWindRadiusLarge_s, "WindRadiusLarge");
    getStaticParam(&mWindSpeed_s, "WindSpeed");
    getStaticParam(&mWindSpeedLarge_s, "WindSpeedLarge");
    getStaticParam(&mWindSpeedRate1_s, "WindSpeedRate1");
    getStaticParam(&mWindSpeedRate2_s, "WindSpeedRate2");
    getStaticParam(&mWindSpeedRate3_s, "WindSpeedRate3");
    getStaticParam(&mWindLength_s, "WindLength");
    getStaticParam(&mCapsuleMaxSpeed_s, "CapsuleMaxSpeed");
    getStaticParam(&mWindReduceRate_s, "WindReduceRate");
    getStaticParam(&mWindReduceRateLarge_s, "WindReduceRateLarge");
    getStaticParam(&mWindFlyingDist_s, "WindFlyingDist");
    getStaticParam(&mWindFlyingDistLarge_s, "WindFlyingDistLarge");
    getStaticParam(&mWindFlyingDistRate1_s, "WindFlyingDistRate1");
    getStaticParam(&mWindFlyingDistRate2_s, "WindFlyingDistRate2");
    getStaticParam(&mWindFlyingDistRate3_s, "WindFlyingDistRate3");
}

// NON_MATCHING: the original tests `(type | 2) == 2` first and `type != 2` afterwards; clang folds
// them here and tests `type == 2` first
void EquipedDefaultWindWeapon::calc_() {
    EquipedAction::calc_();

    bool trigger = false;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        if (weapon->_c4c) {
            const s32 type = weapon->_c20._0;
            if ((type | 2) == 2) {
                if (type != 2 && !weapon->_d09)
                    trigger = true;
            }
        }
    }
    if (!trigger) {
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (weapon && weapon->_af8._0 == 9)
            trigger = true;
    }
    if (trigger) {
        m36(true);
        m37();
    }
}

}  // namespace uking::action
