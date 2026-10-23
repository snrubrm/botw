#include <Havok/Ai/Pathfinding/Utilities/hkaiPathfindingUtil.h>

namespace hkaiPathfindingUtil {

FindPathInput::FindPathInput() : m_startPoint(), m_goalPoints(), m_startFaceKey(0xffffffff),
                                 m_goalFaceKeys(), _48() {}

FindPathInput::~FindPathInput() = default;

FindPathOutput::FindPathOutput() : m_10(), m_pathOut(), _30() {}

FindPathOutput::~FindPathOutput() = default;

}  // namespace hkaiPathfindingUtil
