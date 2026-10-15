#include "Game/Actor/Action/actionApplyMoveImpulse.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

ApplyMoveImpulse::ApplyMoveImpulse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyMoveImpulse::~ApplyMoveImpulse() = default;

bool ApplyMoveImpulse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyMoveImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    _30 = 0;
    mFlags.set(Flag::Changeable);
}

void ApplyMoveImpulse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyMoveImpulse::loadParams_() {
    getStaticParam(&mFellImpRate_s, "FellImpRate");
    getStaticParam(&mFellRotRate_s, "FellRotRate");
}

// NON_MATCHING: Clang outlines the existing inverse33 API; determinant grouping and flag width differ.
void ApplyMoveImpulse::calc_() {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body)
        return;
    sead::Vector3f linear_velocity;
    sead::Vector3f angular_velocity;
    body->getLinearVelocity(&linear_velocity);
    body->getAngularVelocity(&angular_velocity);
    const f32 linear_speed = linear_velocity.length();
    const f32 angular_speed = angular_velocity.length();
    const bool stationary = linear_speed <= 0.01f && angular_speed <= 0.01f;
    ksys::act::acc::PlayerBase player;
    sead::Vector3f contact_position = sead::Vector3f::zero;
    sead::Vector3f contact_velocity = sead::Vector3f::zero;
    bool found_player = false;
    bool player_state = false;
    auto* contacts = body->getContactPointInfo();
    if (contacts && contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
        for (auto it = contacts->begin(), end = contacts->end(); it != end; ++it) {
            auto* other = it.getPoint()->body_b;
            if (!other || other->getMotionType() == ksys::phys::MotionType::Fixed)
                continue;
            auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(other->getUserTag());
            if (!tag)
                continue;
            tag->acquireActor(&player);
            if (!player.hasProc() || !ksys::act::isPlayerProfile(player))
                continue;
            found_player = true;
            player_state = player.m186();
            contact_position = it.getPointPosition(ksys::phys::ContactPointInfo::Iterator::Point::BodyA);
            other->getPointVelocity(&contact_velocity, contact_position);
            break;
        }
    }
    if (stationary) {
        if (!found_player || !player_state) {
            _30 = 0;
        } else if (!_30) {
            _30 = 1;
            sead::Matrix34f inverse;
            inverse.setInverse33(actor->getMtx());
            sead::Vector3f direction = actor->getMtx().getTranslation() - contact_position;
            direction.rotate(inverse);
            direction.y = 0.0f;
            direction.rotate(actor->getMtx());
            direction.normalize();
            sead::Vector3f torque;
            sub_71005E0230(&torque, body, direction);
            const f32 mass = body->getMass();
            const sead::Vector3f impulse = mass * direction * *mFellImpRate_s;
            torque = mass * torque * *mFellRotRate_s;
            body->applyLinearImpulse(impulse);
            body->applyAngularImpulse(torque);
        }
    }
}

}  // namespace uking::action
