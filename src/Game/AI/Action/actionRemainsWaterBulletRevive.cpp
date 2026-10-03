#include "Game/AI/Action/actionRemainsWaterBulletRevive.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

RemainsWaterBulletRevive::RemainsWaterBulletRevive(const InitArg& arg)
    : RemainsWaterBulletWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
RemainsWaterBulletRevive::~RemainsWaterBulletRevive() {
    ;
}

bool RemainsWaterBulletRevive::init_(sead::Heap* heap) {
    return RemainsWaterBulletWait::init_(heap);
}

void RemainsWaterBulletRevive::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsWaterBulletWait::enter_(params);
}

void RemainsWaterBulletRevive::leave_() {
    RemainsWaterBulletWait::leave_();
    auto* actor = mActor;
    sub_710072BEC4(actor, nullptr, false);
    if (auto* body = actor->getMainBody())
        body->setContactNone();
}

void RemainsWaterBulletRevive::loadParams_() {
    RemainsWaterBulletWait::loadParams_();
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void RemainsWaterBulletRevive::calc_() {
    RemainsWaterBulletWait::calc_();
}

bool RemainsWaterBulletRevive::isFinished() const {
    return mFlags.isOn(Flag::Finished) || !_c0.sub_7101241B6C();
}

}  // namespace uking::action
