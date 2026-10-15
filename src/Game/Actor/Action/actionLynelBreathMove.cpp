#include "Game/Actor/Action/actionLynelBreathMove.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
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

// NON_MATCHING: saved position loads, stack slots and registers differ.
bool LynelBreathMove::isFinished() const {
    sead::Vector3f initial = _1c;
    const f32 speed = initial.normalize();
    sead::Vector3f current = mActor->getVelocity();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    current.normalize();
    if (!(initial.dot(current) >= std::cos(sead::Mathf::pi() * 0.5f)))
        return true;
    if (isBgGroundHit(mActor, false) && sub_71007A49F0(mActor) > 0) {
        s32 i = 0;
        do {
            if (const auto* contact = sub_71007A4948(mActor, i)) {
                sead::Vector3f direction = contact->_0 - position;
                direction.normalize();
                if (initial.dot(direction) >= std::cos(sead::Mathf::pi() * 0.25f))
                    return true;
            }
        } while (++i < sub_71007A49F0(mActor));
    }
    if (isLandedMaybe(mActor, false) && sub_71007A47C4(mActor) > 0) {
        s32 i = 0;
        do {
            if (const auto* contact = sub_71007A471C(mActor, i)) {
                sead::Vector3f direction = contact->_0 - position;
                direction.normalize();
                if (initial.dot(direction) >= std::cos(sead::Mathf::pi() * 0.25f))
                    return true;
            }
        } while (++i < sub_71007A47C4(mActor));
    }
    if (!_d0) {
        if (auto* chemical = mActor->getChemicalStuff()) {
            if (chemical->_c0 != 2)
                return true;
        }
    }
    if (_28.sub_71007169CC(speed * 0.4f))
        return true;
    return _28._78 <= 0.0f;
}

}  // namespace uking::action
