#include "KingSystem/ActorSystem/actBoneControl.h"

namespace ksys::act {

BoneControl::BoneControl() = default;

void BoneControl::sub_7100D82F94() {
    if (_0)
        _0->sub_7100D85644();
}

void BoneControl::sub_7100D82FA4() {
    if (_0)
        _0->sub_7100D8566C();
}

void BoneControl::sub_7100D82FB4() {
    if (_0)
        _0->sub_7100D85794();
}

void BoneControl::sub_7100D82FE8(f32 value) {
    if (auto* unk = _0) {
        unk->_e8._28 = value;
        unk->_10._d0 = value;
    }
}

Unk_7100d860d8* sub_7100D82FFC(BoneControl* bone_control) {
    if (!bone_control)
        return nullptr;
    auto* unk = bone_control->_0;
    if (!unk)
        return nullptr;
    return &unk->_10;
}

bool sub_7100D83014(sead::Vector3f* out, const BoneControl* bone_control) {
    if (!bone_control)
        return false;
    auto* unk = bone_control->_0;
    if (!unk)
        return false;
    unk->_10.sub_7100D892C4(out);
    return true;
}

bool Unk_7100d860d8::sub_7100D87BE4() const {
    return _8c & 0x10;
}

void Unk_7100d860d8::sub_7100D89618(const f32& value) {
    if (_a8 == 0.0f)
        return;
    const f32 ratio = -value / _a8;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._104 = ratio * _18[i]._f4;
        _18[i]._160 = ratio * _18[i]._158;
    }
}

void Unk_7100d860d8::sub_7100D8969C(const f32& value) {
    if (_ac == 0.0f)
        return;
    const f32 ratio = value / _ac;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._108 = ratio * _18[i]._f8;
        _18[i]._164 = ratio * _18[i]._15c;
    }
}

void Unk_7100d860d8::sub_7100D8971C(const f32& value) {
    if (_b0 == 0.0f)
        return;
    const f32 ratio = value / _b0;
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._10c = ratio * _18[i]._fc;
}

void Unk_7100d860d8::sub_7100D8977C(const f32& value) {
    if (_b4 == 0.0f)
        return;
    const f32 ratio = -value / _b4;
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._110 = ratio * _18[i]._100;
}

void Unk_7100d860d8::sub_7100D8A9D0(const f32& value) {
    if (!(value <= 0.0f) && !(value > 1.0f))
        _9c = value;
}

void Unk_7100d860d8::sub_7100D8A9EC(const f32& value) {
    if (!(value <= 0.0f) && !(value > 1.0f))
        _a4 = value;
}

void Unk_7100d860d8::sub_7100D8AA08(const f32& value) {
    const f32 ratio = value / _c8;
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._144 = ratio * _18[i]._13c;
}

void Unk_7100d860d8::sub_7100D8AA60(const f32& value) {
    const f32 ratio = value / _cc;
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._148 = ratio * _18[i]._140;
}

void Unk_7100d860d8::sub_7100D8AAB8() {
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._144 = _18[i]._13c;
}

void Unk_7100d860d8::sub_7100D8AB00() {
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._148 = _18[i]._140;
}

#define SUM_FIELD(NAME, FIELD)                                                                    \
    f32 Unk_7100d860d8::NAME() const {                                                            \
        f32 sum = 0;                                                                              \
        for (s32 i = 0; i < _28; ++i)                                                             \
            sum += _18[i].FIELD;                                                                  \
        return sum;                                                                               \
    }

SUM_FIELD(sub_7100D8A25C, _104)
SUM_FIELD(sub_7100D8A2EC, _108)
SUM_FIELD(sub_7100D8A37C, _10c)
SUM_FIELD(sub_7100D8A40C, _110)
SUM_FIELD(sub_7100D8A49C, _124)
SUM_FIELD(sub_7100D8A52C, _128)
SUM_FIELD(sub_7100D8A5BC, _12c)
SUM_FIELD(sub_7100D8A64C, _130)

#undef SUM_FIELD

f32 Unk_7100d860d8::sub_7100D8A7FC(const s32& idx) const {
    if (idx < 0 || idx >= _18.size())
        return 0;
    return _18[idx]._138;
}

}  // namespace ksys::act
