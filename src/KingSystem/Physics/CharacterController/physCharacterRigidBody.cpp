#include "KingSystem/Physics/CharacterController/physCharacterRigidBody.h"

#include <Havok/Common/Base/Container/Array/hkLocalArray.h>
#include <Havok/Common/Internal/SimplexSolver/hkSimplexSolver.h>
#include <Havok/Physics2012/Collide/Agent3/Machine/Nn/hkpAgentNnEntry.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Havok/Physics2012/Dynamics/Constraint/Atom/hkpModifierConstraintAtom.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Utilities/CharacterControl/StateMachine/hkpCharacterState.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

CharacterRigidBody::CharacterRigidBody(const hkpCharacterRigidBodyCinfo& info)
    : hkpCharacterRigidBody(info), _88(1.0f), _8c(10000.0f) {}

CharacterRigidBody::~CharacterRigidBody() = default;

// NON_MATCHING: contact iteration, solver temporaries and local-array lifetimes differ in scheduling.
hkpSurfaceInfo::SupportedState CharacterRigidBody::getSupportInfo(const hkStepInfo& step,
                                                                hkArray<SupportInfo>& support) {
    hkLocalArray<hkSurfaceConstraintInfo> constraints(20);
    hkLocalArray<SupportInfo> contacts(20);
    hkArray<hkpLinkedCollidable::CollisionEntry> entries;
    m_character->getCollidableMtUnchecked()->getCollisionEntriesSorted(entries);
    for (int i = 0; i < entries.getSize(); ++i) {
        const auto* entry = entries[i].m_agentEntry;
        if (entry->m_contactMgr->m_type != hkpContactMgr::TYPE_SIMPLE_CONSTRAINT_CONTACT_MGR)
            continue;
        auto* mgr = static_cast<hkpSimpleConstraintContactMgr*>(entry->m_contactMgr);
        if (mgr->isConstraintDisabled())
            continue;
        hkVector4 surface_velocity;
        surface_velocity.setZero();
        for (const hkpConstraintAtom* atom = mgr->m_constraint.getConstraintModifiers(); atom;) {
            if (atom->getType() < hkpConstraintAtom::TYPE_MODIFIER_SOFT_CONTACT)
                break;
            if (atom->getType() == hkpConstraintAtom::TYPE_MODIFIER_MOVING_SURFACE) {
                surface_velocity =
                    static_cast<const hkpMovingSurfaceModifierConstraintAtom*>(atom)->m_velocity;
                break;
            }
            atom = static_cast<const hkpModifierConstraintAtom*>(atom)->m_child;
        }
        auto& data = mgr->m_contactConstraintData;
        for (int j = 0; j < data.getNumContactPoints(); ++j) {
            const hkContactPointId id = data.getContactPointIdAt(j);
            if (data.getContactPointProperties(id)->m_flags &
                hkContactPointMaterial::CONTACT_IS_DISABLED)
                continue;
            const auto* first = entry->m_collidable[0];
            const auto* other =
                first == m_character->getCollidable() ? entry->m_collidable[1] : first;
            auto* body = hkpGetRigidBody(other);
            if (!body)
                continue;
            auto& contact = contacts._expandOne(hkContainerHeapAllocator().get());
            contact.m_rigidBody = body;
            contact.m_contactPoint = data.getContactPoint(id);
            contact.m_surfaceVelocity = surface_velocity;
            if (first != m_character->getCollidable())
                contact.m_contactPoint.flip();
            auto& constraint = constraints._expandOne(hkContainerHeapAllocator().get());
            constraint.m_plane = contact.m_contactPoint.getSeparatingNormal();
            constraint.m_velocity.setZero();
            constraint.m_staticFriction = 0;
            constraint.m_extraUpStaticFriction = 0;
            constraint.m_extraDownStaticFriction = 0;
            constraint.m_dynamicFriction = 0;
            constraint.m_priority = body->getMotionType() == hkpMotion::MOTION_FIXED ? 2 :
                                    int(body->getMotionType() == hkpMotion::MOTION_KEYFRAMED);
        }
    }
    hkLocalArray<hkSurfaceConstraintInteraction> interactions(constraints.getSize());
    hkSimplexSolverInput input;
    input.m_position.setZero();
    input.m_velocity.setMul(hkSimdReal(-_4c / step.m_deltaTime), m_up);
    input.m_maxSurfaceVelocity.setAll(_48);
    input.m_upVector = m_up;
    input.m_deltaTime = step.m_deltaTime;
    input.m_minDeltaTime = step.m_deltaTime;
    input.m_constraints = constraints.begin();
    input.m_numConstraints = constraints.getSize();
    hkSimplexSolverOutput output;
    output.m_planeInteractions = interactions.begin();
    interactions.setSize(constraints.getSize());
    constraints.setSize(input.m_numConstraints);
    hkSimplexSolverSolve(input, output);
    if (output.m_velocity.allEqual<3>(input.m_velocity, hkSimdReal(0.001f)))
        return hkpSurfaceInfo::UNSUPPORTED;
    auto state = hkpSurfaceInfo::SUPPORTED;
    const hkSimdReal length_squared = output.m_velocity.lengthSquared<3>();
    if (!length_squared.isLess(hkSimdReal(0.001f))) {
        const hkSimdReal up_component = output.m_velocity.dot<3>(m_up);
        if ((length_squared * hkSimdReal(_44 * _44))
                .isGreater(length_squared - up_component * up_component))
            state = hkpSurfaceInfo::SLIDING;
    }
    int num_supports = 0;
    for (int i = 0; i < constraints.getSize(); ++i) {
        if (interactions[i].m_touched &&
            constraints[i].m_plane.dot<3>(m_up).val() > 0.08f) {
            support.pushBack(contacts[i]);
            ++num_supports;
        }
    }
    return num_supports != 0 ? state : hkpSurfaceInfo::UNSUPPORTED;
}

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
