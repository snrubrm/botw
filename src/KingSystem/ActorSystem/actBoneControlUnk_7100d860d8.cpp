#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::act {

// Unk_7100d860d8 lives in its own source file: BoneControl's helpers (actBoneControl.cpp) call these out of
// line in the original.
bool Unk_7100d860d8::sub_7100D87BE4() const {
    return _8c & 0x10;
}

// Set A (L / R / U / D).
// NON_MATCHING: regalloc (the original keeps the ratio in the divisor's register)
void Unk_7100d860d8::sub_7100D897E0(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _a8 -= _18[idx]._104;
    const f32 negated = -value;
    const f32 old = _18[idx]._104;
    _18[idx]._104 = negated;
    const f32 ratio = negated / old;
    _a8 += _18[idx]._104;
    _18[idx]._160 *= ratio;
}

// NON_MATCHING: regalloc (the original keeps the ratio in the divisor's register)
void Unk_7100d860d8::sub_7100D89884(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _ac -= _18[idx]._108;
    const f32 old = _18[idx]._108;
    _18[idx]._108 = value;
    const f32 ratio = value / old;
    _ac += _18[idx]._108;
    _18[idx]._164 *= ratio;
}

void Unk_7100d860d8::sub_7100D89924(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _b0 -= _18[idx]._10c;
    _18[idx]._10c = value;
    _b0 += _18[idx]._10c;
}

void Unk_7100d860d8::sub_7100D899A0(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _b4 -= _18[idx]._110;
    _18[idx]._110 = -value;
    _b4 += _18[idx]._110;
}

// Set B.
// NON_MATCHING: regalloc (the original keeps the ratio in the divisor's register)
void Unk_7100d860d8::sub_7100D89A20(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _b8 -= _18[idx]._124;
    const f32 negated = -value;
    const f32 old = _18[idx]._124;
    _18[idx]._124 = negated;
    const f32 ratio = negated / old;
    _b8 += _18[idx]._124;
    _18[idx]._170 *= ratio;
}

// NON_MATCHING: regalloc (the original keeps the ratio in the divisor's register)
void Unk_7100d860d8::sub_7100D89AC4(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _bc -= _18[idx]._128;
    const f32 negated = -value;
    const f32 old = _18[idx]._128;
    _18[idx]._128 = value;
    const f32 ratio = negated / old;
    _bc += _18[idx]._128;
    _18[idx]._174 *= ratio;
}

void Unk_7100d860d8::sub_7100D89B68(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _c0 -= _18[idx]._12c;
    _18[idx]._12c = value;
    _c0 += _18[idx]._12c;
}

void Unk_7100d860d8::sub_7100D89BE4(const f32& value, const s32& idx) {
    if (idx < 0 || idx >= _18.size())
        return;
    _c4 -= _18[idx]._130;
    _18[idx]._130 = -value;
    _c4 += _18[idx]._130;
}

void Unk_7100d860d8::sub_7100D89C64() {
    _a8 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._104 = _18[i]._f4;
        _a8 = _18[i]._f4 + _a8;
        _18[i]._160 = _18[i]._158;
    }
}

void Unk_7100d860d8::sub_7100D89CDC() {
    _ac = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._108 = _18[i]._f8;
        _ac = _18[i]._f8 + _ac;
        _18[i]._164 = _18[i]._15c;
    }
}

void Unk_7100d860d8::sub_7100D89D54() {
    _b0 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._10c = _18[i]._fc;
        _b0 = _18[i]._fc + _b0;
    }
}

void Unk_7100d860d8::sub_7100D89DC4() {
    _b4 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._110 = _18[i]._100;
        _b4 = _18[i]._100 + _b4;
    }
}

void Unk_7100d860d8::sub_7100D89E34() {
    _a8 = 0;
    _ac = 0;
    _b0 = 0;
    _b4 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._104 = _18[i]._f4;
        _a8 = _18[i]._f4 + _a8;
        _18[i]._160 = _18[i]._158;
        _18[i]._108 = _18[i]._f8;
        _ac = _18[i]._f8 + _ac;
        _18[i]._164 = _18[i]._15c;
        _18[i]._10c = _18[i]._fc;
        _b0 = _18[i]._fc + _b0;
        _18[i]._110 = _18[i]._100;
        _b4 = _18[i]._100 + _b4;
    }
}

void Unk_7100d860d8::sub_7100D89F60() {
    _b8 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._124 = _18[i]._114;
        _b8 = _18[i]._114 + _b8;
        _18[i]._170 = _18[i]._168;
    }
}

