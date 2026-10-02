#include "Game/Actor/actCameraUtil.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>

// Camera parameter globals (in .data / .bss). Nothing in the binary writes them or takes their
// address, yet the loads are not folded and do not go through the GOT: hidden visibility (as for
// ksys::gdt::detail::sCommonFlags0; KSYS_VISIBILITY_HIDDEN).
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474158 = 0.28f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247415c = -80.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474160 = 0.4f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474164 = 0.2f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474168 = 0.5f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247416c = 0.4f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474170 = 45.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474174 = 15.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474178 = 30.0f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247417c = 0.6f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474180 = 0.8f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474184 = 0.1f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474188 = 0.6f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247418c = 0.9f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474190 = 0.02f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474194 = 0.08f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102474198 = 0.2f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_710247419c = 0.1f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71024741a0 = 0.6f;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71025d24c8;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71025d24cc;
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d24d0;

bool sub_7100922030(u32 type, bool* is5) {
    if (type > 5)
        return false;
    if (is5)
        *is5 = type == 5;
    return true;
}

f32 sub_7100922058() {
    return 0.1f;
}

f32 sub_7100922064() {
    return 25000.0f;
}

bool sub_7100922070() {
    return false;
}

bool sub_7100922078() {
    return false;
}

s32 sub_7100922080() {
    return 16;
}

s32 sub_7100922088() {
    return 90;
}

f32 sub_7100922090() {
    return sUnk_7102474158;
}

f32 sub_710092209C() {
    return sUnk_710247415c;
}

f32 sub_71009220A8() {
    return sUnk_71025d24c8;
}

f32 sub_71009220B4() {
    return sUnk_7102474160;
}

f32 sub_71009220C0() {
    return sUnk_7102474164;
}

f32 sub_71009220CC() {
    return sUnk_7102474168;
}

f32 sub_71009220D8() {
    return sUnk_710247416c;
}

f32 sub_71009220E4() {
    return sUnk_7102474170;
}

f32 sub_71009220F0() {
    return sUnk_7102474174;
}

f32 sub_7100922120() {
    return 1.78f;
}

f32 sub_710092212C() {
    return 2.0f;
}

f32 sub_7100922134() {
    return 1.125f;
}

f32 sub_710092213C() {
    return 0.5f;
}

f32 sub_7100922144() {
    return 0.7f;
}

f32 sub_7100922150() {
    return 2.9f;
}

f32 sub_710092215C() {
    return 0.25f;
}

f32 sub_7100922164() {
    return 0.4f;
}

f32 sub_7100922170() {
    return 0.25f;
}

f32 sub_7100922178() {
    return 10.0f;
}

bool sub_7100922180() {
    return false;
}

f32 sub_7100922188() {
    return 0.005f;
}

f32 sub_7100922194() {
    return 0.0f;
}

f32 sub_710092219C() {
    return 0.023f;
}

f32 sub_71009221A8() {
    return 0.0f;
}

f32 sub_71009221B0() {
    return 5.0f;
}

bool sub_71009221B8() {
    return false;
}

f32 sub_71009221C0() {
    return 0.5f;
}

f32 sub_71009221C8() {
    return 0.005f;
}

f32 sub_71009221D4() {
    return 1.0f;
}

f32 sub_71009221DC() {
    return -1.5f;
}

f32 sub_71009221E4() {
    return 5.0f;
}

f32 sub_71009221EC() {
    return 0.1f;
}

f32 sub_71009221F8() {
    return 0.01f;
}

f32 sub_7100922204() {
    return 1.0f;
}

f32 sub_710092221C() {
    return 0.1f;
}

f32 sub_7100922228() {
    return 0.025f;
}

f32 sub_7100922234() {
    return 0.17f;
}

bool sub_7100922240() {
    return false;
}

bool sub_7100922248() {
    return false;
}

bool sub_7100922250() {
    return false;
}

bool sub_7100922258() {
    return true;
}

bool sub_7100922260() {
    return false;
}

bool sub_7100922268() {
    return false;
}

bool sub_7100922270() {
    return false;
}

bool sub_7100922278() {
    return false;
}

f32 sub_7100922280() {
    return 0.4f;
}

f32 sub_710092228C() {
    return 0.9f;
}

f32 sub_7100922298() {
    return 0.2f;
}

f32 sub_71009222A4() {
    return 0.7f;
}

f32 sub_71009222B0() {
    return 0.3f;
}

f32 sub_71009222BC() {
    return -30.0f;
}

f32 sub_71009222C4() {
    return 30.0f;
}

f32 sub_71009222CC() {
    return 2.0f;
}

f32 sub_71009222D4() {
    return 3.5f;
}

f32 sub_71009222DC() {
    return sUnk_7102474178;
}

f32 sub_71009222E8() {
    return 50.0f;
}

f32 sub_71009222F4() {
    return sUnk_710247417c;
}

f32 sub_7100922300() {
    return sUnk_7102474180;
}

f32 sub_710092230C() {
    return sUnk_7102474184;
}

f32 sub_7100922318() {
    return sUnk_7102474188;
}

f32 sub_7100922324() {
    return sUnk_710247418c;
}

f32 sub_7100922330() {
    return sUnk_7102474190;
}

f32 sub_710092233C() {
    return sUnk_71025d24cc;
}

f32 sub_7100922348() {
    return sUnk_7102474194;
}

f32 sub_7100922354() {
    return sUnk_7102474198;
}

f32 sub_7100922360() {
    return sUnk_710247419c;
}

