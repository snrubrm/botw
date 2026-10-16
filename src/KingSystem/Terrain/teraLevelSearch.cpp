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

}  // namespace ksys::tera
