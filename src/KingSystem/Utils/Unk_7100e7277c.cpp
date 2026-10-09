#include "KingSystem/Utils/Unk_7100e7277c.h"
#include "KingSystem/Utils/Unk_7100e726a8.h"
#include <cmath>
#include "KingSystem/System/VFR.h"

// NON_MATCHING: scheduling of the coefficient and current-value loads.
f32 Unk_7100e7277c::sub_7100E7277C(f32 target) {
    _8 = target + (_8 - target) * std::pow(1.0f - *_0, ksys::VFR::instance()->getDeltaFrame());
    return _8;
}


f32 Unk_7100e726a8::sub_7100E726A8(f32 value) {
    return sub_7100E72498(&_30, &_34, &_38, value, *_0, *_8, *_10, *_18, *_20, *_28);
}
