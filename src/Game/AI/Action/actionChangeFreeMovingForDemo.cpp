#include "Game/AI/Action/actionChangeFreeMovingForDemo.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ChangeFreeMovingForDemo::ChangeFreeMovingForDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeFreeMovingForDemo::~ChangeFreeMovingForDemo() = default;

bool ChangeFreeMovingForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original materialises the MotionType 0 argument as a 64-bit zero (mov x1, xzr)
void ChangeFreeMovingForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        if (*mSetFreeMoving_d)
            body->setGravityFactor(0.0f);
        else
            body->setGravityFactor(1.0f);
    } else if (auto* controller = mActor->getCharacterController()) {
        if (*mSetFreeMoving_d) {
            controller->sub_7100F5F458(ksys::act::MotionType::Hover);
            controller->sub_7100F5EEB8(0.0f);
        } else {
            controller->sub_7100F5F458(ksys::act::MotionType::_0);
            controller->sub_7100F5EEB8(1.0f);
        }
    }
    setFinished();
}

void ChangeFreeMovingForDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeFreeMovingForDemo::loadParams_() {
    getDynamicParam(&mSetFreeMoving_d, "SetFreeMoving");
}

void ChangeFreeMovingForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
