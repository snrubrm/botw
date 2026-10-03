#include "Game/AI/aiUnk_71025b0578.h"
#include <math/seadMathCalcCommon.h>

// 0x71007169cc.
// NON_MATCHING: the original keeps the result in w8 and returns through a shared `mov w0, w8`
bool Unk_7100716408::sub_71007169CC(f32 threshold) const {
    bool result = false;
    if (threshold > 0.0f) {
        if (_8c) {
            result = sead::Mathf::max(sead::Mathf::max(_90.getSizeX(), _90.getSizeY()),
                                      _90.getSizeZ()) < threshold;
        }
    }
    return result;
}

// 0x710071f47c / 0x710071f494 (TU 0x710071f47c-0x710071f6dc).

void Unk_710071f494::sub_710071F47C() {
    _c = _8;
    _10 = false;
    _4 = _0;
}

void Unk_710071f494::sub_710071F494(s32 check_time, f32 value) {
    _0 = value;
    _10 = false;
    _8 = _c = check_time;
    _4 = value;
}
