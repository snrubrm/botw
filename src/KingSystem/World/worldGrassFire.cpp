#include "KingSystem/World/worldGrassFire.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>

namespace ksys::world {

Unk_710251cea8::~Unk_710251cea8() {
    _50.freeBuffer();
}

// NON_MATCHING: bounded cell iteration and floor arithmetic differ in scheduling.
void Unk_710251cea8::sub_71012E7990(f32 diameter, f32,
                                          const sead::Vector2f* position) {
    sead::ScopedLock<sead::CriticalSection> lock(&_10);
    f32 radius = diameter * 0.5f;
    if (radius > 10.0f)
        radius = 10.0f;
    const s32 min_x = sead::Mathi::max(29 - mGridPosition.x +
        sead::Mathf::floor((position->x - radius) / 10.0f), 0);
    const s32 min_y = sead::Mathi::max(29 - mGridPosition.y +
        sead::Mathf::floor((position->y - radius) / 10.0f), 0);
    const s32 max_x = sead::Mathi::min(29 - mGridPosition.x +
        sead::Mathf::floor((position->x + radius) / 10.0f), 58);
    const s32 max_y = sead::Mathi::min(29 - mGridPosition.y +
        sead::Mathf::floor((position->y + radius) / 10.0f), 58);
    for (s32 y = min_y; y <= max_y; ++y) {
        for (s32 x = min_x; x <= max_x; ++x) {
            auto& cell = mCells[(y + mCellIndices.y) % 59][(x + mCellIndices.x) % 59];
            if (cell.mFlags & 1)
                cell.mFlags |= 8;
        }
    }
}


}  // namespace ksys::world
