#include "KingSystem/Terrain/teraResourceNode.h"
#include <math/seadMathCalcCommon.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Terrain/teraAreaNode.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

Unk_710110d278* Unk_7101108460::getB() const {
    return mB;
}

Unk_710250dbc8* Unk_7101108460::getA() {
    return mA;
}

const Unk_710250dbc8* Unk_7101108460::getA() const {
    return mA;
}

// NON_MATCHING: store order of _b8 / _c3 / _c4.
Unk_7101106F44::Unk_7101106F44() {
    _8 = {1.0f, 0.0f};
    _10 = {1.0f, 0.0f};
    _20 = {0.0f, 0.0f};
    _28 = {0.0f, 0.0f};
    _30 = {0.0f, 0.0f};
    _38 = {0.0f, 0.0f};
}

Unk_7101108460* Unk_7101106F44::sub_7101108460(sead::Heap* heap, Unk_710110d278::Key* key) {
    auto* node = new (heap) Unk_7101108460;
    node->mA = new (heap) Unk_710250dbc8;
    node->mA->init(ImageSizeMaybe(1));
    node->mB = new (heap) Unk_710110d278;
    node->mB->init({heap, node->mA, key, 0});
    mNodes.pushBack(node);
    return node;
}

Unk_710250db28* Unk_7101106F44::sub_7101108564(sead::Heap* heap, u32 index, u32 size) {
    auto* image = new (heap) Unk_710250db28;
    image->init({index, size});
    mImages.pushBack(image);
    return image;
}

u16 Unk_7101108460::sub_7101108614() const {
    return mB->_8->id;
}

bool Unk_7101108460::sub_7101108624() const {
    return mB->_a0 > sead::Mathf::epsilon();
}

u32 sub_7101108AE8(sead::Vector2f* out_pos, s32* out_index, const sead::Vector2f& pos,
                   const Unk_7101108AE8Flags& flags, const Unk_71010FEDBC& areas, u32 max_level) {
    if ((flags._0 & 3) != 3)
        return 0;

    const u32 count = flags._2 < max_level ? flags._2 : max_level;
    out_pos->x = 0.0f;
    out_pos->y = 0.0f;
    *out_index = 0;
    *out_index = areas.sub_71010FEDBC(pos, count, 0.0f);
    while (*out_index != -1) {
        Unk_71010FEDBC::Result result;
        while (!areas.sub_71010FE920(&result, pos, *out_index) || !result._16) {
            if (*out_index == 0)
                return 0;
            --*out_index;
        }

        out_pos->x = result.pos.x;
        out_pos->y = result.pos.y;
        if (result.pos.x >= -1.0f && result.pos.x < 2.0f && result.pos.y >= -1.0f &&
            result.pos.y < 2.0f) {
            return result._10 == 0 ? 2 : 1;
        }

        if (*out_index == 0)
            return 0;
        *out_index = areas.sub_71010FEDBC(pos, *out_index - 1, 0.0f);
    }
    return 0;
}

// NON_MATCHING: the type-2 search loads the index before the list head (two instructions swapped).
void Unk_7101106F44::sub_71011080D4(const ImageTypeMaybe& type) {
    getImageMaybe(type)->sub_710110DD3C();
}

}  // namespace ksys::tera
