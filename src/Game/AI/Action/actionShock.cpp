#include "Game/AI/Action/actionShock.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

Shock::Shock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void Shock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Shock::leave_() {
    ksys::act::ai::Action::leave_();
}

// NON_MATCHING: register allocation only (the original keeps `this + 0x20` and the SafeString vtable in the
// callee-saved registers x20 / x21 because the first getter is not the one with the lowest offset).
void Shock::loadParams_() {
    getStaticParam(&mHitImpactForce_s, "HitImpactForce");
    getStaticParam(&mVelReduce_s, "VelReduce");
    getStaticParam(&mKnockBackTime_s, "KnockBackTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASSlot_s, "ASSlot");
}

void Shock::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (_68.value <= sead::Mathf::epsilon()) {
        controller->sub_7100F5E7F0(0.0f);
        sub_7100738660(controller, *mVelReduce_s);
    } else {
        sub_71007377D4(controller, *mVelReduce_s);
        sub_7100738660(controller, *mVelReduce_s);
        _68.update();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

bool Shock::isFinished() const {
    return ksys::act::ai::Action::isFinished() || isFinishedAS(*mASSlot_s, 0);
}

bool Shock::m32() {
    if (*mWeaponIdx_s >= 0) {
        auto* actor = mActor;
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
            return enemy->m170();
    }
    return false;
}

void Shock::m33(const sead::Vector3f* velocity) {
    playerOrEnemyDropWeapon(mActor, velocity, *mWeaponIdx_s, true, false, nullptr, false);
}

}  // namespace uking::action
