#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

// Camera utility code (0x71009212d0-0x710092e000): camera states, angle and polar-coordinate
// helpers, camera parameters and player-state queries used by the camera actor and the camera
// AI / action classes. Function names are placeholders (`sub_<address>`) unless the CSV names them.

// Camera parameters (0x7100922030-0x7100922428; constants or globals that are never written).
// 0x7100922030: whether `type` is valid (<= 5); `is5` (optional) receives `type == 5`.
bool sub_7100922030(u32 type, bool* is5);
// 0x7100922058: used when Unk_710079a8e8::_804 does not select _15c.
f32 sub_7100922058();
f32 sub_7100922064();
bool sub_7100922070();
bool sub_7100922078();
s32 sub_7100922080();
s32 sub_7100922088();
f32 sub_7100922090();
f32 sub_710092209C();
f32 sub_71009220A8();
f32 sub_71009220B4();
f32 sub_71009220C0();
f32 sub_71009220CC();
f32 sub_71009220D8();
f32 sub_71009220E4();
f32 sub_71009220F0();
f32 sub_7100922120();
f32 sub_710092212C();
f32 sub_7100922134();
f32 sub_710092213C();
f32 sub_7100922144();
f32 sub_7100922150();
f32 sub_710092215C();
f32 sub_7100922164();
f32 sub_7100922170();
f32 sub_7100922178();
bool sub_7100922180();
f32 sub_7100922188();
f32 sub_7100922194();
f32 sub_710092219C();
f32 sub_71009221A8();
f32 sub_71009221B0();
bool sub_71009221B8();
f32 sub_71009221C0();
f32 sub_71009221C8();
f32 sub_71009221D4();
f32 sub_71009221DC();
f32 sub_71009221E4();
f32 sub_71009221EC();
f32 sub_71009221F8();
f32 sub_7100922204();
f32 sub_710092221C();
f32 sub_7100922228();
f32 sub_7100922234();
bool sub_7100922240();
bool sub_7100922248();
bool sub_7100922250();
bool sub_7100922258();
bool sub_7100922260();
bool sub_7100922268();
bool sub_7100922270();
bool sub_7100922278();
f32 sub_7100922280();
f32 sub_710092228C();
f32 sub_7100922298();
f32 sub_71009222A4();
f32 sub_71009222B0();
f32 sub_71009222BC();
f32 sub_71009222C4();
f32 sub_71009222CC();
f32 sub_71009222D4();
f32 sub_71009222DC();
f32 sub_71009222E8();
f32 sub_71009222F4();
f32 sub_7100922300();
f32 sub_710092230C();
f32 sub_7100922318();
f32 sub_7100922324();
f32 sub_7100922330();
f32 sub_710092233C();
f32 sub_7100922348();
f32 sub_7100922354();
f32 sub_7100922360();
f32 sub_710092236C();
f32 sub_7100922378();
f32 sub_7100922384();
f32 sub_7100922390();
f32 sub_710092239C();
bool sub_71009223D8();
bool sub_71009223E0();
bool sub_71009223E8();
s32 sub_71009223F0();
f32 sub_7100922418();
f32 sub_7100922420();
bool sub_7100922428();
// 0x71009220fc: 0.8 + 0.4 * idx for idx in [0, 4], else 1.6.
f32 sub_71009220FC(s32 idx);
// 0x71009223a8 (CSV setFlagToOne) / 0x71009223b8: set / clear a global flag; 0x71009223c4: whether
// it is clear.
void setFlagToOne();
void sub_71009223B8();
bool sub_71009223C4();
f32 sub_71009223F8(s32 idx);
f32 sub_7100922408(s32 idx);

// 0x7100922468 (CSV angleStuff): wraps an angle in degrees into [-180, 180).
f32 angleStuff(f32 deg);
// Helpers on an angle in degrees passed by reference (callers pass fields such as
// Unk_7100922700::_4 / _8 or Unk_710079a8e8::_1b8):
// 0x7100922530: angleStuff(deg + 180).
f32 sub_7100922530(const f32& deg);
// 0x7100922600: deg = angleStuff(deg + 180).
void sub_7100922600(f32& deg);
// 0x71009226d8: |deg|.
f32 sub_71009226D8(const f32& deg);
// 0x71009226ec: cos(deg).
f32 sub_71009226EC(const f32& deg);

