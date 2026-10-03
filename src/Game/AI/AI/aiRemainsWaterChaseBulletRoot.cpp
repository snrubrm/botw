#include "Game/AI/AI/aiRemainsWaterChaseBulletRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

RemainsWaterChaseBulletRoot::RemainsWaterChaseBulletRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
RemainsWaterChaseBulletRoot::~RemainsWaterChaseBulletRoot() {
    ;
}

bool RemainsWaterChaseBulletRoot::init_(sead::Heap* heap) {
    mActor->sub_71011D0204(0x40);
    _3c = false;
    return true;
}

void RemainsWaterChaseBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterChaseBulletRoot::leave_() {
    sub_710054AAD8();
}

void RemainsWaterChaseBulletRoot::loadParams_() {
    getStaticParam(&mAtkMinDamage_s, "AtkMinDamage");
    getStaticParam(&mCheckPower_s, "CheckPower");
    getStaticParam(&mHighDamageAddSpd_s, "HighDamageAddSpd");
    getStaticParam(&mLowDamageAddSpd_s, "LowDamageAddSpd");
    getStaticParam(&mShootAddSpd_s, "ShootAddSpd");
    getStaticParam(&mResetASName_s, "ResetASName");
}

void RemainsWaterChaseBulletRoot::sub_710054AAD8() {
    auto* actor = mActor;
    sub_71007A2D7C(actor, "BulletAtk");
    sub_71007A3634(actor, "BulletTgt");
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(*sub_71007A2548())) {
            if (auto* body = set->findBodyByHavokName("PlayerSensor"))
                body->removeFromWorld();
        }
    }
}

}  // namespace uking::ai
