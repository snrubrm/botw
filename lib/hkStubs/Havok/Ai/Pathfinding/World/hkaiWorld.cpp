#include <Havok/Ai/Pathfinding/World/hkaiWorld.h>

hkaiDynamicNavMeshQueryMediator* hkaiWorld::getMediator() {
    return m_mediator.val();
}

const hkaiDynamicNavMeshQueryMediator* hkaiWorld::getMediator() const {
    return m_mediator.val();
}