namespace uking::act {

// Placeholder name (out-of-line ctor 0x71009214b8, in the camera utility code): a camera state
// (position, look-at, up and four parameters). Camera embeds many of them (Camera::_860 starts with
// six; camera actions read state 0 at Camera+0x860 / +0x86c).
class Unk_71009214b8 {
public:
    Unk_71009214b8();

    // 0x7100921524
    void set(const sead::Vector3f& pos, const sead::Vector3f& at, const sead::Vector3f& up, f32 a24,
             f32 a28, f32 a2c, f32 a30, f32 a34);
    // 0x710092156c
    f32 sub_710092156C(f32 a1, f32 a2, const sead::Vector3f& pos) const;
    // 0x7100921710: transforms `pos` by the inverse of the view matrix (false if it is degenerate).
    bool sub_7100921710(const sead::Vector3f& pos, sead::Vector3f* out) const;
    // 0x7100921818: the view (look-at) matrix (false if degenerate).
    bool sub_7100921818(sead::Matrix34f* out) const;
    // 0x7100921a24: radius of the near plane (from _24, _2c and _30) plus `offset`.
    f32 sub_7100921A24(f32 offset) const;
    // 0x7100921a90: the point at distance _30 from the position towards the look-at point.
    void sub_7100921A90(sead::Vector3f* out) const;
    // 0x7100921b48 (CSV: mis-named agl::sdw::ShadowUtil::calcViewDir duplicate): moves the
    // position to `p` plus _30 in the direction from the old position to `p`.
    void sub_7100921B48(const sead::Vector3f& p);
    // 0x7100921c04 / 0x7100921c50: elevation (negated) / azimuth of the look direction (degrees).
    f32 sub_7100921C04() const;
    f32 sub_7100921C50() const;
    // 0x7100921c98: _28 in degrees.
    f32 sub_7100921C98() const;
    // 0x7100921cac: validity check; `flags` (optional) receives the error bits (NaN components,
    // _24 outside (0, pi), non-positive _2c/_30/_34, position == look-at, _34 <= _30).
    void sub_7100921CAC(u32* flags) const;

    /* 0x00 */ sead::Vector3f _0 = sead::Vector3f::zero;  // position
    /* 0x0c */ sead::Vector3f _c = sead::Vector3f::ez;    // look-at point
    /* 0x18 */ sead::Vector3f _18 = sead::Vector3f::ey;   // up
    /* 0x24 */ f32 _24 = 1.5;  // an angle in radians (the Camera ctor sets pi/4 for Camera::_860._0)
    /* 0x28 */ f32 _28 = 0;    // an angle in radians (sub_7100921C98)
    /* 0x2c */ f32 _2c = 1.7;
    /* 0x30 */ f32 _30 = 1.0;
    /* 0x34 */ f32 _34 = 100.0;
};
KSYS_CHECK_SIZE_NX150(Unk_71009214b8, 0x38);

// Placeholder name (out-of-line ctors 0x7100922700 (r, a, b) and 0x71009228a8 (vector)): a polar
// coordinate in degrees: distance, elevation (_4, from the XZ plane towards +Y) and azimuth (_8,
// around Y from +Z towards +X).
class Unk_7100922700 {
public:
    Unk_7100922700(f32 r, f32 a, f32 b);
    explicit Unk_7100922700(const sead::Vector3f& v);

    Unk_7100922700& set(f32 r, f32 a, f32 b);
    Unk_7100922700& set(const sead::Vector3f& v);
    // 0x7100922b1c: makes _0 non-negative and _4 within [-90, 90] (adjusting _8).
    Unk_7100922700* sub_7100922B1C();
    // 0x7100923254: the Cartesian vector.
    sead::Vector3f sub_7100923254() const;

    /* 0x0 */ f32 _0;
    /* 0x4 */ f32 _4 = 0;
    /* 0x8 */ f32 _8 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7100922700, 0xc);

}  // namespace uking::act
