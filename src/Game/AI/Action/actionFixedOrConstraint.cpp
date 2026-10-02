#include "Game/AI/Action/actionFixedOrConstraint.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

FixedOrConstraint::FixedOrConstraint(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FixedOrConstraint::~FixedOrConstraint() = default;

bool FixedOrConstraint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FixedOrConstraint::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (body && actor->getConstraints().size() == 0)
        body->changeMotionType(ksys::phys::MotionType::Fixed);
}

void FixedOrConstraint::leave_() {
    ksys::act::ai::Action::leave_();
}

void FixedOrConstraint::loadParams_() {}

void FixedOrConstraint::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