void Unk_7100d860d8::sub_7100D89FD8() {
    _bc = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._128 = _18[i]._118;
        _bc = _18[i]._118 + _bc;
        _18[i]._174 = _18[i]._16c;
    }
}

void Unk_7100d860d8::sub_7100D8A050() {
    _c0 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._12c = _18[i]._11c;
        _c0 = _18[i]._11c + _c0;
    }
}

void Unk_7100d860d8::sub_7100D8A0C0() {
    _c4 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._130 = _18[i]._120;
        _c4 = _18[i]._120 + _c4;
    }
}

void Unk_7100d860d8::sub_7100D8A130() {
    _b8 = 0;
    _bc = 0;
    _c0 = 0;
    _c4 = 0;
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._124 = _18[i]._114;
        _b8 = _18[i]._114 + _b8;
        _18[i]._170 = _18[i]._168;
        _18[i]._128 = _18[i]._118;
        _bc = _18[i]._118 + _bc;
        _18[i]._174 = _18[i]._16c;
        _18[i]._12c = _18[i]._11c;
        _c0 = _18[i]._11c + _c0;
        _18[i]._130 = _18[i]._120;
        _c4 = _18[i]._120 + _c4;
    }
}

// NON_MATCHING: scheduling / register naming of the limit selects (same instructions, different order)
// 0x7100d8a830: sets (or, if `relative`, rotates by the difference to the previous value and clamps)
// the left / right offset of the first node.
void Unk_7100d860d8::sub_7100D8A830(const f32& value, bool relative) {
    if (!(_d4 & 1))
        return;
    if (relative) {
        const f32 delta = util::sub_71011EF0CC(value) - _90;
        const f32 low = (_8c & 0x10) ? _18[0]._124 : _18[0]._104;
        const f32 angle = util::sub_71011EF0CC(_18[0]._134 - delta);
        const f32 high = (_8c & 0x10) ? _18[0]._128 : _18[0]._108;
        _18[0]._134 = sead::Mathf::clamp(angle, low, high);
    }
    _90 = util::sub_71011EF0CC(value);
    _8c |= 0x200;
}

// NON_MATCHING: same as sub_7100D8A830
// 0x7100d8a904: the same for the up / down offset (no angle wrapping).
void Unk_7100d860d8::sub_7100D8A904(const f32& value, bool relative) {
    if (!(_d4 & 1))
        return;
    if (relative) {
        const f32 delta = value - _94;
        const f32 low = (_8c & 0x10) ? _18[0]._130 : _18[0]._110;
        const f32 angle = util::sub_71011EF0CC(_18[0]._138 - delta);
        const f32 high = (_8c & 0x10) ? _18[0]._12c : _18[0]._10c;
        _18[0]._138 = sead::Mathf::clamp(angle, low, high);
    }
    _94 = value;
    _8c |= 0x200;
}

void Unk_7100d860d8::sub_7100D86AF0() {
    if (_18.isBufferReady()) {
        for (s32 i = 0; i < _18.size(); ++i)
            mActor->sub_71011DA868(&_18[i]._0);
        _18.freeBuffer();
    }
}

// NON_MATCHING: register naming of the two flag words in the tail
void Unk_7100d860d8::sub_7100D86BD8() {
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._138 = 0;
        _18[i]._134 = 0;
        sub_7100D86D28(&_18[i]);
    }
    _d4 &= ~0x3008;
    _8c &= ~0x3c;
}

void Unk_7100d860d8::sub_7100D86C90() {
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i]._138 = 0;
        _18[i]._134 = 0;
        sub_7100D86D28(&_18[i]);
    }
}

// NON_MATCHING: the original keeps the `_d4 & 0x30` and `_d4 & 1` tests separate (ours merges them into
// one `(_d4 & 0x31) == 1` test) and reads _8c as a halfword
void Unk_7100d860d8::sub_7100D88C5C() {
    if (!(_d4 & 0x30)) {
        if (_d4 & 1) {
            if (!(_8c & 0x400)) {
                for (s32 i = 0; i < _18.size(); ++i)
                    sub_7100D86D28(&_18[i]);
            }
        }
    }
}

bool Unk_7100d860d8::sub_7100D88CE0() const {
    return (_d4 & 6) == 6;
}

void Unk_7100d860d8::sub_7100D89070(bool reset) {
    _d4 |= 0x10;
    if (reset) {
        for (s32 i = 0; i < _18.size(); ++i) {
            _18[i]._134 = 0;
            _18[i]._138 = 0;
            _18[i]._178 = 0;
            _18[i]._0._68 = sead::Matrix34f::ident;
        }
    }
}

