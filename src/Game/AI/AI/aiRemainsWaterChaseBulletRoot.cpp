#include "Game/AI/AI/aiRemainsWaterChaseBulletRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

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

bool RemainsWaterChaseBulletRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000b6) {
        mActor->sub_71011D0204(0x80);
        return true;
    }
    if (message->getType() == 0x80000b7) {
        mActor->sub_71011D0228(0x80);
        return true;
    }
    if (message->getType() == 0x8000004) {
        _39 = true;
        return true;
    }
    if (message->getType() == 0x800006b) {
        _3a = true;
        return true;
    }
    if (message->getType() == 0x3000003) {
        if (auto* body = mActor->getMainBody())
            body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    } else if (message->getType() == 0x3000004) {
        if (auto* body = mActor->getMainBody())
            body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    }
    return false;
}

void RemainsWaterChaseBulletRoot::loadParams_() {
    getStaticParam(&mParams.mAtkMinDamage_s, "AtkMinDamage");
    getStaticParam(&mParams.mCheckPower_s, "CheckPower");
    getStaticParam(&mParams.mHighDamageAddSpd_s, "HighDamageAddSpd");
    getStaticParam(&mParams.mLowDamageAddSpd_s, "LowDamageAddSpd");
    getStaticParam(&mParams.mShootAddSpd_s, "ShootAddSpd");
    getStaticParam(&mParams.mResetASName_s, "ResetASName");
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
