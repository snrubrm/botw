#include "Game/AI/Action/actionRemoveRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RemoveRigidBody::RemoveRigidBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemoveRigidBody::~RemoveRigidBody() = default;

bool RemoveRigidBody::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemoveRigidBody::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    if (auto* controller = physics->getCharacterController())
        controller->sub_7100F5EC44();
    auto* set = physics->findBodyByName(*sub_71007A24E4());
    if (!set)
        return;
    if (!*mChangeLayer_s) {
        set->removeFromWorld();
        return;
    }
    for (int i = 0; i < set->getRigidBodies().size(); ++i) {
        if (auto* body = set->getRigidBodies()[i])
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
    }
}

void RemoveRigidBody::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemoveRigidBody::loadParams_() {
    getStaticParam(&mChangeLayer_s, "ChangeLayer");
}

void RemoveRigidBody::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
