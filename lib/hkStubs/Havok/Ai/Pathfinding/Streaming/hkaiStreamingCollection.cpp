#include <Havok/Ai/Pathfinding/Streaming/hkaiStreamingCollection.h>
#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMeshInstance.h>

int hkaiStreamingCollection::sub_71015145D0(hkUint32 sectionUid) {
    for (int i = 0; i < m_instances.getSize(); ++i) {
        const auto* instance = m_instances[i].m_instancePtr;
        if (instance && instance->m_sectionUid == sectionUid)
            return i;
    }
    return -1;
}
