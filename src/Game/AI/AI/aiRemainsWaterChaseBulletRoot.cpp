#include "Game/AI/AI/aiRemainsWaterChaseBulletRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
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
    if (auto* body = mActor->getMainBody())
        body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    auto* actor = mActor;
    _39 = false;
    _3a = false;
    _3b = false;
    sub_71007A458C(actor, true);
    actor->sub_71011D0228(0x80);
    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        if (auto* body = set->findBodyByHavokName("BulletAtk"))
            body->enableContactLayer(ksys::phys::ContactLayer::SensorPlayer);
    }
    if (auto* sensor = getActorAttackSensor(actor)) {
        sensor->activateAttackSensor(
            0x2000, 8, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
            actor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f, 0,
            actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), -1,
            false, *mParams.mAtkMinDamage_s, -1);
    }

    if (_3c) {
        _3c = false;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_40, "TargetPos", -1);
        changeChild("復活", &pack);
    } else {
        sub_710054AC5C();
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
        changeChild("待機");
    }
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

void RemainsWaterChaseBulletRoot::sub_710054AC5C() {
    auto* actor = mActor;
    sub_71007A2C30(actor, "BulletAtk", nullptr);
    sub_71007A34B8(actor, "BulletTgt");
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(*sub_71007A2548())) {
            if (auto* body = set->findBodyByHavokName("PlayerSensor"))
                body->addToWorld();
        }
    }
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

// 0x7100549e90
void RemainsWaterChaseBulletRoot::sub_7100549E90() {
    if (auto* as_list = mActor->getASList()) {
        if (!mParams.mResetASName_s.isEmpty())
            as_list->startAnimationMaybe(-1.0f, -1.0f, mParams.mResetASName_s.cstr(), 0, 0, true);
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000);
    sub_710054AAD8();
    _3c = true;
    _40 = mActor->getMtx().getTranslation();
    changeChild("爆発", nullptr);
}

}  // namespace uking::ai
