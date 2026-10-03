#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actMotorcycleStickControl.h"
#include "KingSystem/System/VFR.h"

namespace uking::act {

f32 Unk_7100e72ac0::motorcycleStickControlStuff(f32 target) {
    const f32 eps = sead::Mathf::epsilon();
    const f32 cur = _8;
    const f32 rate = (target < -eps ? cur < target : target < eps || cur > target) ? _0 : _4;
    _8 = sead::Mathf::clamp(target, cur - rate * ksys::VFR::instance()->getDeltaFrame(),
                            _8 + rate * ksys::VFR::instance()->getDeltaFrame());
    return _8;
}

}  // namespace uking::act
