#include "Game/Actor/Action/actionCatch.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

Catch::Catch(const InitArg& arg) : ActionEx(arg) {}

// NON_MATCHING: normalized up-vector stores and paired speed stores differ.
void Catch::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    ksys::act::ActorLinkConstDataAccess weapon;
    ksys::act::acquireActor(mTargetWeapon_d, &weapon);
    mActor->getASList()->goLimpFromHeadShotMaybe(44, weapon.getProfile(), 0);

    const sead::Vector3f gravity = controller->get70();
    const f32 gravity_length = gravity.length();
    sead::Vector3f up = -gravity;
    if (gravity_length > 0.0f)
        up *= 1.0f / gravity_length;
    if (gravity_length < sead::Mathf::epsilon())
        up = sead::Vector3f::ey;
    m32();

    sead::Vector3f velocity = mActor->getVelocity();
    ksys::util::sub_71011EFA00(&velocity, velocity, up);
    const f32 speed = velocity.normalize();
    _6c.value = speed;
    _6c.prev_value = speed;
    sub_710072C1B4(controller, velocity);
    const f32 angular_speed = mActor->getAngVelocity().length();
    _78.value = angular_speed;
    _78.prev_value = angular_speed;
    sub_7100741034(&_48, mActor);
    _84 = false;
    _85 = false;
}

void Catch::leave_() {
    ActionEx::leave_();
}

void Catch::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: up-vector stores, caught-state branch merging and speed stores differ.
void Catch::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _6c *= 0.65f;
    _6c.updateStats();
    controller->sub_7100F5E7F0(_6c.value * 30.0f);
    auto* target = sead::DynamicCast<ksys::act::Actor>(mTargetWeapon_d->getProc(nullptr, nullptr));
    if (target && !_84) {
        sub_7100741038(&_48, mActor);
        const sead::Vector3f gravity = controller->get70();
        const f32 gravity_length = gravity.length();
        sead::Vector3f up = -gravity;
        if (gravity_length > 0.0f)
            up *= 1.0f / gravity_length;
        if (gravity_length < sead::Mathf::epsilon())
            up = sead::Vector3f::ey;
        ksys::act::ActorLinkConstDataAccess weapon_access;
        ksys::act::acquireActor(mTargetWeapon_d, &weapon_access);
        sead::Vector3f direction = weapon_access.getActorMtx().getTranslation() -
                                   mActor->getMtx().getTranslation();
        ksys::util::sub_71011EFA00(&direction, direction, up);
        direction.normalize();
        _78.lerp(*mRotSpd_s, 0.12f);
        _78.updateStats();
        sub_7100741578(&_48, direction, up, true, 0.12f, _78.value, _78.value * 0.1f);
        sub_71007419F4(_48, controller);
        auto* as_list = mActor->getASList();
        if (!as_list) {
            setFailed();
        } else if (as_list->x(69, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            bool caught = false;
            if (target->getState() != ksys::act::BaseProc::State::Sleep) {
                if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(target)) {
                    if (!sub_71005DEC08(mTargetWeapon_d, mActor, 999.0f, 999.0f, sead::Mathf::pi()) &&
                        !weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
                        caught = sub_71005D8A30(mActor, weapon, *mWeaponIdx_s);
                    }
                }
            }
            _85 = caught;
            const f32 angular_speed = mActor->getAngVelocity().length();
            _78.value = angular_speed;
            _78.prev_value = angular_speed;
            _84 = true;
        }
    } else {
        sub_7100738660(controller, target ? 0.8f : 0.65f);
    }
    if (isFinishedAS(0, 0)) {
        if (_85)
            setFinished();
        else
            setFailed();
    }
}

void Catch::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
