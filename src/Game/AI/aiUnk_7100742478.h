#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

// 0x7100742478 (declared only; unnamed free function in the AI utility area): queries the
// navmesh / ground with the segment from `pos` down by `height` (along Vector3f::ey) using the
// world's HavokAI; on success writes the hit point to `out` and returns whether its vertical
// offset is within a tolerance. Placeholder name; `a3` is passed through to 0x7100f74fd8.
bool sub_7100742478(sead::Vector3f* out, const sead::Vector3f& pos, f32 height, s32 a3);

namespace ksys::phys {
class NavMeshCharacter;
}

// 0x7100742278 (declared only): navmesh query (HavokAI query for `a2`, then the character's
// path-finder) whether `pos` can be reached by `nav` within `radius`. Placeholder name; `a2` is passed
// as null by all callers.
bool sub_7100742278(f32 radius, void* a2, ksys::phys::NavMeshCharacter* nav,
                    const sead::Vector3f* pos);

// 0x7100742588 (lane1 s22, declared only): like sub_7100742278 (HavokAI navmesh query with `radius`
// for `pos`, filled with the character's parameters); optionally writes the resulting position to
// `out`. Placeholder name; `out` is passed as null by AnimalRoam::m35.
bool sub_7100742588(sead::Vector3f* out, ksys::phys::NavMeshCharacter* nav, const sead::Vector3f* pos,
                    f32 radius);
