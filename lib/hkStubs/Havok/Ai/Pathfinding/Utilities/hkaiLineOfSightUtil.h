#pragma once

#include <Havok/Ai/Pathfinding/hkaiAgentTraversalInfo.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Math/Vector/hkVector4f.h>

class hkaiAstarCostModifier;
class hkaiAstarEdgeFilter;
class hkaiStreamingCollection;

// The reflection class names for these records are in the image:
// "hkaiLineOfSightUtilInputBase" (0x50), ...DirectPathInput (0x60),
// ...LineOfSightInput (0x70) and ...LineOfSightOutput (0x50). The member
// records give the names and offsets used below.
class hkaiLineOfSightUtil {
public:
    // Reflected enum QueryMode, values MODE_LINE_OF_SIGHT / MODE_DIRECT_PATH.
    enum QueryMode {
        MODE_LINE_OF_SIGHT,
        MODE_DIRECT_PATH,
    };

    // Reflected enum LineOfSightResult, ten values in this order.
    enum LineOfSightResult {
        RESULT_INVALID_INPUT,
        RESULT_CANT_ADVANCE,
        RESULT_REACHED_BOUNDARY_CHECK_LIMIT,
        RESULT_IN_PROGRESS,
        RESULT_HIT_BOUNDARY_EDGE,
        RESULT_HIT_REJECTED_EDGE,
        RESULT_REACHED_RADIUS_LIMIT,
        RESULT_REACHED_PATH_LENGTH_LIMIT,
        RESULT_REACHED_ITERATION_LIMIT,
        RESULT_REACHED_GOAL,
    };

    // Reflected enum UserEdgeFlagBits, six values.
    enum UserEdgeFlagBits {
        USER_EDGE_IGNORE = 0,
        USER_EDGE_UNTRAVERSABLE_AS_BOUNDARY = 1,
        USER_EDGE_ALL_AS_BOUNDARY = 2,
        USER_EDGE_FOLLOW = 4,
        USER_EDGE_PRIORITIZE_REGULAR_EDGE = 8,
        USER_EDGE_IGNORE_WINDING = 16,
    };

    // Reflection initializer 0x7101770770 proves the real traversal-info
    // type and its diameter/filterInfo fields. Kept as an alias for callers.
    using AgentInfo = hkaiAgentTraversalInfo;

    struct InputBase {
        InputBase();

        hkVector4f m_startPoint;                              // +0x00 startPoint
        hkVector4f m_up;                                      // +0x10 up
        hkUint32 m_startFaceKey;                              // +0x20 startFaceKey
        hkInt32 m_maxNumberOfIterations;                      // +0x24 maxNumberOfIterations
        AgentInfo m_agentInfo;                                // +0x28 agentInfo
        hkReal m_searchRadius;                                // +0x30 searchRadius
        hkReal m_maximumPathLength;                           // +0x34 maximumPathLength
        const hkaiAstarCostModifier* m_costModifier;          // +0x38 costModifier
        const hkaiAstarEdgeFilter* m_edgeFilter;              // +0x40 edgeFilter
        hkBool m_outputEdgesOnFailure;                        // +0x48 outputEdgesOnFailure
        hkBool m_projectedRadiusCheck;                        // +0x49 projectedRadiusCheck
        hkBool m_exactInternalVertexHandling;                 // +0x4a exactInternalVertexHandling
        hkBool m_isWallClimbing;                              // +0x4b isWallClimbing
        hkEnum<QueryMode, hkUint8> m_mode;                    // +0x4c mode
        hkFlags<UserEdgeFlagBits, hkUint8> m_userEdgeHandling;  // +0x4d userEdgeHandling
        hkBool m_ignoreBackfacingEdges;                       // +0x4e ignoreBackfacingEdges
    };

    struct LineOfSightInput : InputBase {
        LineOfSightInput();

        hkVector4f m_goalPoint;  // +0x50 goalPoint
        hkUint32 m_goalFaceKey;  // +0x60 goalFaceKey
    };

    struct DirectPathInput : InputBase {
        DirectPathInput();

        hkVector4f m_direction;  // +0x50 direction
    };

    struct LineOfSightOutput {
        LineOfSightOutput();

        hkArray<hkUint32> m_visitedEdgesOut;    // +0x00 visitedEdgesOut
        hkArray<hkReal> m_distancesOut;         // +0x10 distancesOut
        hkArray<hkVector4f> m_pointsOut;        // +0x20 pointsOut
        hkBool m_doNotExceedArrayCapacity;      // +0x30 doNotExceedArrayCapacity
        hkInt32 m_numIterationsOut;             // +0x34 numIterationsOut
        hkUint32 m_finalFaceKey;                // +0x38 finalFaceKey (uninitialized in the original ctor)
        hkReal m_accumulatedDistance;           // +0x3c accumulatedDistance
        hkVector4f m_finalPoint;                // +0x40 finalPoint
    };

    // 0x710154b6bc, 340 B. Profile name "TtfindDirectPath"; the CSV name
    // "findDirectPathMaybe" is a guess. The callers load the collection from
    // hkaiWorld +0x20; the query mediator is the distinct +0x40 member.
    static LineOfSightResult findDirectPathMaybe(const hkaiStreamingCollection* collection,
                                                const DirectPathInput& input,
                                                LineOfSightOutput& output);

    // 0x71015498ac, 7696 B. Called with a goal direction, a goal point, the
    // start face key, the streaming collection, the input and the output; the name is a
    // guess. 0x7100f84d64 / 0x7100f851bc call it directly.
    static LineOfSightResult graphSearchMaybe(const hkVector4f& goalDirection,
                                              const hkVector4f& goalPoint, hkUint32 startFaceKey,
                                              const hkaiStreamingCollection* collection,
                                              const InputBase& input, LineOfSightOutput& output);
};

static_assert(sizeof(hkaiLineOfSightUtil::InputBase) == 0x50);
static_assert(sizeof(hkaiLineOfSightUtil::LineOfSightInput) == 0x70);
static_assert(sizeof(hkaiLineOfSightUtil::DirectPathInput) == 0x60);
static_assert(sizeof(hkaiLineOfSightUtil::LineOfSightOutput) == 0x50);
