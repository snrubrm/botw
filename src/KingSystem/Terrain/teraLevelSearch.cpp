#include <math/seadMathCalcCommon.h>
#include <basis/seadNew.h>
#include <heap/seadHeap.h>
#include "KingSystem/System/DebugMessage.h"
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

void Unk_7101108AE8Flags::sub_71010F94F4(bool free_memory) {
    if (free_memory)
        _20.deleteGPUMemBlock();
    _0 &= ~2;
}

// NON_MATCHING: 1928 bytes against 1968; regalloc and stack slots.
bool Unk_71010FEDBC::sub_71010FA87C(CellRangeList* out, CellRangeBuffer* buffer,
                                    const ImageTypeMaybe& type, u32 index) {
    constexpr f32 Scale = 1.0f / 8192.0f;
    const auto to_fixed = [](f32 value) -> s16 {
        const s32 fixed = s32(value * 8192.0f);
        return fixed < -0x8000 ? -0x8000 : (fixed > 0x7ffe ? 0x7fff : fixed);
    };

    out->owner = this;
    out->count = 0;
    out->ranges = nullptr;

    Area& area = mAreas[index];
    const u32 num = (1 << mLevel) + 1;
    for (u32 y = 0; y < num; ++y) {
        for (u32 x = 0; x < num; ++x) {
            u8& flags = area.mCellFlags[y][x];
            if (flags & 0xf) {
                const u32 low = (flags & 0xf) + 1;
                flags = (flags & 0xf0) | ((low < 0xf ? low : 0xf) & 0xf);
            }
            if (flags >> 4) {
                const u32 high = (flags >> 4) + 1;
                flags = (flags & 0xf) | ((high < 0xf ? high : 0xf) << 4);
            }
        }
    }

    if (area._35 & 0xf) {
        const u8 count = (area._35 & 0xf) + 1;
        area._35 = (area._35 & 0xf0) | ((count < 0xf ? count : 0xf) & 0xf);
        return false;
    }

    const s32 start = buffer->count;
    const Area* prev = index != 0 ? &mAreas[index - 1] : nullptr;
    for (u32 y = 0; y < num; ++y) {
        for (u32 x = 0; x < num; ++x) {
            const Area::Cell& cell = area.mCells[y][x];
            switch (cell._8) {
            case 0:
                continue;
            case 3: {
                const u32 x0 = cell._9 & 0xf;
                const u32 x1 = cell._9 >> 4;
                const u32 y0 = cell._a & 0xf;
                const u32 y1 = cell._a >> 4;
                if (prev->mCells[y0][x0]._8 != 0 || prev->mCells[y0][x1]._8 != 0 ||
                    prev->mCells[y1][x0]._8 != 0 || prev->mCells[y1][x1]._8 != 0) {
                    continue;
                }
                break;
            }
            case 2:
                if (!cell._10->isImageFlagSetMaybe(type, 4))
                    continue;
                break;
            default:
                break;
            }

            const Area::Offset& offset_x = area.mOffsetsX[x];
            const Area::Offset& offset_y = area.mOffsetsY[y];
            bool added = false;
            if (static_cast<f32>(offset_x._0) * Scale < static_cast<f32>(offset_x._2) * Scale &&
                static_cast<f32>(cell._4) * Scale < static_cast<f32>(cell._6) * Scale) {
                CellRange& range = buffer->ranges[buffer->count++];
                range.rangeX = offset_x;
                range.rangeY = {cell._4, cell._6};
                range.x = x;
                range.y = y;
                range.area = index;
                range.kind = 3;
                added = true;
            }

            const f32 cell_x0 = static_cast<f32>(cell._0) * Scale;
            const f32 cell_x1 = static_cast<f32>(cell._2) * Scale;
            if (cell_x0 < cell_x1) {
                const f32 range_y0 = static_cast<f32>(offset_y._0) * Scale;
                const f32 range_y1 = static_cast<f32>(offset_y._2) * Scale;
                if (range_y0 < range_y1) {
                    const f32 cell_y0 = static_cast<f32>(cell._4) * Scale;
                    const f32 cell_y1 = static_cast<f32>(cell._6) * Scale;
                    Area::Offset rx = {cell._0, cell._2};
                    Area::Offset ry = offset_y;
                    if (cell_y0 < cell_y1) {
                        const f32 x0 = static_cast<f32>(offset_x._0) * Scale;
                        const f32 x1 = static_cast<f32>(offset_x._2) * Scale;
                        u32 mask_x;
                        if (sead::Mathf::abs(x0 - cell_x0) <= 0.001f)
                            mask_x = 1;
                        else
                            mask_x = sead::Mathf::abs(x1 - cell_x1) <= 0.001f ? 2 : 0;
                        u32 mask_y;
                        if (sead::Mathf::abs(cell_y0 - range_y0) <= 0.001f)
                            mask_y = 4;
                        else
                            mask_y = sead::Mathf::abs(cell_y1 - range_y1) <= 0.001f ? 8 : 0;

                        const u32 mask = mask_x | mask_y;
                        if (mask == 9 || mask == 10) {
                            rx = {to_fixed(cell_x0), to_fixed(cell_x1)};
                            ry = {to_fixed(range_y0), to_fixed(cell_y0)};
                        } else if (mask == 5 || mask == 6) {
                            rx = {to_fixed(cell_x0), to_fixed(cell_x1)};
                            ry = {to_fixed(cell_y1), to_fixed(range_y1)};
                        } else if (auto* debug = Terrain::instance()->_a50) {
                            auto entry = debug->_70.log(
                                "おかしい！ [ cur  1st = u : %f, %f @ v : %f, %f | 2nd = u : %f, %f @ v : %f, %f ]",
                                x0, x1, cell_y0, cell_y1, cell_x0, cell_x1, range_y0, range_y1);
                            if (entry.buffer)
                                entry.buffer->setDisplayTime(10.0f);
                        }
                    }

                    if (static_cast<f32>(rx._0) * Scale < static_cast<f32>(rx._2) * Scale &&
                        static_cast<f32>(ry._0) * Scale < static_cast<f32>(ry._2) * Scale) {
                        CellRange& range = buffer->ranges[buffer->count++];
                        range.rangeX = rx;
                        range.rangeY = ry;
                        range.x = x;
                        range.y = y;
                        range.area = index;
                        range.kind = 3;
                        continue;
                    }
                }
            }

            if (!added) {
                CellRange& range = buffer->ranges[buffer->count++];
                range.rangeX = {0x2000, 0};
                range.rangeY = {0x2000, 0};
                range.x = x;
                range.y = y;
                range.area = index;
                range.kind = 2;
            }
        }
    }

    if (start == buffer->count)
        return false;
    out->ranges = &buffer->ranges[start];
    out->count = buffer->count - start;
    return true;
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
