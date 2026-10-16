#include <math/seadMathCalcCommon.h>
#include <basis/seadNew.h>
#include <heap/seadHeap.h>
#include "KingSystem/Terrain/teraResourceNode.h"

namespace ksys::tera {

void Unk_7101108AE8Flags::sub_71010F94F4(bool free_memory) {
    if (free_memory)
        _20.deleteGPUMemBlock();
    _0 &= ~2;
}

void Unk_71010FEDBC::sub_71010FCB04() {
    _0 = nullptr;
    mAreas = nullptr;
    _10 = 1000000.0f;
    _14 = 1000000.0f;
    _18 = 1.0f;
    _1c = 0;
    mNumAreas = 0;
    mLevel = 0;
    _1f = 0;
}

// NON_MATCHING: register allocation of the division and the merged 1000000 stores (as in
// sub_71010FEB94, which is inlined here).
void Unk_71010FEDBC::sub_71010FCB20(sead::Heap* heap, u8 num_areas, u32 size, s8 level) {
    mNumAreas = num_areas;
    mLevel = level;
    _18 = 1.0f / static_cast<f32>(size);
    _0 = new (heap, 0x20) AreaPos[16];
    mAreas = new (heap, 0x20) Area[mNumAreas];
    for (s32 i = 0; i < 16; ++i) {
        AreaPos& pos = _0[i];
        pos.pos = sead::Vector2f::zero;
        pos._8 = sead::Vector2f::zero;
        pos._10 = sead::Vector2f::zero;
        pos._18 = 1.0f;
    }
    sub_71010FEB94(0);
}

bool Unk_71010FEDBC::sub_71010FCFD0(u32 index) const {
    constexpr f32 cEpsilon = 1.0f / 524288.0f;
    if ((_0[index]._8 - mAreas[index]._8).squaredLength() > cEpsilon)
        return true;
    const sead::Vector2f& pos = _0[index].pos;
    const f32 distance = (pos - mAreas[index].center).squaredLength();
    const f32 scale = sead::Mathf::max(
        sead::Mathf::max(pos.x > 0.0f ? pos.x : -pos.x, pos.y > 0.0f ? pos.y : -pos.y), 1.0f);
    return distance > scale * cEpsilon;
}

// NON_MATCHING: the offset entries are stored as 16-bit halves here (merged 32 / 64-bit stores in the
// original) and the final center / origin stores are scheduled differently. The original also stores
// zero to center before setting it.
void Unk_71010FEDBC::Area::sub_71010FE480() {
    for (s32 i = 0; i < 5; ++i) {
        mOffsetsX[i] = {0x2000, 0};
        mOffsetsY[i] = {0x2000, 0};
    }
    mOffsetIndex = 0;
    _35 = (_35 & ~0x1f) | 0x10;
    for (s32 y = 0; y < 5; ++y) {
        for (s32 x = 0; x < 5; ++x) {
            mCellFlags[y][x] = 0;
            Cell& cell = mCells[y][x];
            cell._8 = 1;
            cell._0 = 0x2000;
            cell._2 = 0;
            cell._4 = 0x2000;
            cell._6 = 0;
            cell._10 = nullptr;
            cell._18 = sead::Vector2f::zero;
            cell._9 = 0x55;
            cell._a = 0x55;
        }
    }
    center = sead::Vector2f::zero;
    origin = sead::Vector2f::zero;
    size = 1.0f;
    center.set(1000000.0f, 1000000.0f);
    _8.set(10000.0f, 10000.0f);
}

s32 Unk_71010FEDBC::sub_71010FEDBC(const sead::Vector2f& pos, u32 count, f32 margin) const {
    const f32 range = _18 * static_cast<f32>(1 << mLevel) * 4.5f;
    while (count != 0) {
        --count;
        const Area& area = mAreas[count];
        const f32 dx = sead::Mathf::abs(pos.x - area.center.x);
        const f32 dy = sead::Mathf::abs(pos.y - area.center.y);
        if ((sead::Mathf::max(dx, dy) + margin) / (area.size * -0.5f) + 1.0f > range)
            return count;
    }
    return -1;
}


// NON_MATCHING: regalloc (the original keeps the constant 1 for the shift, the flag and the return in
// w0 and copies `this` to x8) and the order of the grid index computation.
bool Unk_71010FEDBC::sub_71010FE920(Result* result, const sead::Vector2f& pos, u32 index) const {
    const Area& area = mAreas[index];
    const f32 half = area.size * 0.5f;
    if (!(sead::Mathf::abs(pos.x - area.center.x) <= half))
        return false;
    if (!(sead::Mathf::abs(pos.y - area.center.y) <= half))
        return false;

    constexpr f32 Scale = 1.0f / 8192.0f;
    const f32 inv_size = 1.0f / area.size;
    const f32 x = (pos.x - area.origin.x) * inv_size;
    const f32 y = (pos.y - area.origin.y) * inv_size;
    const s32 level = 1 << mLevel;
    const u32 num = level + 1;
    const u32 offset_x = area.mOffsetIndex & 0xf;
    const u32 offset_y = area.mOffsetIndex >> 4;
    const u8 ix = u32(static_cast<f32>(offset_x) +
                      static_cast<f32>(level) *
                          (x - static_cast<f32>(area.mOffsetsX[offset_x]._2) * Scale) +
                      1.0f) %
                  num;
    const u8 iy = u32(static_cast<f32>(offset_y) +
                      static_cast<f32>(level) *
                          (y - static_cast<f32>(area.mOffsetsY[offset_y]._2) * Scale) +
                      1.0f) %
                  num;
    const f32 margin = _18;

    result->pos.x = x;
    result->pos.y = y;
    result->_8 = area.mCells[iy][ix]._10;
    result->_10 = area.mCells[iy][ix]._8;
    result->_14 = area.mCellFlags[iy][ix] & 0xf;
    result->_15 = area.mCellFlags[iy][ix] >> 4;
    result->_16 = true;
    if (result->_14 < 4) {
        const Area::Rect& rect = area.mRects[iy][ix];
        result->_16 = !(static_cast<f32>(rect.minX) * Scale <= x + margin &&
                        x - margin <= static_cast<f32>(rect.maxX) * Scale) &&
                      !(static_cast<f32>(rect.minY) * Scale <= y + margin &&
                        y - margin <= static_cast<f32>(rect.maxY) * Scale);
    }
    return true;
}

// NON_MATCHING: the two 1000000 stores are merged into one 64-bit store here.
void Unk_71010FEDBC::sub_71010FEB94(s32 start) {
    for (s32 i = start; i < mNumAreas; ++i) {
        mAreas[u32(i)].sub_71010FE480();
        _10 = 1000000.0f;
        _14 = 1000000.0f;
    }
}

}  // namespace ksys::tera
