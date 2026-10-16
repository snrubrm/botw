#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Terrain/teraAreaNode.h"

namespace ksys::tera {

u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    return sub_710110AA5C(0.0f, Terrain::instance()->_3cc, out_height, xz, &info->_20, info);
}

// NON_MATCHING: register allocation.
Unk_7101106F44* System::sub_7101115218(sead::Vector2f* out_center, f32* out_size,
                                       const sead::Vector2f& pos, u32 levels) {
    Unk_7101106F44* node = _8;
    if (!node)
        return nullptr;

    sead::Vector2f center = _1c;
    f32 size = _24;
    while (true) {
        const f32 half = size * 0.5f;
        if (center.x - half <= pos.x && pos.x < half + center.x && center.y - half <= pos.y &&
            pos.y < half + center.y) {
            break;
        }
        center.x += node->_1 == 1 || node->_1 == 3 ? -half : half;
        center.y += node->_1 == 2 || node->_1 == 3 ? -half : half;
        size += size;
        node = node->mParent;
        ++levels;
        if (!node)
            return nullptr;
    }

    for (u32 i = 0; i < levels; ++i) {
        const s32 index = (pos.x >= center.x) | (pos.y >= center.y) << 1;
        Unk_7101106F44* child = node->mChildren[index];
        if (!child)
            break;
        size *= 0.5f;
        center.y += size * sUnk_7101EC503C[index].y;
        center.x += size * sUnk_7101EC503C[index].x;
        node = child;
    }

    *out_center = center;
    *out_size = size;
    return node;
}

// NON_MATCHING: the original loads the offset pair with one ldp before multiplying.
void Unk_7101106F44::sub_7101120374(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                                    const ImageTypeMaybe& type) {
    Unk_7101106F44* area = *node;
    while (area) {
        if (area->hasImageMaybe(type)) {
            const Unk_710250dcd8* image = area->getImageMaybe(type);
            if (image && image->_8 & 4)
                break;
        }
        Unk_7101106F44* parent = area->mParent;
        const s32 slot = parent ? area->_1 : 0;
        *center -= sUnk_7101EC503C[slot] * *size;
        *size += *size;
        area = parent;
    }
    *node = area;
}

// NON_MATCHING: the original loads the offset pair with one ldp before multiplying.
void Unk_7101106F44::sub_7101120598(Unk_7101106F44** node, sead::Vector2f* center, f32* size,
                                    const ImageTypeMaybe& type) {
    Unk_7101106F44* area = *node;
    while (area && !area->hasImageMaybe(type)) {
        Unk_7101106F44* parent = area->mParent;
        const s32 slot = parent ? area->_1 : 0;
        *center -= sUnk_7101EC503C[slot] * *size;
        *size += *size;
        area = parent;
    }
    *node = area;
}

}  // namespace ksys::tera
