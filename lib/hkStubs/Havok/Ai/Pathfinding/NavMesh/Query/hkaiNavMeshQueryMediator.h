#pragma once

#include <Havok/Common/Base/hkBase.h>

// The dynamic mediator constructor 0x710156eb64 installs vtable 0x710253a398.
// Its first five slots are hkReferencedObject's interface. Profiling strings in
// 0x710156edfc / 0x710156eeec / 0x710156efdc identify the three following query operations.
class hkaiNavMeshQueryMediator : public hkReferencedObject {
public:
    // Descriptive input/member names: the shared prefix is copied as 0x28 bytes by
    // castRay 0x710156efdc. HavokAI 0x7100f85c00 and 0x7100f87760 initialize it identically.
    struct QueryInput {
        hkUint32 _0 = 0;
        hkInt32 _4 = -1;
        hkUlong _8 = 0;
        const void* _10 = nullptr;
        const void* _18 = nullptr;
        const void* _20 = nullptr;
    };
    static_assert(sizeof(QueryInput) == 0x28);

    struct ClosestPointInput : QueryInput {
        hkVector4 m_position;  // +0x30
        hkVector4 m_halfExtents;  // +0x40
    };
    static_assert(sizeof(ClosestPointInput) == 0x50);

    struct RaycastInput : QueryInput {
        hkVector4 m_from;  // +0x30
        hkVector4 m_to;  // +0x40
    };
    static_assert(sizeof(RaycastInput) == 0x50);

    // The dynamic castRay writes two floats and a packed face key. HavokAI
    // 0x7100f87760 interpolates the endpoints by the first float and consumes the key.
    struct RaycastOutput {
        hkReal m_hitFraction;
        hkReal _4;
        hkUint32 m_faceKey;
    };
    static_assert(sizeof(RaycastOutput) == 0xc);

    virtual hkUint32 getClosestPoint(const ClosestPointInput& input, hkVector4& point) const = 0;
    virtual hkUint32 getClosestBoundaryPoint(const ClosestPointInput& input,
                                           hkVector4& point) const = 0;
    virtual hkBool32 castRay(const RaycastInput& input, RaycastOutput& output) const = 0;
    // The later sphere, bidirectional-ray and AABB virtual interfaces are not modelled yet.
};
