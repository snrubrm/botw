#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/MathUtil.h"
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

namespace sead {
class Viewport;
}

namespace ksys::act {
class ActorConstDataAccess;
class ActorLinkConstDataAccess;
class BaseProcLink;
class PlayerBase;
}  // namespace ksys::act

namespace ksys::phys {
class SystemGroupHandler;
}

namespace uking::act {
class Camera;
class Unk_71009214b8;
}  // namespace uking::act

// Camera math helpers (TU 0x7100924be4-).
// 0x7100924be4: acquires the player (PlayerInfo's player link) into `accessor`.
void sub_7100924BE4(ksys::act::ActorConstDataAccess* accessor);
// 0x7100924c08: 2 * atan2(tan(fovy / 2) * aspect, 1).
f32 sub_7100924C08(f32 fovy, f32 aspect);
// 0x7100924c40: `in` scaled by half the size of the camera manager's viewport (if any).
void sub_7100924C40(sead::Vector2f* out, const sead::Vector2f& in);
// 0x7100924c94: min / max of a and b.
void sub_7100924C94(f32 a, f32 b, f32* min, f32* max);
// 0x7100924cac: clamps to [-89.9, 89.9].
f32 sub_7100924CAC(f32 value);
// 0x7100924cdc: sub_7100924C94 of the values clamped with sub_7100924CAC.
void sub_7100924CDC(f32 a, f32 b, f32* min, f32* max);
// 0x7100924d40: at least 0.01.
f32 sub_7100924D40(f32 value);
// 0x7100924d50: clamps to [0.1, 179.9] degrees (in radians).
f32 sub_7100924D50(f32 value);
// 0x7100924d80: clamps to [0, 1].
f32 sub_7100924D80(f32 value);
// 0x7100924da4: sub_7100924C94 of the values clamped with sub_7100924D80.
void sub_7100924DA4(f32 a, f32 b, f32* min, f32* max);
// 0x7100924dfc: wraps degrees into [-180, 180] by adding / subtracting 360.
f32 sub_7100924DFC(f32 deg);
// 0x7100924e48: the horizontal vector perpendicular to `dir` (z, 0, -x), normalized and scaled by
// `scale` (false if dir has no horizontal component).
bool sub_7100924E48(const sead::Vector3f& dir, const f32& scale, sead::Vector3f* out);
// 0x7100924f04: sub_71009222E8().
f32 sub_7100924F04();
// 0x7100924f08: the right stick of MaskController controller 3 with a dead zone (0.005) and a
// response curve (length raised to sub_710092212C()); zero without a controller or when a component
// is NaN / infinite.
void sub_7100924F08(sead::Vector2f* stick);
// 0x7100925110: whether axis `axis` of `mtx` is less than 60 degrees from the horizontal plane.
bool sub_7100925110(const sead::Matrix33f& mtx, int axis);
// 0x71009251c4: Camera::_848 (secondary base _8), else the VFR delta frame (1 without VFR).
f32 sub_71009251C4(const uking::act::Camera* camera);
// 0x710092523c: 1 - (1 - t)^exponent.
f32 sub_710092523C(f32 exponent, f32 t);
// Camera player-state helpers (TU 0x7100926430-).
// 0x7100926430: searches the ground / water height below `pos` (`count` probes); a4-a6 are distances
// (parameter order between the floats and the others is a guess).
bool sub_7100926430(const sead::Vector3f& pos, int count, f32* out, f32 a4, f32 a5, f32 a6);
// 0x71009269f8: sub_7100926430(pos, 3, out, 1, 1, 5).
bool sub_71009269F8(const sead::Vector3f& pos, f32* out);
// 0x7100925654: collision check of the camera state `state` against `prev` (sphere cast; `handler`
// is the system group handler of an actor to ignore); true if it was hit.
bool sub_7100925654(uking::act::Unk_71009214b8* state, const uking::act::Unk_71009214b8& prev,
                    ksys::phys::SystemGroupHandler* handler);
// 0x7100926210: the look-at position of the actor (acc::PlayerBase::getLookAtPosForCamera for the
// player, else getPreviousPos2); false (out unchanged) if it is NaN / infinite.
bool sub_7100926210(const ksys::act::ActorConstDataAccess& accessor, sead::Vector3f* out);
// 0x7100926a14 / 0x7100926a2c: PlayerInfo::getPlayer() / getPlayer_() (null without PlayerInfo).
ksys::act::PlayerBase* sub_7100926A14();
ksys::act::PlayerBase* sub_7100926A2C();
// 0x7100926a50: acquires the player into `accessor` (same as sub_7100924BE4).
void sub_7100926A50(ksys::act::ActorConstDataAccess* accessor);
// 0x7100926a74 / 0x7100926a9c: acquires the player's horse (PlayerInfo's horse link).
bool sub_7100926A74(ksys::act::ActorConstDataAccess* accessor);
bool sub_7100926A9C(ksys::act::ActorConstDataAccess* accessor);
// 0x7100926cb0: acc::PlayerBase m190 || m191.
bool sub_7100926CB0();
// 0x7100926d24: acc::PlayerBase isRidingHorse || x_15 || x_17 || (x_16 && !x_17 && !x_18).
bool sub_7100926D24();
// 0x7100926fd0: false.
bool sub_7100926FD0();
// 0x7100927054: the left stick of MaskController controller 1 (zero without a controller or when
// a component is NaN / infinite).
void sub_7100927054(sead::Vector2f* stick);
// 0x71009270a4: whether that stick is not zero.
bool sub_71009270A4();
// 0x7100927110 / 0x71009271b0: acc::Camera::sub_7100799F60 / sub_710079A05C on the camera of Root6
// (false without a Root6 or camera).
bool sub_7100927110();
bool sub_71009271B0();
// 0x7100927238: sub_71009220FC of the "StickSensitivity" game data value (2 by default).
f32 sub_7100927238();
// 0x71009272a8: sub_7100927238's value times sub_7100922120().
f32 sub_71009272A8();
// 0x7100927228 / 0x7100927230: -1.
f32 sub_7100927228();
f32 sub_7100927230();
// 0x710092738c: terrain slope (degrees, negated and weighted) ahead of `pos` along the horizontal
// direction from `target` to `pos`, from ground ray casts; 0 when the ground below `pos` is less
// than 4 units deep.
f32 sub_710092738C(const sead::Vector3f& pos, const sead::Vector3f& target);

