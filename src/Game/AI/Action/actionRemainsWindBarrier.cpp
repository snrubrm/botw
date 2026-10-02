#include "Game/AI/Action/actionRemainsWindBarrier.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

RemainsWindBarrier::RemainsWindBarrier(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemainsWindBarrier::~RemainsWindBarrier() {
    if (_30) {
        delete _30;
        _30 = nullptr;
    }
}

bool RemainsWindBarrier::init_(sead::Heap* heap) {
    _30 = new (heap) ksys::act::ModelBindInfo;
    return true;
}

void RemainsWindBarrier::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* set = actor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        _20 = set->getRigidBodies()[0];
        if (_20) {
            getActorAttackSensor(actor)->activateAttackSensor(
                0x4000, 0xc, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
                0, 0.0f, 0, 1, -1, false, 1, -1);
            _20->setTransform(actor->getMtx());
            sub_71007A2EB0(_20, actor, nullptr);
            sub_71007A2B64(_20, nullptr);
        }
    }
    _28 = actor->getPhysics()->findBodyByName(*sub_71007A2534());
    if (_28) {
        _28->setTransform(actor->getMtx());
        _28->addToWorld();
    }
}

void RemainsWindBarrier::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWindBarrier::loadParams_() {}

void RemainsWindBarrier::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
