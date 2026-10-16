#include "Game/gameIceBlockMgr.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"

namespace uking {

// createInstance is NON_MATCHING: store scheduling of the zeroed members in the inlined ctor.
SEAD_SINGLETON_DISPOSER_IMPL(IceBlockMgr)

IceBlockMgr::IceBlockMgr() = default;

// NON_MATCHING: register allocation of the last link reset (the original keeps it in x20).
IceBlockMgr::~IceBlockMgr() {
    _38.clear();
    if (_150) {
        delete _150;
        _150 = nullptr;
    }
    if (_158) {
        ksys::phys::QueryContactPointInfo::free(_158);
        _158 = nullptr;
    }
}

f32 IceBlockMgr::sub_710066F004() const {
    return sead::Mathf::clamp(_140 / 50.0f, 0.0f, 1.0f);
}

bool IceBlockMgr::sub_710066F038() const {
    return _140 > 0.0f;
}

}  // namespace uking
