#include "KingSystem/ActorSystem/actBoneControl.h"

namespace ksys::act {

// Unk_7100d8557c lives in its own source file: BoneControl's forwarders (actBoneControl.cpp) tail-call
// these functions in the original instead of inlining them.
Unk_7100d8557c::Unk_7100d8557c(Actor* actor) : mActor(actor), _10(actor), _e8(actor) {}

void Unk_7100d8557c::sub_7100D8571C(const sead::Vector3f& pos) {
    _10._8 = pos;
    _e8._8 = pos;
}

void Unk_7100d8557c::sub_7100D85750() {
    if (_e8._24 & 1)
        _e8._24 |= 2;
    if (_10._d4 & 1)
        _10._d4 |= 2;
}

void Unk_7100d8557c::sub_7100D85774() {
    _10._d4 &= ~0xc02;
    _e8._24 &= ~0xc02;
}

void Unk_7100d8557c::sub_7100D85794() {
    _10._d4 |= 0x10;
    _e8._24 |= 0x10;
}

void Unk_7100d8557c::sub_7100D857B0() {
    _10._d4 &= ~0x10;
    _e8._24 &= ~0x10;
}

// NON_MATCHING: the original stores `_8` as an integer register (fmov w8, s0) and copies the value once
// (stp w8, w8); ours stores the floats separately and reloads *value (the members are probably not
// plain floats)
void Unk_7100d8557c::sub_7100D855B4(const f32& value) {
    if ((_10._d4 & 1) && (_e8._24 & 1)) {
        _8 = value;
        _c = value;
    } else {
        _8 = _c = (_10._d4 & 1) ? 1.0f : 0.0f;
    }
}

void Unk_7100d8557c::sub_7100D85600(const f32& value) {
    if ((_10._d4 & 1) && (_e8._24 & 1))
        _8 = value;
}

bool Unk_7100d8557c::sub_7100D855F0(res::BoneControl* res, sead::Heap* heap) {
    return _10.sub_7100D86170(res, heap);
}

bool Unk_7100d8557c::sub_7100D855F8(res::BoneControl* res, sead::Heap* heap) {
    return _e8.sub_7100D83090(res, heap);
}

void Unk_7100d8557c::sub_7100D8561C() {
    _10.sub_7100D86AF0();
    _e8.sub_7100D838A8();
}

void Unk_7100d8557c::sub_7100D85644() {
    _10.sub_7100D86BD8();
    _e8.sub_7100D839A8();
}

// NON_MATCHING: the original keeps `this` and `&_e8` in two callee-saved registers (add x20, x19, #0xe8
// after the first call); ours computes `&_e8` before the call
void Unk_7100d8557c::sub_7100D8566C() {
    auto& e8 = _e8;
    _10.sub_7100D87BF0(&_8);
    const f32 weight = 1.0f - _8;
    e8.sub_7100D83A0C(weight);
    e8.sub_7100D84E14();
}

// NON_MATCHING: same as sub_7100D8566C
void Unk_7100d8557c::sub_7100D856C4() {
    auto& e8 = _e8;
    _10.sub_7100D87264(&_8);
    const f32 weight = 1.0f - _8;
    e8.sub_7100D84C2C(weight);
    e8.sub_7100D84E14();
}

void Unk_7100d8557c::sub_7100D85EF4(bool on) {
    if (on) {
        _10._d4 |= 0x20;
        _e8._24 |= 0x20;
    } else {
        _10._d4 &= ~0x20;
        _e8._24 &= ~0x20;
    }
}

}  // namespace ksys::act
