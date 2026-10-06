#include "Game/AI/Action/actionRemainsWaterChaseBulletFall.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

RemainsWaterChaseBulletFall::RemainsWaterChaseBulletFall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterChaseBulletFall::~RemainsWaterChaseBulletFall() = default;

bool RemainsWaterChaseBulletFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWaterChaseBulletFall::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = ksys::Timer(*mEndTimer_s, *mEndTimer_s);
    if (auto* body = mActor->getMainBody()) {
        _4c = body->isFlag100000Set();
        body->setFlag100000();
        const sead::Vector3f velocity = sub_7100232D60();
        body->setLinearVelocity(velocity);
    }
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
}

void RemainsWaterChaseBulletFall::leave_() {
    if (auto* body = mActor->getMainBody())
        body->changeFlag100000(_4c);
}

void RemainsWaterChaseBulletFall::loadParams_() {
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mSetVelocity_s, "SetVelocity");
    getStaticParam(&mSetVelocityFromWeapon_s, "SetVelocityFromWeapon");
}

sead::Vector3f RemainsWaterChaseBulletFall::sub_7100232D60() const {
    sead::Vector3f velocity = sead::Vector3f::ey * *mSetVelocity_s;
    if (auto* manager = sub_710072BA90(mActor)) {
        // Both results are discarded in the original.
        manager->getField54();
        manager->getField50();
        if (manager->getField50() == 0 || manager->getField50() == 2 || manager->getField50() == 1)
            velocity = sead::Vector3f::ey * *mSetVelocityFromWeapon_s;
    }
    return velocity * 30.0f;
}

void RemainsWaterChaseBulletFall::calc_() {
    if (_40.value <= sead::Mathf::epsilon())
        return;
    _40.update();
}

bool RemainsWaterChaseBulletFall::isFinished() const {
    auto* actor = mActor;
    if (isBgGroundHit(actor, false))
        return true;

    const f32 depth_threshold = *mInWaterDepth_s;
    if (depth_threshold >= 0.0f) {
        f32 depth = 0.0f;
        if (actor->get68f().load()) {
            const f32 y = actor->getMtx().m[1][3];
            depth = actor->get6f0() - y;
        }
        if (depth >= depth_threshold)
            return true;
    }

    if (*mEndTimer_s > 0.0f && _40.value <= sead::Mathf::epsilon())
        return true;
    return false;
}

}  // namespace uking::action
