#include "Game/AI/Action/actionRemainsWaterBulletAction.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

RemainsWaterBulletAction::RemainsWaterBulletAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterBulletAction::~RemainsWaterBulletAction() = default;

bool RemainsWaterBulletAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
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
