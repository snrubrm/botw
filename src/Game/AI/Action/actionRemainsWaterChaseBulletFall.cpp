#include "Game/AI/Action/actionRemainsWaterChaseBulletFall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

RemainsWaterChaseBulletFall::RemainsWaterChaseBulletFall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterChaseBulletFall::~RemainsWaterChaseBulletFall() = default;

bool RemainsWaterChaseBulletFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWaterChaseBulletFall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsWaterChaseBulletFall::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWaterChaseBulletFall::loadParams_() {
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mSetVelocity_s, "SetVelocity");
    getStaticParam(&mSetVelocityFromWeapon_s, "SetVelocityFromWeapon");
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
