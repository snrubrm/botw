#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actMotorcycleStickControl.h"
#include "KingSystem/System/VFR.h"

namespace uking::act {

// NON_MATCHING: the original loads and takes the absolute value of _8 after the second delta frame
// fetch of the zero crossing branch; we do it before the fetch (all else matches)
f32 Unk_71002c8918::sub_71002C8918(f32 target) {
    const f32 eps = sead::Mathf::epsilon();
    f32 rate;
    if (target <= eps && target >= -eps) {
        rate = _0;
    } else {
        const f32 cur = _8;
        if ((cur <= eps && cur >= -eps) || (cur < 0 && target < cur) || (cur > 0 && cur < target)) {
            rate = _4;
        } else {
            const f32 abs_cur = sead::Mathf::abs(cur);
            if (abs_cur > _0 * ksys::VFR::instance()->getDeltaFrame()) {
                rate = _0;
            } else {
                const f32 rest = 1.0f - sead::Mathf::abs(_8) / (_0 * ksys::VFR::instance()->getDeltaFrame());
                const f32 step = sead::Mathf::abs(_8) + _4 * rest;
                _8 = sead::Mathf::clamp(target, _8 - step, _8 + step);
                return _8;
            }
        }
    }
    _8 = sead::Mathf::clamp(target, _8 - rate * ksys::VFR::instance()->getDeltaFrame(),
                            _8 + rate * ksys::VFR::instance()->getDeltaFrame());
    return _8;
}

}  // namespace uking::act
