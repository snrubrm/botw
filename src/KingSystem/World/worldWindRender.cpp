#include <math/seadMathCalcCommon.h>
#include "KingSystem/World/worldWindMgr.h"

namespace ksys::world {

// 0x7102660d10 (placeholder name): two 64-entry tables filled at run time outside the decompiled code;
// hidden visibility keeps the loads direct without folding them.
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102660D10[2][64];

f32 Unk_710251F868::sub_71012FF268(f32 strength) {
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    return sUnk_7102660D10[0][s32(t * 63.0f)] / 0.619999766f;
}

f32 Unk_710251F868::sub_71012FF2B0(f32 strength) {
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    return sUnk_7102660D10[1][s32(t * 63.0f)] / 0.619999766f;
}

}  // namespace ksys::world
