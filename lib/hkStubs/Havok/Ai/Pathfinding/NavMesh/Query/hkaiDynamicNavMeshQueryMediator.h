#pragma once

#include <Havok/Ai/Pathfinding/NavMesh/Query/hkaiNavMeshQueryMediator.h>
#include <Havok/Common/Base/Types/hkRefPtr.h>

class hkaiStreamingCollection;
class hkaiNavMeshCutter;

// Named by the reflected hkaiWorld dynamicNavMeshMediator member. World constructor
// 0x71015555b8 allocates 0x30 bytes and invokes 0x710156eb64 with the collection, tree and cutter.
// Only the query interface through castRay is modelled; the lifetime remains declared only.
class hkaiDynamicNavMeshQueryMediator : public hkaiNavMeshQueryMediator {
public:
    ~hkaiDynamicNavMeshQueryMediator() override;

    hkUint32 getClosestPoint(const ClosestPointInput& input, hkVector4& point) const override;
    hkUint32 getClosestBoundaryPoint(const ClosestPointInput& input,
                                   hkVector4& point) const override;
    hkBool32 castRay(const RaycastInput& input, RaycastOutput& output) const override;

private:
    hkRefPtr<hkaiStreamingCollection> m_collection;  // +0x10
    hkRefPtr<hkReferencedObject> m_tree;  // +0x18; concrete tree type not identified
    hkRefPtr<hkaiNavMeshCutter> m_cutter;  // +0x20
    hkReal _28;
};
static_assert(sizeof(hkaiDynamicNavMeshQueryMediator) == 0x30);
