#include <Havok/Ai/Pathfinding/Utilities/hkaiLineOfSightUtil.h>

// NON_MATCHING: the original copies the 16-byte vector constants as two 8-byte
// moves (ldr/ldr + stp), while our hkVector4f stores m128 and copies them with a
// single 16-byte load/store. Every other instruction of the three constructors
// below agrees with the original. Changing hkVector4f's storage is a shared
// header change that needs its own evidence.
hkaiLineOfSightUtil::InputBase::InputBase()
    : m_startPoint(hkVector4f::getConstant<HK_QUADREAL_MAX>()),
      m_up(hkVector4f::getConstant<HK_QUADREAL_MAX>()),
      m_startFaceKey(0xffffffff),
      m_maxNumberOfIterations(100000),
      m_agentInfo(),
      m_searchRadius(-1.0f),
      m_maximumPathLength(HK_REAL_MAX),
      m_costModifier(nullptr),
      m_edgeFilter(nullptr),
      m_outputEdgesOnFailure(false),
      m_projectedRadiusCheck(true),
      m_exactInternalVertexHandling(true),
      m_isWallClimbing(false),
      m_mode(MODE_LINE_OF_SIGHT),
      m_userEdgeHandling(hkUint8(USER_EDGE_IGNORE)),
      m_ignoreBackfacingEdges(true) {}

hkaiLineOfSightUtil::LineOfSightInput::LineOfSightInput()
    : m_goalPoint(hkVector4f::getConstant<HK_QUADREAL_MAX>()), m_goalFaceKey(0xffffffff) {}

hkaiLineOfSightUtil::DirectPathInput::DirectPathInput()
    : m_direction(hkVector4f::getConstant<HK_QUADREAL_MAX>()) {
    m_isWallClimbing = true;
    m_mode = MODE_DIRECT_PATH;
}

hkaiLineOfSightUtil::LineOfSightOutput::LineOfSightOutput()
    : m_visitedEdgesOut(), m_distancesOut(), m_pointsOut(), m_doNotExceedArrayCapacity(false),
      m_numIterationsOut(0), m_accumulatedDistance(0.0f),
      m_finalPoint(hkVector4f::getConstant<HK_QUADREAL_MAX>()) {}
