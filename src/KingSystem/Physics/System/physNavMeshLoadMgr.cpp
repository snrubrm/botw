#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

// NON_MATCHING: register allocation / instruction scheduling only (the original ors the tile sizes in the other operand order
// and clamps the z tile before converting the z position)
bool NavMeshLoadMgr::x_1(const sead::Vector3f* pos) {
    if (_190)
        return false;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return false;
    if (_178 == 0 && _17c == 0)
        return false;

    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170) / _178, 0, _180 - 1);
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _174) / _17c, 0, _184 - 1);
    const s32 dx = sead::Mathi::abs(x - _188);
    const s32 dz = sead::Mathi::abs(z - _18c);
    if (dx < 2 && dz < 2)
        return false;
    if (dx == 2 && dz == 2)
        return false;
    return dx < 3 && dz < 3;
}

}  // namespace ksys::phys
