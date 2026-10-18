#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace uking {

bool AutoPlacementInfo::x(const sead::Vector3f& pos, bool a2, u32 type_mask, MarginDelegate* a4) {
    const int px = int(pos.x) + 5000;
    int cx = px / 1000;
    if (cx > 9)
        cx = 9;
    if (px < -999)
        cx = 0;

    const int pz = int(pos.z) + 4000;
    int cz = pz / 1000;
    if (cz > 7)
        cz = 7;
    if (pz < -999)
        cz = 0;

    if (x_0(1.0f, cx, cz, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx - 1, cz - 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx, cz - 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx + 1, cz - 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx - 1, cz, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx + 1, cz, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx - 1, cz + 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx, cz + 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    return x_0(1.0f, cx + 1, cz + 1, pos, a2, type_mask, nullptr, a4) != -1;
}

// NON_MATCHING: record iteration, optional output, and height-index arithmetic are scheduled differently.
int AutoPlacementInfo::x_0(f32 scale, int cell_x, int cell_z, const sead::Vector3f& pos,
                           bool filter_types, u32 type_mask, QueryResults* results,
                           MarginDelegate* margin) {
    if (u32(cell_x) >= 10 || u32(cell_z) >= 8)
        return -1;
    const auto& cell = mGridEntries[cell_x][cell_z];
    const s32 count = cell.size();
    const Entry* entry = cell.getBufferPtr();
    for (s32 i = 0; i < count; ++i, ++entry) {
        if (filter_types && !(entry->type_mask & type_mask))
            continue;
        const f32 extra = margin ? margin->invoke(*entry) : 0.0f;
        const f32 dx = pos.x - entry->x;
        const f32 dz = pos.z - entry->z;
        const f32 radius = (extra + entry->radius) * scale;
        bool inside;
        if (entry->shape == 1) {
            const f32 c = std::cos(entry->yaw);
            const f32 s = std::sin(entry->yaw);
            const f32 x = dx * c - dz * s;
            const f32 z = dz * c + dx * s;
            const f32 half_depth = (extra + entry->half_depth) * scale;
            inside = -half_depth < z && x < radius && -radius < x && z < half_depth;
        } else {
            inside = dx * dx + dz * dz < radius * radius;
        }
        if (!inside)
            continue;
        if (!results || results->count >= 32)
            return i;
        auto& geometry = results->entries[results->count];
        const f32 height = mHasHeights ? mHeights[s32(entry - mEntries.getBufferPtr())] : 0.0f;
        geometry.position.set(entry->x, height, entry->z);
        geometry.rotation.set(0.0f, entry->yaw, 0.0f);
        geometry.scale.set(entry->radius, 1.0f, entry->half_depth);
        geometry.shape = entry->shape;
        geometry.type_mask = entry->type_mask;
        ++results->count;
    }
    return -1;
}

}  // namespace uking
