#include "Game/AI/Action/actionAddRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AddRigidBody::AddRigidBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AddRigidBody::~AddRigidBody() = default;

bool AddRigidBody::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AddRigidBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AddRigidBody::leave_() {
    ksys::act::ai::Action::leave_();
}

void AddRigidBody::loadParams_() {
    getStaticParam(&mResetLayer_s, "ResetLayer");
}

void AddRigidBody::calc_() {
    mFlags.set(Flag::Changeable);
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    if (auto* controller = physics->getCharacterController())
        controller->sub_7100F5EC30();
    auto* set = physics->findBodyByName(*sub_71007A24E4());
    if (!set)
        return;
    if (!*mResetLayer_s) {
        set->addToWorld();
        return;
    }
    for (int i = 0; i < set->getRigidBodies().size(); ++i) {
        if (auto* body = set->getRigidBodies()[i])
            physics->sub_7100FBAF18(body);
    }
}

}  // namespace uking::action
