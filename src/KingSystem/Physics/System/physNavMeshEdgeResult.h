#pragma once

#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMesh.h>
#include "KingSystem/Utils/Types.h"

class hkaiNavMeshInstance;
class hkaiStreamingCollection;

namespace ksys::phys {

class Unk_7100f7e9f0Event;

// Constructor 0x7100f7e64c and independent visitor 0x7100f854c4 establish
// this edge result. Callback 0x710066a30c reads the edge's opposite key.
class Unk_7100f7e64c {
public:
    Unk_7100f7e64c(hkaiStreamingCollection* collection, s32 key,
                   Unk_7100f7e9f0Event* event);
    ~Unk_7100f7e64c();

    hkaiNavMeshInstance* mInstance;
    const hkaiNavMesh::Edge* mEdge;
    Unk_7100f7e9f0Event* mEvent;
};
KSYS_CHECK_SIZE_NX150(Unk_7100f7e64c, 0x18);

}  // namespace ksys::phys
