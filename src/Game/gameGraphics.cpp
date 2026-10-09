#include "Game/gameGraphics.h"
#include <prim/seadScopedLock.h>
#include <layer/aglLayer.h>

// NON_MATCHING: scheduling of the bounds and zero stores differs.
Unk_7100f35df8::Unk_7100f35df8() = default;

Unk_7100f35df8* Graphics::sub_7100F35E54() const {
    return _ae0;
}

void Graphics::sub_7100F35FA4(bool value, bool second) {
    if (second)
        _284.changeBit(12, value);
    else
        _284.changeBit(11, value);
    _280 |= 1;
}

void Graphics::sub_7100F2E06C() {
    _284.setBit(22);
}

void Graphics::sub_7100F35F50(agl::lyr::Layer* layer, bool value) {
    if (layer)
        layer->sub_7100B60DC4(value);
}

void Graphics::sub_7100F35F68(bool value) {
    _284.changeBit(14, value);
    if (_398) {
        if (value)
            _398->mFlags.setBit(0);
        else
            _398->mFlags.resetBit(0);
    }
}

void Graphics::sub_7100F2AF70(u8 map) {
    auto lock = sead::makeScopedLock(_f18);
    _f59 = map;
}

void Graphics::sub_7100F2AFAC(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5b = value;
}

void Graphics::sub_7100F2AFE8(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5d = value;
}

void Graphics::sub_7100F2B024(u8 value) {
    auto lock = sead::makeScopedLock(_f18);
    _f5f = value;
}

f32 Graphics::sub_7100F35F28() const {
    return _378->_18->_1520;
}

f32 Graphics::sub_7100F35F38() const {
    return _378->_18->_1524;
}

void Graphics::sub_7100F32AC8(sead::Camera* camera, void* unk) {
    _e08 = camera;
    _e10 = unk;
}

void Graphics::sub_7100F2F1C8(Unk_7100f35df8* settings) {
    if (_ae0)
        return;
    _ae0 = settings;
    settings->_0 = false;
    _b38->sub_71012920C4(0);
}

void Graphics::sub_7100F2F1E8(Unk_7100f35df8* settings) {
    if (!_ae0 || _ae0 == settings) {
        _ae0 = nullptr;
        _b38->sub_71012920C4(0);
    }
}

// NON_MATCHING: the mode byte store is scheduled before the comparisons.
void Unk_71012a20e0::sub_71012A2268(u32 mode) {
    const bool reset = _1b0 == 2 || mode == 2;
    _1b0 = mode;
    switch (_1b0) {
    case 0:
        _194 = 0.2f;
        break;
    case 1:
        _194 = 0.4f;
        break;
    case 2:
        _194 = 0.0f;
        break;
    }
    if (reset)
        _190 = _194;
}
