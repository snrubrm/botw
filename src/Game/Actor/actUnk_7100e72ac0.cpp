#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actMotorcycleStickControl.h"
#include "Game/Actor/actHorseBoneController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/VFR.h"

namespace uking::act {

// The semicolon preserves the original vtable store, as in GameDataFlagSelector's destructor
// (upstream commit 96101229).
Unk_71024eb5e0::~Unk_71024eb5e0() { ; }

void Unk_71024eb5e0::destroy() {
    for (auto* chain : mChains) {
        if (chain)
            chain->sub_7100F73B7C();
    }
    delete this;
}

f32 Unk_7100e72ac0::motorcycleStickControlStuff(f32 target) {
    const f32 eps = sead::Mathf::epsilon();
    const f32 cur = _8;
    const f32 rate = (target < -eps ? cur < target : target < eps || cur > target) ? _0 : _4;
    _8 = sead::Mathf::clamp(target, cur - rate * ksys::VFR::instance()->getDeltaFrame(),
                            _8 + rate * ksys::VFR::instance()->getDeltaFrame());
    return _8;
}

}  // namespace uking::act
