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
    if (_10 && _18) {
        delete[] static_cast<u8*>(_18);
        _18 = nullptr;
        _10 = 0;
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