f32 sub_710092236C() {
    return sUnk_71024741a0;
}

f32 sub_7100922378() {
    return 1.4f;
}

f32 sub_7100922384() {
    return 0.01f;
}

f32 sub_7100922390() {
    return 0.2f;
}

f32 sub_710092239C() {
    return 0.6f;
}

bool sub_71009223D8() {
    return false;
}

bool sub_71009223E0() {
    return false;
}

bool sub_71009223E8() {
    return false;
}

s32 sub_71009223F0() {
    return 0;
}

f32 sub_7100922418() {
    return 1.5f;
}

f32 sub_7100922420() {
    return 30.0f;
}

bool sub_7100922428() {
    return true;
}

f32 sub_71009220FC(s32 idx) {
    switch (idx) {
    case 0:
        return 0.8f;
    case 1:
        return 1.2f;
    case 2:
        return 1.6f;
    case 3:
        return 2.0f;
    case 4:
        return 2.4f;
    default:
        return 1.6f;
    }
}

void setFlagToOne() {
    sUnk_71025d24d0 = true;
}

void sub_71009223B8() {
    sUnk_71025d24d0 = false;
}

// NON_MATCHING: the original negates the loaded byte with mvn/and (no bool range assumption).
bool sub_71009223C4() {
    return !sUnk_71025d24d0;
}

f32 sub_71009223F8(s32 idx) {
    static const f32 sTable[] = {40.0f, 2.0f, 2.0f, 50.0f, 2.0f, 30.0f, 2.0f};
    return sTable[idx];
}

f32 sub_7100922408(s32 idx) {
    static const f32 sTable[] = {60.0f, 0.7f, 3.0f, 50.0f, 1.2f, 0.0f, 2.0f};
    return sTable[idx];
}

f32 angleStuff(f32 deg) {
    if (deg < -180.0f) {
        const f32 d = -180.0f - deg;
        const s32 i = d;
        const s32 m = i / 360 * 360;
        f32 n;
        if (i == d && i - m == 0)
            n = i;
        else
            n = m + (i < 0 ? -360 : 360);
        return n + deg;
    }
    if (deg >= 180.0f) {
        const f32 d = deg + 180.0f;
        const s32 i = d;
        const s32 m = i / 360 * 360;
        f32 n;
        if (i == d && i - m == 0)
            n = i;
        else
            n = m;
        return deg - n;
    }
    return deg;
}






















f32 sub_7100922530(const f32& deg) {
    return angleStuff(deg + 180.0f);
}

void sub_7100922600(f32& deg) {
    deg = angleStuff(deg + 180.0f);
}

f32 sub_71009226D8(const f32& deg) {
    return deg < 0 ? -deg : deg;
}

f32 sub_71009226EC(const f32& deg) {
    return std::cos(deg * (sead::Mathf::pi() / 180.0f));
}

namespace uking::act {

Unk_7100922700::Unk_7100922700(f32 r, f32 a, f32 b) {
    set(r, a, b);
}

Unk_7100922700& Unk_7100922700::set(f32 r, f32 a, f32 b) {
    _0 = r;
    _4 = angleStuff(a);
    _8 = angleStuff(b);
    sub_7100922B1C();
    return *this;
}

Unk_7100922700::Unk_7100922700(const sead::Vector3f& v) {
    set(v);
}

Unk_7100922700& Unk_7100922700::set(const sead::Vector3f& v) {
    const f32 x = v.x;
    const f32 y = v.y;
    const f32 z = v.z;
    const f64 xx = x * x;
    const f64 yy = y * y;
    const f64 zz = z * z;
    const f64 xz2 = xx + zz;
    const f64 len2 = yy + xz2;
    f32 xz = 0;
    if (xz2 > 0)
        xz = std::sqrt(xz2);
    f32 len = 0;
    if (len2 > 0)
        len = std::sqrt(len2);
    _0 = len;
    _4 = angleStuff((sead::Mathf::piHalf() - std::atan2(xz, y)) * (180.0f / sead::Mathf::pi()));
    _8 = angleStuff(std::atan2(x, z) * (180.0f / sead::Mathf::pi()));
    sub_7100922B1C();
    return *this;
}


// NON_MATCHING: the original keeps separate copies of the inlined angle wrapping in the two
// pitch branches (ours shares one).
Unk_7100922700* Unk_7100922700::sub_7100922B1C() {
    if (_0 < 0) {
        _0 = -_0;
        _4 = angleStuff(-_4);
        _8 = angleStuff(angleStuff(_8 + 180.0f));
    }
    if (_4 < -90.0f) {
        _4 = angleStuff(_4 + 180.0f);
        _8 = angleStuff(angleStuff(_8 + 180.0f));
    } else if (_4 > 90.0f) {
        _4 = angleStuff(-180.0f - _4);
        _8 = angleStuff(angleStuff(_8 + 180.0f));
    }
    return this;
}

sead::Vector3f Unk_7100922700::sub_7100923254() const {
    const f32 ca = std::cos(_4 * (sead::Mathf::pi() / 180.0f));
    const f32 sa = std::sin(_4 * (sead::Mathf::pi() / 180.0f));
    const f32 cb = std::cos(_8 * (sead::Mathf::pi() / 180.0f));
    const f32 sb = std::sin(_8 * (sead::Mathf::pi() / 180.0f));
    const f32 h = ca * _0;
    return {sb * h, sa * _0, cb * h};
}

}  // namespace uking::act
