#pragma once

#include <Havok/Ai/Pathfinding/NavMesh/hkaiNavMesh.h>
#include <math/seadVector.h>
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
    // Visitor 0x7100f854c4 passes this same edge result to shared cleanup
    // 0x7100f7e728, also used by the face result; both own the event at +0x10.
    ~Unk_7100f7e64c();

    // 0x7100f7e754 writes endpoints and optional midpoint, direction, length,
    // sideways normal and up vector. The independent callback 0x710066a30c consumes them.
    void sub_7100F7E754(sead::Vector3f* start_out, sead::Vector3f* end_out,
                        sead::Vector3f* midpoint_out, sead::Vector3f* direction_out,
                        f32* length_out, sead::Vector3f* side_out, sead::Vector3f* up_out) const;

    hkaiNavMeshInstance* mInstance;
    const hkaiNavMesh::Edge* mEdge;
    Unk_7100f7e9f0Event* mEvent;
};
KSYS_CHECK_SIZE_NX150(Unk_7100f7e64c, 0x18);

}  // namespace ksys::phys
