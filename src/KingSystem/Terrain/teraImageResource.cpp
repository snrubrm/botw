#include <common/aglTextureData.h>
#include <common/aglTextureFormatInfo.h>
#include <cstring>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Terrain/teraResourceNode.h"
#include "KingSystem/Terrain/teraSystem.h"

// Terrain image resources (TUs at 0x710110cbcc / 0x710110cfd0 / 0x710110d860 / 0x710110e0f4).

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

namespace ksys::tera {

Unk_710110d278::Unk_710110d278() = default;

Unk_710110d278::~Unk_710110d278() {
    freeBufferMaybe();
}

void Unk_710110d278::init(const InitArg& arg) {
    freeBufferMaybe();
    mImage = arg.image;
    _8 = arg.key;
    _a0 = arg._18;
    sub_710110D320(arg.heap);
}

// NON_MATCHING: loop shapes (store scheduling, the clearing loop is not unrolled the same way).
void Unk_710110d278::sub_710110D320(sead::Heap* heap) {
    u32 num_layers = _8->_a8.size();
    if (num_layers == 0)
        return;

    if (!(_a0 > sead::Mathf::epsilon())) {
        for (u32 i = 0; i != num_layers; ++i) {
            _20[i] = 0;
            _60[i] = 0;
        }
        return;
    }

    const u32 count = _a0 * _a0 * _8->_a4;
    if (_10 != count) {
        freeBufferMaybe();
        if (s32(count) > 0) {
            if (auto* buffer = new (heap, 8, std::nothrow) Entry[s32(count)]) {
                _10 = count;
                _18 = buffer;
            }
        }
    }

    u32 start = 0;
    num_layers = _8->_a8.size();
    if (num_layers != 0) {
        f32 total = 0.0f;
        for (u32 j = 0; j != num_layers; ++j)
            total += _8->_a8(j)->weight;
        u32 offset = 0;
        for (u32 i = 0; i != num_layers; ++i) {
            _20[i] = offset;
            offset += u32(static_cast<f32>(count) * (_8->_a8(s32(i))->weight / total));
            _60[i] = 0;
        }
        start = _8->_a8.size();
        if (start > 15)
            return;
    }
    for (u32 i = start; i != 16; ++i) {
        _20[i] = 0;
        _60[i] = 0;
    }
}

}  // namespace ksys::tera

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

Unk_710250dc50::Unk_710250dc50() = default;

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

Unk_710250dd60::Unk_710250dd60() = default;

void Unk_710250dd60::init(const ImageSizeMaybe& size) {
    mSize = size;
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

namespace ksys::tera {

// NON_MATCHING: scheduling in the level loop (the height clamp is computed before the width store).
void sub_710110DE64(TextureMipTableMaybe* table, const agl::TextureData& texture) {
    u8* image = static_cast<u8*>(texture.getImagePtr().getAddress());
    u8* mip = static_cast<u8*>(texture.getMipPtr().getAddress());
    const s32 width = texture.getWidth() < 2 ? 1 : texture.getWidth();
    const u32 pitch = texture.getSurface_1c();
    const s32 min_height = texture.getMinHeight_();
    const s32 tex_height = texture.getHeight();
    table->_150 = pitch;
    const s32 height = min_height > tex_height ? min_height : tex_height;
    table->_154 = agl::TextureFormatInfo::sub_7100B3B7F8(texture.getFormat()) & 0xff;
    table->num_levels = texture.getMipLevelNum();

    table->levels[0].address = image;
    table->levels[0].pitch = pitch;
    table->levels[0].width = width;
    table->levels[0].height = height;
    table->levels[0].half_texel_x = 0.5f / static_cast<f32>(width);
    table->levels[0].half_texel_y = 0.5f / static_cast<f32>(table->levels[0].height);

    for (u32 i = 1; i < texture.getMipLevelNum(); ++i) {
        const u32 size = texture.calcMipByteSize(i);
        auto& level = table->levels[i];
        level.address = mip;
        const s32 level_min_height = texture.getMinHeight_();
        const s32 level_tex_height = texture.getHeight() >> i;
        const u32 rows = level_min_height > level_tex_height ? level_min_height : level_tex_height;
        level.width = (u32(width) >> i) < 2 ? 1 : (u32(width) >> i);
        level.height = (u32(height) >> i) < 2 ? 1 : (u32(height) >> i);
        level.half_texel_x = 0.5f / static_cast<f32>(level.width);
        level.half_texel_y = 0.5f / static_cast<f32>(level.height);
        level.pitch = size / rows;
        mip += size;
    }
    for (u32 i = texture.getMipLevelNum(); i < 14; ++i) {
        table->levels[i].address = nullptr;
        table->levels[i].pitch = 0;
        table->levels[i].width = 0;
        table->levels[i].height = 0;
        table->levels[i].half_texel_x = 0;
        table->levels[i].half_texel_y = 0;
    }
}

}  // namespace ksys::tera
