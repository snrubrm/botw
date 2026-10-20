#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>

class hkaiNavMeshQueryMediator;
class hkaiStreamingCollection;
class hkaiNavMeshInstance;
struct hkcdRay;

// Utility owner identified by the neighboring removeOwnedFaces/getNearbyBoundaries entries.
class hkaiNavMeshUtils {
public:
    // 1527624 triangulates the face in world space and returns the nearest
    // ray fraction. Game F7EDD8 supplies an instance and the local face key.
    // Declaration only; function name is descriptive.
    static bool castRayFaceMaybe(const hkaiNavMeshInstance& instance, hkInt32 faceIndex,
                                 const hkcdRay& ray, hkSimdReal& fractionOut);

    // Descriptive name: 1524EA8 appends the face key followed by the packed edge key.
    // HavokAI F854C4/F8565C consume the second word as an edge key for their callbacks.
    struct FaceEdgePair {
        hkUint32 m_faceKey;
        hkUint32 m_edgeKey;
    };

    // 0x7101525018: mediator AABB query, followed by per-face edge intersection tests.
    // Declaration only; function name is descriptive.
    static void queryAabbEdgesMaybe(hkaiStreamingCollection* collection,
                                    const hkaiNavMeshQueryMediator* mediator,
                                    const hkAabb& aabb, hkArray<FaceEdgePair>& hits);
};
static_assert(sizeof(hkaiNavMeshUtils::FaceEdgePair) == 8);
static_assert(offsetof(hkaiNavMeshUtils::FaceEdgePair, m_edgeKey) == 4);
