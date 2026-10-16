#include "KingSystem/Terrain/teraResourceNode.h"
#include <math/seadMathCalcCommon.h>
#include "Game/gameUnkRttiPlaceholders.h"
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

}  // namespace ksys::tera

using ksys::tera::ImageSizeMaybe;
using ksys::tera::ImageTypeMaybe;
using ksys::tera::getImageSizeMaybe;

Unk_710250db28::Unk_710250db28()
    : sead::TListNode<Unk_710250db28*>(this), mSize(0x0a), mIndex(0xff) {}

void Unk_710250db28::init(const InitArg& arg) {
    mIndex = arg.index;
    mSize = arg.size;
}

s32 Unk_710250db28::m4() {
    return getImageType().sub_710114A5A0();
}

s32 Unk_710250db28::m5() {
    return getImageType().sub_710114A5A8();
}

s32 Unk_710250db28::m6() {
    return getImageType().sub_710114A5CC();
}

s32 Unk_710250db28::m7() {
    return getImageType().sub_710114A62C();
}

u16 Unk_710250db28::m8() {
    return getImageType().sub_710114A650(m9(), m10());
}

u32 Unk_710250db28::m9() {
    return getImageSizeMaybe(ImageSizeMaybe(mSize));
}

Unk_710250dbc8::Unk_710250dbc8() = default;

void Unk_710250dbc8::init(const ImageSizeMaybe& size) {
    mSize = size;
}

s32 Unk_710250dbc8::m4() {
    return getImageType().sub_710114A5A0();
}

s32 Unk_710250dbc8::m5() {
    return getImageType().sub_710114A5A8();
}

s32 Unk_710250dbc8::m6() {
    return getImageType().sub_710114A5CC();
}

s32 Unk_710250dbc8::m7() {
    return getImageType().sub_710114A62C();
}

u16 Unk_710250dbc8::m8() {
    return getImageType().sub_710114A650(m9(), m10());
}

u32 Unk_710250dbc8::m9() {
    return getImageSizeMaybe(mSize);
}

void Unk_710250dbc8::m13(void* unused, const void* src, u32 size) {
    Unk_710250dcd8::m13(unused, src, size);
}

s32 Unk_710250dc50::m4() {
    return ksys::tera::sUnk_7101EC54AC.sub_710114A5A0();
}

s32 Unk_710250dc50::m5() {
    return ksys::tera::sUnk_7101EC54AC.sub_710114A5A8();
}

s32 Unk_710250dc50::m6() {
    return ksys::tera::sUnk_7101EC54AC.sub_710114A5CC();
}

s32 Unk_710250dc50::m7() {
    return ksys::tera::sUnk_7101EC54AC.sub_710114A62C();
}

u16 Unk_710250dc50::m8() {
    return ksys::tera::sUnk_7101EC54AC.sub_710114A650(m9(), m10());
}

u32 Unk_710250dc50::m9() {
    return ksys::tera::Terrain::instance()->_3d0;
}

s32 Unk_710250dd60::m4() {
    return ksys::tera::sUnk_7101EC54B4.sub_710114A5A0();
}

s32 Unk_710250dd60::m5() {
    return ksys::tera::sUnk_7101EC54B4.sub_710114A5A8();
}

s32 Unk_710250dd60::m6() {
    return ksys::tera::sUnk_7101EC54B4.sub_710114A5CC();
}

s32 Unk_710250dd60::m7() {
    return ksys::tera::sUnk_7101EC54B4.sub_710114A62C();
}

u16 Unk_710250dd60::m8() {
    return ksys::tera::sUnk_7101EC54B4.sub_710114A650(m9(), m10());
}

u32 Unk_710250dd60::m9() {
    return getImageSizeMaybe(mSize);
}