// Camera access helpers (TU 0x710092da50-).
// 0x710092dab8 / 0x710092dad0: the camera manager's viewport (CameraMgr::sub_7100D8C4C8), null
// without manager.
const sead::Viewport* sub_710092DAB8();
const sead::Viewport* sub_710092DAD0();
// 0x710092dae8 / 0x710092db0c (CSV getRoot6SomeActor): acquire the camera into `accessor` (Root6
// sub_7100927198 / sub_71009287CC).
void sub_710092DAE8(ksys::act::ActorLinkConstDataAccess* accessor);
void getRoot6SomeActor(ksys::act::ActorLinkConstDataAccess* accessor);
// 0x710092db30: acquires the camera into `link`.
void sub_710092DB30(ksys::act::BaseProcLink* link);
// 0x710092db74: stores the camera (null if not accessible) in `camera`.
void sub_710092DB74(uking::act::Camera** camera);
// 0x710092dba4: Camera::_139c, or ksys::util::sUnk_7101EC6BAC (0) without camera.
ksys::util::Unk_7101EC6BAC sub_710092DBA4();
// 0x710092dc00: Camera::_860.sub_710079C120(1) (false without camera).
bool sub_710092DC00();

namespace uking::act {

// Placeholder name (out-of-line ctor 0x71009214b8, in the camera utility code): a camera state
// (position, look-at, up and four parameters). Camera embeds many of them (Camera::_860 starts with
// six; camera actions read state 0 at Camera+0x860 / +0x86c).
class Unk_71009214b8 {
public:
    Unk_71009214b8();
    ~Unk_71009214b8() {}

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
    // 0x71009237bc: recomputes the up vector (_18) from the look direction and the roll _28.
    void sub_71009237BC();

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
    // Inline (e.g. CameraEventPolarCoordPlayerRel::m52: _0 = 0, then angleStuff(0) twice).
    Unk_7100922700() : _0(0), _4(angleStuff(0)), _8(angleStuff(0)) {}
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

// 0x7100923494: n! (1 for 0, -1 for negative n); used by the curve below.
s32 sub_7100923494(s32 n);

// Placeholder name (vtable 0x71024741b8 (no RTTI): empty dtor, D0, eval; ctor 0x7100923674): a
// rational cubic Bezier curve over [0, 1] with control values _8-_14 and weights 1, _18, _1c, 1.
// Camera actions build one on the stack, call set() and then sub_71009234D8.
class Unk_71024741b8 {
public:
    Unk_71024741b8();
    virtual ~Unk_71024741b8() {}
    // 0x71009236b4: the curve value at `t` (clamped to [0, 1]).
    virtual f32 eval(f32 t) const;

    // 0x710092368c: control values and the two inner weights (clamped to >= 0).
    void set(f32 p0, f32 p1, f32 p2, f32 p3, f32 w1, f32 w2);
    // 0x71009234d8: the t for which eval(t) == value (bisection with `iterations` steps, then a
    // linear interpolation).
    f32 sub_71009234D8(f32 value, int iterations) const;

    /* 0x08 */ f32 _8 = 0;
    /* 0x0c */ f32 _c = 0;
    /* 0x10 */ f32 _10 = 0;
    /* 0x14 */ f32 _14 = 0;
    /* 0x18 */ f32 _18 = 0;
    /* 0x1c */ f32 _1c = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024741b8, 0x20);

// Name from the CSV (Root6::createInstance 0x7100928700, Root6::getInstance 0x7100927188,
// Root6::getCameraActor 0x71009287e4). A sead singleton without vtable (size 0x28, instance
// 0x71025d2508) that holds the camera actor. TU 0x71009285f0-0x710092886c; getInstance and
// sub_7100927198 are in the camera player-state TU (0x7100926430-).
class Root6 {
    SEAD_SINGLETON_DISPOSER(Root6)
    Root6() = default;

public:
    static Root6* getInstance();

    // 0x71009285f0 / 0x71009287e4 (CSV getCameraActor): the camera if it is still accessible.
    Camera* sub_71009285F0();
    Camera* getCameraActor();
    // 0x71009287cc / 0x7100927198: acquires the camera into `accessor` (if not null).
    void sub_71009287CC(ksys::act::ActorLinkConstDataAccess* accessor);
    void sub_7100927198(ksys::act::ActorLinkConstDataAccess* accessor);
    // 0x7100928838: registers `camera` unless one is registered already.
    bool sub_7100928838(Camera* camera);
    // 0x7100928854: unregisters `camera`.
    void sub_7100928854(Camera* camera);

private:
    Camera* mCamera = nullptr;
};
KSYS_CHECK_SIZE_NX150(Root6, 0x28);

}  // namespace uking::act
