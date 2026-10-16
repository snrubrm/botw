#include <math/seadMathCalcCommon.h>
#include "KingSystem/Terrain/teraResourceNode.h"

namespace ksys::tera {

s32 Unk_71010FEDBC::sub_71010FEDBC(const sead::Vector2f& pos, u32 count, f32 margin) const {
    const f32 range = _18 * static_cast<f32>(1 << (_1e >> 5)) * 4.5f;
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
    const s32 level = 1 << (_1e >> 5);
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

}  // namespace ksys::tera
