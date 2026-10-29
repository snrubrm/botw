#pragma once

#include <basis/seadTypes.h>
#include "gsys/gsysModelAccessKey.h"

namespace gsys {

// 0x7100c7cfb0: the animation debug records. The two arrays at +0x70 / +0x110 are the
// SkeletalAnimObj work buffers initialized by initialize 0x7100c7cfec.
class ModelAnimationDebugInfo {
public:
    ~ModelAnimationDebugInfo();

private:
    u8 _0[0x70];
    u8* _70;
    u8 _78[0x110 - 0x78];
    u8* _110;
};

// Pointed to by Model +0x138. Layout not modelled beyond the two destructible members.
class ModelDebugInfo {
public:
    ~ModelDebugInfo();

    // 0x7100c00a1c
    void resetEditModelIndex();

private:
    u8 _0[0x98];
    BoneAccessKeyEx mKey;                  // +0x98
    ModelAnimationDebugInfo mAnimation;    // +0xd0
};

}  // namespace gsys
