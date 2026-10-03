#pragma once

#include "Game/AI/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking {

// inline-only in the original; name is a guess. The ratio that undoes the slow-time effect: `1 /
// scale` while isSlowTimeMaybe() and the slow-time scale (the global 0.05f, 0x7101e7c1dc) is above
// 0.001, else 1. The same sequence is inlined in ForkNoSlowTimer::m33 and SetBoneControlNoSlow::m8.
inline f32 getNoSlowTimeRatio() {
    f32 ratio = 1.0f;
    if (isSlowTimeMaybe()) {
        const f32 scale = sUnk_7101e7c1dc;
        if (scale > 0.001f)
            ratio = 1.0f / scale;
    }
    return ratio;
}

}  // namespace uking
