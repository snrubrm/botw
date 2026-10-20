#include "KingSystem/Physics/CharacterController/physCharacterRigidBody.h"

#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

CharacterRigidBody::CharacterRigidBody(const hkpCharacterRigidBodyCinfo& info)
    : hkpCharacterRigidBody(info), _88(1.0f), _8c(10000.0f) {}

CharacterRigidBody::~CharacterRigidBody() = default;

void CharacterRigidBody::getGround(const hkArray<SupportInfo>&, hkBool, hkpSurfaceInfo&) {}

// NON_MATCHING: vector selection and loop branches are scheduled differently.
void CharacterRigidBody::updateSurfaceVelocityMaybe(const hkArray<SupportInfo>& support,
                                                    hkBool use_dynamic, hkpSurfaceInfo& surface,
                                                    ContactLayer layer, bool clamp_upward) const {
    surface.m_surfaceVelocity.setZero();
    const s32 num_supports = support.getSize();
    for (s32 i = 0; i < num_supports; ++i) {
        const auto& info = support[i];
        surface.m_surfaceVelocity.add(info.m_surfaceVelocity);
        const auto motion_type = info.m_rigidBody->getMotionType();
        auto* character_body = getRigidBody();
        if (motion_type == hkpMotion::MOTION_FIXED)
            continue;
        hkSimdReal time_factor = character_body->getTimeFactor();
        if (time_factor.isEqualZero())
            time_factor = 0.0f;
        auto* body = reinterpret_cast<RigidBody*>(info.m_rigidBody->getUserData());
        if (motion_type != hkpMotion::MOTION_KEYFRAMED &&
            (!use_dynamic || (body->hasFlag(RigidBody::Flag::NoCharStandingOn) &&
                              (layer != ContactLayer::EntitySmallObject ||
                               !body->isEntityMotionFlag80On()))))
            continue;
        const auto* state = body->getHkBody()->getMotion()->getMotionState();
        const auto& swept = state->getSweptTransform();
        const hkSimdReal inv_delta_time = swept.getInvDeltaTimeSr();
        hkVector4 linear_velocity;
        linear_velocity.setSub(swept.m_centerOfMass1, swept.m_centerOfMass0);
        linear_velocity.mul(inv_delta_time);
        hkVector4 angular_velocity;
        angular_velocity.setMul(state->m_deltaAngle, inv_delta_time);
        hkVector4 relative_position;
        relative_position.setSub(info.m_contactPoint.getPosition(), swept.m_centerOfMass1);
        hkVector4 point_velocity;
        point_velocity.setCross(angular_velocity, relative_position);
        point_velocity.add(linear_velocity);
        point_velocity.mul(time_factor);
        if (clamp_upward && point_velocity.getY().isGreaterZero())
            point_velocity.zeroComponent<1>();
        surface.m_surfaceVelocity.add(point_velocity);
    }
    surface.m_surfaceVelocity.mul(hkSimdReal(float(num_supports)).reciprocal());
}

}  // namespace ksys::phys
