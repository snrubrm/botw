#include "Game/AI/Action/actionRemainsWaterBulletAction.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

RemainsWaterBulletAction::RemainsWaterBulletAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterBulletAction::~RemainsWaterBulletAction() = default;

bool RemainsWaterBulletAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

f32 RemainsWaterBulletAction::sub_7100230304() {
    if (mSignASName_s.isEmpty())
        return 0.0f;
    f32 left = 1.0f;
    if (_68) {
        if (auto* as_list = mActor->getASList()) {
            const f32 total = as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
            const f32 current = as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
            if (total > 0.0f)
                left = 1.0f - sead::Mathf::clamp(current / total, 0.0f, 1.0f);
        }
    }
    return left;
}

void RemainsWaterBulletAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    const f32 time = sead::Mathf::max(*mEndTimer_s, 0.0f);
    _6c = ksys::Timer(time, time);
    _68 = false;
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    _78 = body->isFlag100000Set();
    body->changeFlag100000(*mIgnroeWater_s);
    _7c = body->getGravityFactor();
    if (*mIgnoreGravity_s)
        body->setGravityFactor(0.0f);
    else
        body->setGravityFactor(1.0f);
}

void RemainsWaterBulletAction::m33() {
    if (*mEndTimer_s > 0.0f) {
        if (!(_6c.value <= sead::Mathf::epsilon())) {
            _6c.update();
            if (!(_6c.value <= sead::Mathf::epsilon())) {
                if (!_68 && f32(*mSignASFrame_s) >= _6c.value && !mSignASName_s.isEmpty()) {
                    _68 = true;
                    playAS(mSignASName_s.cstr(), false, 0, 0, -1.0f);
                    if (auto* as_list = mActor->getASList()) {
                        const f32 total =
                            as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
                        const f32 current =
                            as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011630A4);
                        const f32 left = total - current;
                        if (left > 0.0f)
                            as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100,
                                         left / _6c.value);
                    }
                }
            }
        }
        if (_6c.value <= sead::Mathf::epsilon()) {
            if (!_68 || isFinishedAS(0, 0))
                setFailed();
        }
    }
}

void RemainsWaterBulletAction::m34() {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body)
        return;
    if (*mUseParentRevDirRot_s) {
        if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(&bullet->_bd0._0, &accessor)) {
                const sead::Vector3f parent_pos = accessor.getActorMtx().getTranslation();
                const sead::Vector3f pos = actor->getMtx().getTranslation();
                sead::Vector3f dir;
                dir.x = pos.x - parent_pos.x;
                dir.z = pos.z - parent_pos.z;
                dir.y = 0.0f;
                if (dir.length() > 0.0f) {
                    dir.normalize();
                    sead::Matrix34f mtx;
                    ksys::util::sub_71011F00EC(&mtx, dir, sead::Vector3f::ey,
                                               sead::Vector3f::zero, false);
                    body->changeRotation(mtx, sead::Mathf::epsilon());
                    return;
                }
            }
        }
    }
    f32 factor = 1.0f;
    if (*mEndTimer_s > 0.0f && !(_6c.value <= sead::Mathf::epsilon()))
        factor = sead::Mathf::clamp(1.0f - _6c.value / *mEndTimer_s, 0.0f, 1.0f);
    sead::Vector3f velocity(0.57735026f, 0.57735026f, 0.57735026f);
    velocity.rotate(actor->getMtx());
    f32 speed = factor * *mMaxRotSpd_s;
    if (speed < *mMinRotSpd_s)
        speed = *mMinRotSpd_s;
    velocity *= speed;
    body->setAngularVelocity(velocity, sead::Mathf::epsilon());
}

void RemainsWaterBulletAction::leave_() {
    if (auto* body = mActor->getMainBody()) {
        body->changeFlag100000(_78);
        body->setGravityFactor(_7c);
    }
}

void RemainsWaterBulletAction::loadParams_() {
    getStaticParam(&mSignASFrame_s, "SignASFrame");
    getStaticParam(&mMaxRotSpd_s, "MaxRotSpd");
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mIgnroeWater_s, "IgnroeWater");
    getStaticParam(&mIgnoreGravity_s, "IgnoreGravity");
    getStaticParam(&mUseParentRevDirRot_s, "UseParentRevDirRot");
    getStaticParam(&mSignASName_s, "SignASName");
}

void RemainsWaterBulletAction::calc_() {
    m32();
    m33();
    m34();
}

}  // namespace uking::action
