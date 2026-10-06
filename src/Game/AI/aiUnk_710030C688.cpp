#include <limits>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71007377D4.h"

f32 sub_710030C688(void*, const sead::Vector3f* pos, f32 limit) {
    f32 terrain_height = 0.0f;
    if (!sub_710072C494(&terrain_height, pos))
        return 0.0f;

    const sead::Vector3f from = *pos + sead::Vector3f(0.0f, 3.0f, 0.0f);
    const sead::Vector3f to(from.x, from.y - limit, from.z);
    sead::Vector3f hit_pos;
    f32 ground_height;
    if (sub_710072EA18(from, to, 0, &hit_pos, nullptr, nullptr, 0.0f)) {
        ground_height = hit_pos.y;
    } else {
        f32 height = -10000.0f;
        sub_710072C21C(&height, pos);
        ground_height = sead::Mathf::max(pos->y, height);
    }
    return terrain_height - ground_height;
}
