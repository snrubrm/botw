#include "KingSystem/Utils/Unk_7100e7277c.h"
#include <cmath>
#include "KingSystem/System/VFR.h"

// NON_MATCHING: scheduling of the coefficient and current-value loads.
f32 Unk_7100e7277c::sub_7100E7277C(f32 target) {
    _8 = target + (_8 - target) * std::pow(1.0f - *_0, ksys::VFR::instance()->getDeltaFrame());
    return _8;
}
