// TU of Camera's 0x820-byte sub-object (Unk_710079a8e8, ctor 0x710079a8e8) and its flag / easing
// helper types (0x710079a8e8-0x710079c5b0): separate from the Camera TU, which calls these out of
// line (e.g. Camera::sub_7100794FD0 tail-calls Unk_710079b62c::sub_710079C0CC).
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCamera.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::act {

void Unk_710079b62c::sub_710079B62C(u32 mask) {
    _0 |= mask;
}

bool Unk_710079b62c::sub_710079BFB0(u32 mask) const {
    return (_0 & mask) == 0;
}

bool Unk_710079b62c::sub_710079C0CC(u32 mask) const {
    return (_0 & mask) != 0;
}

bool Unk_710079adc8::sub_710079ADC8(u32 mask) const {
    return (_0 & mask) == 0;
}

void Unk_710079adc8::sub_710079AE20(u32 mask) {
    _0 |= mask;
}

void Unk_710079adc8::sub_710079AE40(u32 mask) {
    _0 &= ~mask;
}

bool Unk_710079adc8::sub_710079AE50(u32 mask) const {
    return (_0 & mask) != 0;
}

bool Unk_710079c1c8::sub_710079C1C8(u8 mask) const {
    return (_0 & mask) != 0;
}

bool Unk_710079c1f4::sub_710079C1F4(u8 mask) const {
    return (_0 & mask) != 0;
}

void Unk_710079c1c8::sub_710079C1DC(u8 mask) {
    _0 |= mask;
}

void Unk_710079c1c8::sub_710079C1EC() {
    _0 = 0;
}

void Unk_710079c1f4::sub_710079C208(u8 mask) {
    _0 |= mask;
}

void Unk_710079c1f4::sub_710079C218() {
    _0 = 0;
}

void Unk_710079a8e8::sub_710079AD90() {
    _7f0[0] = -1.0;
    _7f0[1] = -1.0;
}

f32 Unk_710079a8e8::sub_710079ADA0() const {
    if ((_804._0 & 0x6000) == 0x2000)
        return _15c;
    return sub_7100922058();
}

bool Unk_710079a8e8::sub_710079ADBC() const {
    return _804.sub_710079AE50(0x2000);
}

void Unk_710079a8e8::sub_710079AE30() {
    _804.sub_710079AE40(0x2000);
}

void Unk_710079a8e8::sub_710079AEE0() {
    _1a0.set(0.0f, 0.0f, 0.0f);
    _1b8 = angleStuff(0.0f);
    _1bc = angleStuff(0.0f);
    _1c0 = 0.0f;
    _1c4 = 0.0f;
    _1d0.sub_710079C510(1.0f);
}

void Unk_710079a8e8::sub_710079AED0() {
    _804.sub_710079AE40(0x8000);
}

bool Unk_710079a8e8::sub_710079B63C(u32 mask) const {
    if (_800.sub_710079C0CC(mask))
        return false;
    return _7fc.sub_710079C0CC(mask);
}

void Unk_710079a8e8::sub_710079BC8C() {
    _170 = false;
    _180 = false;
}

void Unk_710079a8e8::sub_710079BD2C() {
    _240.reset();
    _804.sub_710079AE40(0x800);
}

void Unk_710079a8e8::sub_710079BD5C() {
    _7fc.sub_710079B62C(0x20);
}

void Unk_710079a8e8::sub_710079BD6C(f32 value) {
    _190 = sead::Mathf::clamp(value, 0.0f, 1.0f);
}

void Unk_710079a8e8::sub_710079BD98() {
    _190 = -1.0;
}

bool Unk_710079a8e8::sub_710079BDA4() const {
    return _190 >= 0.0f && _190 <= 1.0f;
}

void Unk_710079a8e8::sub_710079BE34() {
    _6f0 = nullptr;
    _6f8 = 0;
}

void Unk_710079a8e8::sub_710079BEA8() {
    _72c._3c = 2;
}

void Unk_710079a8e8::sub_710079BEB4() {
    _7b9 = 0;
}

bool Unk_710079a8e8::sub_710079BEBC() const {
    return _7e0 != -1.0f;
}

f32 Unk_710079a8e8::sub_710079BF0C() const {
    return _7e0;
}

void Unk_710079a8e8::sub_710079BF14() {
    _7e0 = -1.0;
}

bool Unk_710079a8e8::sub_710079BF20() const {
    return _7e4 != -1.0f;
}

void Unk_710079a8e8::sub_710079BF34(f32 value) {
    if (value < 0.0f || std::isnan(value))
        return;
    _7e4 = value;
}

void Unk_710079a8e8::sub_710079BF58() {
    _7e4 = -1.0;
}

void Unk_710079a8e8::sub_710079C0AC() {
    if (!_7fc.sub_710079C0CC(0x80000))
        _804.sub_710079AE40(0x10000);
    else
        _804.sub_710079AE20(0x10000);
}


void Unk_710079a8e8::sub_710079C0DC(int idx, f32 value) {
    _7f0[idx] = value;
}

bool Unk_710079a8e8::sub_710079C0F4(f32* out) const {
    for (f32 value : _7f0) {
        if (value >= 0.0f) {
            *out = value;
            return true;
        }
    }
    return false;
}

bool Unk_710079a8e8::sub_710079C120(u8 mask) const {
    return _80c.isOn(mask);
}

bool Unk_710079a8e8::sub_710079C134(u8 mask) const {
    return _80c.isOff(mask);
}

void Unk_710079a8e8::sub_710079C148(u8 mask) {
    _80c.set(mask);
}

void Unk_710079a8e8::sub_710079C158(u8 mask, bool on) {
    _80c.change(mask, on);
}

void Unk_710079a8e8::sub_710079C17C() {
    _80c.makeAllZero();
}

bool Unk_710079a8e8::sub_710079C184(u32 mask) const {
    if (_808.sub_710079AE50(mask))
        return false;
    return _804.sub_710079AE50(mask);
}


void Unk_710079a8e8::sub_710079ADD8(f32 value) {
    if (ksys::util::sub_71011F0F88(value) || value <= 0.0f)
        return;
    _15c = value;
    _804.sub_710079AE20(0x2000);
}

void Unk_710079a8e8::sub_710079AE88(f32 value) {
    if (ksys::util::sub_71011F0F88(value) || value <= 0.0f)
        return;
    _160 = value;
    _804.sub_710079AE20(0x8000);
}

void Unk_710079a8e8::sub_710079BC98() {
    // C++14 evaluation order: the original evaluates the destination first
    _240.operator=(_230);
    _39c = _354;
    _3cc = _384;
    _3d8 = _390;
    _804.sub_710079AE20(0x800);
}

void Unk_710079a8e8::sub_710079BED0(f32 value) {
    if (ksys::util::sub_71011F0F88(value) || value < 0.0f)
        return;
    _7e0 = value;
}

}  // namespace uking::act
