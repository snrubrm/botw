#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

// 0x7100d8c538 (declared only): forwards to 0x7100d8b080 with the CameraMgr's look-at camera (false when there
// is none): a view test of `pos` with two float tolerances (used as `!sub_7100D8C538(pos, 0.1, dist)` by the
// out-of-screen checks). Placeholder name.
bool sub_7100D8C538(const sead::Vector3f& pos, f32 a2, f32 a3);
