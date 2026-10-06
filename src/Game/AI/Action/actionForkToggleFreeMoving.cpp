#include "Game/AI/Action/actionForkToggleFreeMoving.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::action {

static const sead::SafeString sUnk_710235e1d0 = "Body";

ForkToggleFreeMoving::ForkToggleFreeMoving(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkToggleFreeMoving::~ForkToggleFreeMoving() = default;

bool ForkToggleFreeMoving::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkToggleFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mEnterChoice_s) {
    case 1:
        sub_710005CA88(true);
        break;
    case 2:
        sub_710005CA88(false);
        break;
    }
    mFlags.set(Flag::Changeable);
}

void ForkToggleFreeMoving::leave_() {
    switch (*mLeaveChoice_s) {
    case 1:
        sub_710005CA88(true);
        break;
    case 2:
        sub_710005CA88(false);
        break;
    }
}

void ForkToggleFreeMoving::loadParams_() {
    getStaticParam(&mEnterChoice_s, "EnterChoice");
    getStaticParam(&mLeaveChoice_s, "LeaveChoice");
}

void ForkToggleFreeMoving::sub_710005CA88(bool hover) {
    const f32 gravity = hover ? 0.0f : 1.0f;
    if (auto* set = mActor->getRigidBodyByName(sUnk_710235e1d0.cstr())) {
        const int num_bodies = set->getRigidBodies().size();
        for (int i = 0; i < num_bodies; ++i)
            set->getRigidBody(i)->setGravityFactor(gravity);
    }
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(hover ? ksys::act::MotionType::Hover :
                                           ksys::act::MotionType::_0);
        controller->sub_7100F5EEB8(gravity);
    }
}

void ForkToggleFreeMoving::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
