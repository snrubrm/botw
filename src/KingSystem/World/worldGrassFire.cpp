#include "KingSystem/World/worldGrassFire.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <cstring>

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


// NON_MATCHING: record clearing and two-dimensional loops differ in store grouping and unrolling.
void Unk_710251cea8::resetCells() {
    sead::ScopedLock<sead::CriticalSection> lock(&_10);
    _288 = 0;
    _e98 = 0;
    for (auto& row : mCells) {
        for (auto& cell : row) {
            auto& record = *cell.mRecord;
            cell._14 = 0;
            cell.mFlags = 0;
            cell._11[0] = 0;
            cell._11[1] = 0;
            cell._11[2] = 0;
            cell._16 = 0xff;
            record._0 = 0;
            std::memset(record._4, 0, sizeof(record._4));
            record._1a = 0;
            record._18 = 0;
            record._14 = 0;
            std::memset(record._1c, 0, sizeof(record._1c));
            cell.mRecord->_4[0] = 0;
            cell.mRecord->_4[4] = 0;
            cell.mRecord->_4[8] = 0;
            cell.mRecord->_4[12] = 0;
            cell.mRecord->_3f = 0;
            cell.mRecord->_3c = 0;
            cell.mRecord->_3d = 0;
            cell.mRecord->_3e = 0;
        }
    }
    for (auto& row : mCellStates) {
        for (auto& state : row) {
            state._0 = 0;
            state._2 = 0;
        }
    }
    _4fdc4 = -1;
}

}  // namespace ksys::world
