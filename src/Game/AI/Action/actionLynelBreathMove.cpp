#include "Game/AI/Action/actionLynelBreathMove.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

LynelBreathMove::LynelBreathMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelBreathMove::~LynelBreathMove() = default;

bool LynelBreathMove::init_(sead::Heap* heap) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    return true;
}

void LynelBreathMove::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    _1c = mActor->getVelocity();
    if (auto* body = mActor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        body->setGravityFactor(0.0f);
        body->setFrictionScale(0.0f);
    }
    _28.reset(_28._88);
    _d0 = true;
}

void LynelBreathMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void LynelBreathMove::loadParams_() {}

void LynelBreathMove::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _28.sub_7100716408(pos);
    ksys::act::sub_7100EE5980(mActor, _1c);
    _d0 = false;
}

}  // namespace uking::action
