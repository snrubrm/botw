#include "Game/AI/Action/actionPutFromParent.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

PutFromParent::PutFromParent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PutFromParent::~PutFromParent() = default;

void PutFromParent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PutFromParent::leave_() {
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    actor->sub_71011DA834(&_38);
    sub_7100738DC8(actor);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F62CA8(true);
        controller->sub_7100F62C14(_e8);
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        if (controller->get64().x == 0.0f && controller->get64().z == 0.0f) {
            sead::Vector3f up;
            actor->getMtx().getBase(up, 2);
            sub_710072C1B4(controller, up);
        }
    } else if (auto* body = actor->getMainBody()) {
        body->clearEntityMotionFlag4(true);
        body->setMaxImpulse(_e8);
        body->setLinearDamping(_f0);
        body->setAngularDamping(_ec);
    }
    if (auto* obj = actor->m100()) {
        obj->_b0 = 0;
        obj->_b8 = 0;
    }
}

void PutFromParent::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mHoldOffXLinkKey_s, "HoldOffXLinkKey");
}

void PutFromParent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
