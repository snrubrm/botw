#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

// NON_MATCHING: boolean return materialization, tile-size loads and saved registers differ.
bool NavMeshLoadMgr::x_0(const sead::Vector3f* pos) {
    if (_190)
        return false;
    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return false;
    if (_178.x == 0 && _178.y == 0)
        return true;
    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    if (sead::Mathi::abs(x - _188.x) > 1)
        return false;
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    return sead::Mathi::abs(z - _188.y) < 2;
}

// NON_MATCHING: register allocation / instruction scheduling only (the original ors the tile sizes in the other operand order
// and clamps the z tile before converting the z position)
// NON_MATCHING: register allocation / instruction scheduling only (same as x_1)
void NavMeshLoadMgr::sub_7100F8B334(const sead::Vector3f* pos) {
    if (_190)
        return;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return;
    if ((_180.x | _180.y) == 0)
        return;

    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    TileHandle* handle = _8 > 9 ? &_10->_360 : nullptr;
    if (handle->requestedLoad()) {
        if (x != handle->_50 || z != handle->_54)
            return;
    }
    handle->_50 = x;
    handle->_54 = z;
    a(handle);
}

bool NavMeshLoadMgr::x_1(const sead::Vector3f* pos) {
    if (_190)
        return false;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return false;
    if (_178.x == 0 && _178.y == 0)
        return false;

    const s32 x = sead::Mathi::clamp((s32(pos->x) - _170.x) / _178.x, 0, _180.x - 1);
    const s32 z = sead::Mathi::clamp((s32(pos->z) - _170.y) / _178.y, 0, _180.y - 1);
    const s32 dx = sead::Mathi::abs(x - _188.x);
    const s32 dz = sead::Mathi::abs(z - _188.y);
    if (dx < 2 && dz < 2)
        return false;
    if (dx == 2 && dz == 2)
        return false;
    return dx < 3 && dz < 3;
}

void NavMeshLoadMgr::x_2() {
    if (_190)
        return;

    auto lock = sead::makeScopedLock(_130);
    if (!_10)
        return;
    if ((_180.x | _180.y) == 0)
        return;

    TileHandle* handle = _8 > 9 ? &_10->_360 : nullptr;
    if (handle->requestedLoad())
        x_3(handle, handle);
}

}  // namespace ksys::phys
