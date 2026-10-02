// Unk_7102459dd8 (Camera::_860._1d0, eased progress value): 0x710079c364-0x710079c5ac. A TU of its
// own — Unk_710079a8e8::sub_710079AEE0 calls sub_710079C510 out of line.
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCamera.h"

namespace uking::act {

Unk_7102459dd8::Unk_7102459dd8() = default;

static f32 sub_ease(f32 t) {
    return (std::sin(t * sead::Mathf::pi() - sead::Mathf::piHalf()) + 1.0f) * 0.5f;
}

void Unk_7102459dd8::sub_710079C384(f32 a, f32 t) {
    _8 = sead::Mathf::clampMin(a, 0.0f);
    _14 = sead::Mathf::clamp(t, 0.0f, 1.0f);
    _18 = sub_ease(_14);
}

void Unk_7102459dd8::sub_710079C3F8(f32 a) {
    _c = sead::Mathf::clampMin(a, 0.0f);
}

void Unk_7102459dd8::sub_710079C408() {
    const f32 total = _8 * _c;
    _10 = total == 0.0f ? 1.0f : 1.0f / total;
    const f32 step = _10 * ksys::VFR::instance()->getDeltaFrame();
    if (_14 < 1.0f) {
        const f32 t = _14 + step;
        _14 = (t >= 1.0f || t < _14) ? 1.0f : t;
    } else if (_14 > 1.0f) {
        const f32 t = _14 - step;
        _14 = (t <= 1.0f || _14 < t) ? 1.0f : t;
    }
    _18 = sub_ease(_14);
}

void Unk_7102459dd8::sub_710079C510(f32 t) {
    _14 = sead::Mathf::clamp(t, 0.0f, 1.0f);
    _18 = sub_ease(_14);
}

}  // namespace uking::act
