#include "Game/AI/Action/actionShock.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

Shock::Shock(const InitArg& arg) : ksys::act::ai::Action(arg) {}

// NON_MATCHING: same instructions except the order of the three stores of `drop_velocity` (the
// original stores x, z, then y = 0 after the length computation) and `fadd z*z, x*x + y*y` (the
// original's operand order is flipped)
void Shock::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    sead::Vector3f impulse = mActor->getVelocity();
    if (hasAttackInfo(mActor)) {
        const auto* info = getAttackInfo(mActor, 0);
        impulse += info->_c * *mHitImpactForce_s;
    } else if (auto* damage_mgr = sub_710072BA90(mActor)) {
        sead::Vector3f hit_dir;
        sub_71005E242C(&hit_dir, mActor, damage_mgr);
        impulse += hit_dir * *mHitImpactForce_s;
    }

    ksys::util::sub_71011EFA00(&impulse, impulse, getUpDir(mActor));
    sead::Vector3f dir = impulse;
    dir.normalize();
    sub_710072C1B4(controller, dir);

    if (m32()) {
        sead::Vector3f drop_velocity;
        if (!(*mWeaponDropSpeedXZ_s <= sead::Mathf::epsilon() &&
              *mWeaponDropSpeedXZ_s >= -sead::Mathf::epsilon())) {
            sead::Vector3f front;
            mActor->getMtx().getBase(front, 2);
            drop_velocity = sead::Vector3f(-front.x, 0, -front.z);
            const f32 length = drop_velocity.length();
            if (length > 0.0f)
                drop_velocity *= *mWeaponDropSpeedXZ_s / length;
        } else {
            drop_velocity.x = 0;
            drop_velocity.z = 0;
        }
        drop_velocity.y = *mWeaponDropSpeedY_s;
        m33(&drop_velocity);
    }

    playAS(mASName_s.cstr(), false, *mASSlot_s, 0, -1.0f);
    _68.reset(f32(*mKnockBackTime_s));
    mFlags.set(Flag::Changeable);
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