void Unk_7100d860d8::sub_7100D89324(sead::Vector3f* out) const {
    if (_d4 & 1) {
        out->x = _8.x;
        out->y = _8.y;
        out->z = _8.z;
    }
}

void Unk_7100d860d8::sub_7100D89550(const f32& value, const s32& idx) {
    if ((_d4 & 1) && idx >= 0 && idx < _18.size())
        _18[idx]._ec = value;
}

void Unk_7100d860d8::sub_7100D8958C(const f32& value, const s32& idx) {
    if ((_d4 & 1) && idx >= 0 && idx < _18.size())
        _18[idx]._f0 = value;
}

void Unk_7100d860d8::sub_7100D895C8() {
    if (!(_d4 & 1))
        return;
    for (s32 i = 0; i < _18.size(); ++i)
        _18[i]._ec = _18[i]._e4;
}

// 0x7100d88ec8: the neck offset of the actor's Hylian Mii (0 otherwise) plus the up / down offset _94.
f32 Unk_7100d860d8::sub_7100D88EC8() const {
    f32 offset = 0;
    if (auto* mii = mActor->getUMii()) {
        if (!*mii->getFFSD().no_use_ffsd && *mii->getBody().race == mii::UMii::Body::Race_Hylian)
            offset = *mii->getFace().eye_ctrl.neck_offset_ud * -sead::Mathf::deg2rad(1);
    }
    return offset + _94;
}

// NON_MATCHING: the original keeps the choice of the offset (the actor's Mii base offset or _74) as a branch
// with three separate component pointers; ours turns it into selects
// 0x7100d88cf4: the world position the spine controller aims at: the position of the head bone (or the last
// node's bone), with the actor's own x / z (_8c bit 0 / 2) or y (bit 1 / 3) used instead if requested,
// plus the offset _74 (or the Mii's base offset) rotated by the actor's matrix.
void Unk_7100d860d8::sub_7100D88CF4(sead::Vector3f* out) const {
    if (!(_d4 & 1))
        return;

    const gsys::BoneAccessKeyEx& bone = (_8c & 0x10) ? _18[_18.size() - 1]._a8 : _30;
    sead::Matrix34f mtx;
    mActor->getModel()
        ->getUnits()
        .unsafeAt(bone.getKey().model_unit_index)
        ->mModelUnit->getBoneWorldMatrix(&mtx, bone.getKey().bone_index);
    mtx.getTranslation(*out);

    if (!(_8c & 0x10)) {
        if (_8c & 1) {
            out->x = mActor->getMtx()(0, 3);
            out->z = mActor->getMtx()(2, 3);
        }
        if (_8c & 2)
            out->y = mActor->getMtx()(1, 3);

        const f32* ox = &_74.x;
        const f32* oy = &_74.y;
        const f32* oz = &_74.z;
        if (auto* mii = mActor->getUMii()) {
            if (!*mii->getFFSD().no_use_ffsd && *mii->getBody().race == mii::UMii::Body::Race_Hylian) {
                const sead::Vector3f& base_offset = *mii->getFace().eye_ctrl.base_offset;
                ox = &base_offset.x;
                oy = &base_offset.y;
                oz = &base_offset.z;
            }
        }
        const auto& m = mActor->getMtx();
        const f32 x = out->x, y = out->y, z = out->z;
        const f32 nx = *ox * m(0, 0) + *oy * m(0, 1) + *oz * m(0, 2) + x;
        const f32 ny = *ox * m(1, 0) + *oy * m(1, 1) + *oz * m(1, 2) + y;
        const f32 nz = *ox * m(2, 0) + *oy * m(2, 1) + *oz * m(2, 2) + z;
        out->x = nx;
        out->y = ny;
        out->z = nz;
    } else {
        if (_8c & 4) {
            out->x = mActor->getMtx()(0, 3);
            out->z = mActor->getMtx()(2, 3);
        }
        if (_8c & 8)
            out->y = mActor->getMtx()(1, 3);
    }
}

void Unk_7100d860d8::sub_7100D89260(sead::Matrix34f* out) const {
    if (!(_d4 & 1))
        return;
    const gsys::BoneAccessKeyEx& bone = (_8c & 0x10) ? _18[_18.size() - 1]._a8 : _30;
    mActor->getModel()
        ->getUnits()
        .unsafeAt(bone.getKey().model_unit_index)
        ->mModelUnit->getBoneWorldMatrix(out, bone.getKey().bone_index);
}

void Unk_7100d860d8::sub_7100D892C4(sead::Vector3f* out) const {
    if (_d4 & 1) {
        sub_7100D88CF4(out);
        *out -= mActor->getMtx().getTranslation();
    }
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
