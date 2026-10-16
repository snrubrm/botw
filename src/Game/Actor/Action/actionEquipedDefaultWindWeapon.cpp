#include "Game/Actor/Action/actionEquipedDefaultWindWeapon.h"
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
// NON_MATCHING: case order / pointer loads of the attack count rate and the base speed load timing.
f32 EquipedDefaultWindWeapon::getWindSpeedRate() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return *mWindSpeed_s * 30.0f;

    f32 speed = *mWindSpeed_s;
    u32 flags;
    if ((weapon->_af8._0 | 1) == 7)
        flags = weapon->_af8._4;
    else if (weapon->_d08)
        flags = weapon->_cf4;
    else
        flags = weapon->_c20._4;
    if (flags & 6) {
        speed = *mWindSpeedLarge_s;
        f32 rate = 1.0f;
        if (auto* w = sead::DynamicCast<act::Weapon>(mActor)) {
            const s32 count = w->_c4c ? w->_c20._24 : w->_d14;
            switch (count) {
            case 2:
                rate = *mWindSpeedRate1_s;
                break;
            case 3:
                rate = *mWindSpeedRate2_s;
                break;
            case 4:
                rate = *mWindSpeedRate3_s;
                break;
            }
        }
        speed *= rate;
    }
    return speed * 30.0f;
}

// NON_MATCHING: the original loads each rate pointer per case and dereferences once (4 / 3 / 2 order).
f32 EquipedDefaultWindWeapon::getWindFlyingDist() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return *mWindFlyingDist_s;

    f32 dist = *mWindFlyingDist_s;
    u32 flags;
    if ((weapon->_af8._0 | 1) == 7)
        flags = weapon->_af8._4;
    else if (weapon->_d08)
        flags = weapon->_cf4;
    else
        flags = weapon->_c20._4;
    if (flags & 6) {
        dist = *mWindFlyingDistLarge_s;
        f32 rate = 1.0f;
        if (auto* w = sead::DynamicCast<act::Weapon>(mActor)) {
            const s32 count = w->_c4c ? w->_c20._24 : w->_d14;
            switch (count) {
            case 2:
                rate = *mWindFlyingDistRate1_s;
                break;
            case 3:
                rate = *mWindFlyingDistRate2_s;
                break;
            case 4:
                rate = *mWindFlyingDistRate3_s;
                break;
            }
        }
        dist *= rate;
    }
    return dist;
}

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
