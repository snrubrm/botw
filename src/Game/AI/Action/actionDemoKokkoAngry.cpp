#include "Game/AI/Action/actionDemoKokkoAngry.h"
#include "Game/AI/Action/actionSpotBgmTriggerAction.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

DemoKokkoAngry::DemoKokkoAngry(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoKokkoAngry::~DemoKokkoAngry() = default;

bool DemoKokkoAngry::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoKokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Angry", false, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (auto* body = mActor->getMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.setBit(6);
    ksys::gdt::setBoolByKey(true, "Kokko_Event_Running", false);
    _28 = ksys::Timer(*mWaitTime_s, *mWaitTime_s);
    _34 = 0;
    if (auto* mgr = sub_710FFD7CC())
        mgr->sub_710FFBEA8(true);
}

void DemoKokkoAngry::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoKokkoAngry::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
}

void DemoKokkoAngry::calc_() {
    _28.update();
    if (_28.value <= sead::Mathf::epsilon() && isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
