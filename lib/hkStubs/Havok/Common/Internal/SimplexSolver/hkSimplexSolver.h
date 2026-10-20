#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <cstddef>

/// A moving plane and its friction parameters. Native solver helper 15A468C
/// selects the extra static friction by the sign of the velocity along m_upVector.
struct hkSurfaceConstraintInfo {
    hkVector4 m_plane;
    hkVector4 m_velocity;
    hkReal m_staticFriction;
    hkReal m_extraUpStaticFriction;
    hkReal m_extraDownStaticFriction;
    hkReal m_dynamicFriction;
    hkInt32 m_priority;
};
static_assert(sizeof(hkSurfaceConstraintInfo) == 0x40);
static_assert(offsetof(hkSurfaceConstraintInfo, m_priority) == 0x30);

struct hkSurfaceConstraintInteraction {
    hkBool m_touched;
    hkBool m_stopped;
    hkReal m_surfaceTime;
    hkReal m_penaltyDistance;
    hkInt32 m_status;
};
static_assert(sizeof(hkSurfaceConstraintInteraction) == 0x10);

struct hkSimplexSolverInput {
    hkVector4 m_position;
    hkVector4 m_velocity;
    hkVector4 m_maxSurfaceVelocity;
    hkVector4 m_upVector;
    hkReal m_deltaTime;
    hkReal m_minDeltaTime;
    const hkSurfaceConstraintInfo* m_constraints;
    hkInt32 m_numConstraints;
};
static_assert(sizeof(hkSimplexSolverInput) == 0x60);
static_assert(offsetof(hkSimplexSolverInput, m_constraints) == 0x48);

struct hkSimplexSolverOutput {
    hkVector4 m_position;
    hkVector4 m_velocity;
    hkReal m_deltaTime;
    hkSurfaceConstraintInteraction* m_planeInteractions;
};
static_assert(sizeof(hkSimplexSolverOutput) == 0x30);
static_assert(offsetof(hkSimplexSolverOutput, m_planeInteractions) == 0x28);

// 0x71015a3b80: copies the input position/velocity, then solves the moving planes.
void hkSimplexSolverSolve(const hkSimplexSolverInput& input, hkSimplexSolverOutput& output);
