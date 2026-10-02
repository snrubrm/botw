#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

// 0x7100742478 (declared only; unnamed free function in the AI utility area): queries the
// navmesh / ground with the segment from `pos` down by `height` (along Vector3f::ey) using the
// world's HavokAI; on success writes the hit point to `out` and returns whether its vertical
// offset is within a tolerance. Placeholder name; `a3` is passed through to 0x7100f74fd8.
bool sub_7100742478(sead::Vector3f* out, const sead::Vector3f& pos, f32 height, s32 a3);
