#include "Game/AI/Action/actionGearStop.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GearStop::GearStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GearStop::~GearStop() = default;

bool GearStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GearStop::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        const f32 speed = body->getAngularVelocity().length();
        _30.value = speed;
        _30.prev_value = speed;
    }
    actor->emitBasicSigOff();
}

void GearStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void GearStop::loadParams_() {
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mRotateDamp_m, "RotateDamp");
}

void GearStop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
