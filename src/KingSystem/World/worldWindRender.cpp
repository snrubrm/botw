#include <math/seadMathCalcCommon.h>
#include "KingSystem/World/worldWindMgr.h"
#include <cstring>

namespace ksys::world {

// 0x7102660d10 (placeholder name): two 64-entry tables cleared by the render-wind constructor;
// hidden visibility keeps the loads direct without folding them.
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102660D10[2][64];

// NON_MATCHING: the two adjacent table clears merge into one memset.
Unk_710251F868::Unk_710251F868()
    : _8(0.0f), _c(0.0f), _10(4800.0f), _18(1280), _1c(16), _20(1280), _24(16),
      _40(nullptr), _258(65.5f), _25c(0.07f), _260(0.062f), _264(0.5f) {
    std::memset(sUnk_7102660D10[0], 0, sizeof(sUnk_7102660D10[0]));
    std::memset(sUnk_7102660D10[1], 0, sizeof(sUnk_7102660D10[1]));
}

// NON_MATCHING: the existing TextureData destructor remains an out-of-line call.
Unk_710251F868::~Unk_710251F868() {
    if (_40) {
        _28.deleteGPUMemBlock();
        delete _40;
        _40 = nullptr;
        _28.invalidate();
    }
}

void Unk_710251F868::sub_71012FEFF0(f32 delta) {
    _c += delta;
    if (_c >= _10 + _10)
        _c -= _10 + _10;
    _8 = _c / _10;
}

// NON_MATCHING: trigonometric result registers and table-index scheduling differ.
f32 Unk_710251F868::sub_71012FF01C(const sead::Vector3f* position,
                                   const sead::Vector2f* direction, f32 strength, f32 value) const {
    const f32 phase = (((value * 1.56985867f + _8 * 313.97174f) -
                        direction->x * position->x) - direction->y * position->y) *
                      0.022295f * 6.2831855f;
    const f32 envelope = sead::Mathf::clamp(2.0f * sead::Mathf::min(strength, 1.0f - strength),
                                          0.0f, 1.0f);
    const f32 high_strength = sead::Mathf::clamp(strength - 0.3f, 0.0f, 1.0f);
    const f32 cos2 = sead::Mathf::cos(phase + phase);
    const f32 cos3 = sead::Mathf::cos(phase * 3.0f);
    const f32 cos5 = sead::Mathf::cos(phase * 5.0f);
    const f32 sin3 = sead::Mathf::sin(phase * 3.0f);
    const f32 sin5 = sead::Mathf::sin(phase * 5.0f);
    const f32 sin7 = sead::Mathf::sin(phase * 7.0f);
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    const f32 lower = sUnk_7102660D10[0][s32(t * 63.0f)] / 0.619999766f;
    const f32 upper = sUnk_7102660D10[1][s32(t * 63.0f)] / 0.619999766f;
    const f32 range = upper - lower;
    if (range <= 0.01f)
        return 1.0f;
    const f32 high = high_strength / 0.7f;
    const f32 sample = ((envelope * (1.0f - envelope * cos2 * cos3 * cos5) * 0.23333333f +
                         high * (high * 0.6f * sin3 * sin5 * sin7 + 1.0f)) * 0.3f) /
                       0.619999766f;
    return (sead::Mathf::max(sample, 0.0f) - lower) / range;
}

f32 Unk_710251F868::sub_71012FF268(f32 strength) {
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    return sUnk_7102660D10[0][s32(t * 63.0f)] / 0.619999766f;
}

f32 Unk_710251F868::sub_71012FF2B0(f32 strength) {
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    return sUnk_7102660D10[1][s32(t * 63.0f)] / 0.619999766f;
}

}  // namespace ksys::world
