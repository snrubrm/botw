#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
}

// 0x71005e11ac (declared only; 728 bytes): navmesh query for a ground position near `target` (NaN: use the
// actor's own position) for the actor's NavMeshCharacter, writing the result to `out`. Used by
// EnemyMoveToGround. Placeholder name and parameter names.
bool sub_71005E11AC(sead::Vector3f* out, ksys::act::Actor* actor, const sead::Vector3f* target,
                    f32 search_radius, f32 area_threshold);
