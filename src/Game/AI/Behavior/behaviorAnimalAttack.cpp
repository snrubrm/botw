#include "Game/AI/Behavior/behaviorAnimalAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::behavior {

AnimalAttack::AnimalAttack(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
AnimalAttack::~AnimalAttack() {
    ;
}

bool AnimalAttack::m6(sead::Heap* heap) {
    return true;
}

void AnimalAttack::loadParams() {
    getStaticParam(&mIsUseASEventAtCollision_s, "IsUseASEventAtCollision");
    getStaticParam(&mAtkRigidName_s, "AtkRigidName");
}

void AnimalAttack::m8() {
    auto* actor = mActor;
    _40 = false;
    sub_71007A2C30(actor, mAtkRigidName_s, &actor->getMtx());
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(*sub_71007A24E4())) {
            if (set->getRigidBodies().size() >= 1)
                _48 = set->getRigidBodies()[0];
        }
    }
    if (*mIsUseASEventAtCollision_s) {
        sub_71007A3270(actor, mAtkRigidName_s, nullptr);
        return;
    }
    if (_48)
        _48->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    getActorAttackSensor(actor)->activateAttackSensor(
        0x2000, 2, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(), 0, 0.0f, 0,
        1, -1, false, 1, -1);
}

void AnimalAttack::m9() {
    if (_48)
        _48->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    sub_71007A2D7C(mActor, mAtkRigidName_s);
}

}  // namespace uking::behavior
