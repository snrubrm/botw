#include "Game/Actor/Action/actionBombExplode.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

BombExplode::BombExplode(const InitArg& arg) : ActionEx(arg) {}

BombExplode::~BombExplode() = default;

void BombExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    if (auto* body = mActor->getMainBody()) {
        body->setContactLayerAndGroundHit(ksys::phys::ContactLayer::EntityNoHit,
                                          ksys::phys::GroundHit::HitAll);
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }

    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24D0())) {
        const int num = set->getRigidBodies().size();
        for (int i = 0; i < num; ++i) {
            if (auto* info = set->getRigidBody(i)->getContactPointInfo())
                info->unsubscribeAllLayers();
        }
    }

    ksys::act::disableAllAttClients(mActor);
    playAS("Explode", false, 0, 0, -1.0f);
    _1c = ksys::Timer(*mExplodeTime_s, *mExplodeTime_s);

    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        const int idx = set->findBodyIndexByHavokName("AtkExplode");
        if (idx >= 0) {
            _48 = sead::DynamicCast<ksys::phys::SphereRigidBody>(set->getRigidBody(idx));
            if (_48) {
            auto* sensor = getActorAttackSensor(mActor);
            const auto* attack = mActor->getParam()->getRes().mGParamList->getAttack();
            sensor->activateAttackSensor(0x10, 4, attack->mPower.ref(), attack->mImpulse.ref(), 2.0f,
                                         attack->mGuardBreakPower.ref(), 30, -1, true, 1,
                                         attack->mPowerForPlayer.ref());
            _50 = _48->getRadius();
            f32 step = _50;
            if (*mSizeUpTime_s != 0)
                step = _50 / *mSizeUpTime_s;
            _58 = step;
            _48->setTransform(mActor->getMtx());
            _54 = 0.001f;
            _48->setRadius(0.001f);
            sub_71007A2B64(_48, nullptr);
            }
        }
    }

    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, true);
}

void BombExplode::leave_() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, false);
    if (_48) {
        sub_71007A2D34(_48);
        _48 = nullptr;
    }
}

void BombExplode::loadParams_() {
    if (mActor->getParam()) {
        getStaticParam(&mSizeUpTime_s, "SizeUpTime");
        getStaticParam(&mExplodeTime_s, "ExplodeTime");
        getStaticParam(&mShockPower_s, "ShockPower");
        getStaticParam(&mUseDefaultEffect_s, "UseDefaultEffect");
    }
}

void BombExplode::calc_() {
    if (!_48) {
        setFailed();
        return;
    }

    mActor->m107();
    if (_1c.value <= sead::Mathf::epsilon()) {
        if (_48)
            sub_71007A2D34(_48);
        auto* actor = mActor;
        if (actor) {
            setFinished();
            if (actor->getConnectedCalcParent())
                actor->resetConnectedCalcParent(false);
        }
        return;
    }

    _1c.update();
    ksys::VFR::chase(&_54, _50, _58);
    _48->setRadius(_54);
}

}  // namespace uking::action
