#pragma once

#include <basis/seadTypes.h>
#include <container/seadRingBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {
class ActionBase;
}

namespace uking::act {

class Camera;

// 0x710079be9c (in the Camera TU): idx < 1.
bool sub_710079BE9C(int idx);

// Placeholder name (vtable 0x7102459dd8: empty D1 0x710079c5a8 and D0 only; out-of-line ctor
// 0x710079c364): an eased progress value. _14 moves towards 1 by _10 = 1 / (_8 * _c) per frame;
// _18 = (sin(_14 * pi - pi / 2) + 1) / 2. Camera actions embed or construct them.
class Unk_7102459dd8 {
public:
    Unk_7102459dd8();
    virtual ~Unk_7102459dd8() = default;

    // 0x710079c384: _8 = max(a, 0), _14 = clamp(t, 0, 1).
    void sub_710079C384(f32 a, f32 t);
    // 0x710079c3f8: _c = max(a, 0).
    void sub_710079C3F8(f32 a);
    // 0x710079c408: advances _14 towards 1.
    void sub_710079C408();
    // 0x710079c510: _14 = clamp(t, 0, 1).
    void sub_710079C510(f32 t);
    // 0x710079c57c: copies the five values (not the vtable pointer).
    void sub_710079C57C(const Unk_7102459dd8& other);

    /* 0x08 */ f32 _8 = 0;
    /* 0x0c */ f32 _c = 1.0;
    /* 0x10 */ f32 _10 = 0;
    /* 0x14 */ f32 _14 = 0;
    /* 0x18 */ f32 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102459dd8, 0x20);

// Placeholder name (out-of-line ctor 0x7100791b1c): a 64-character name, an index and a link.
class Unk_7100791b1c {
public:
    Unk_7100791b1c();

    // 0x7100791b88: clears the name, _58 = -1 and resets the link.
    void sub_7100791B88();

    /* 0x00 */ sead::FixedSafeString<64> _0;
    /* 0x58 */ s32 _58 = -1;
    /* 0x60 */ ksys::act::BaseProcLink _60;
};
KSYS_CHECK_SIZE_NX150(Unk_7100791b1c, 0x70);

// Placeholder names (after their first out-of-line method): flag words of Unk_710079a8e8 whose
// methods are not inlined into the camera actions (they are defined in the Camera TU).
// Unk_710079a8e8::_7fc / _800.
class Unk_710079b62c {
public:
    void sub_710079B62C(u32 mask);              // set
    bool sub_710079BFB0(u32 mask) const;        // none of the bits set
    bool sub_710079C0CC(u32 mask) const;        // any of the bits set

    u32 _0 = 0;
};

// Unk_710079a8e8::_804 / _808.
class Unk_710079adc8 {
public:
    bool sub_710079ADC8(u32 mask) const;  // none of the bits set
    void sub_710079AE20(u32 mask);        // set
    void sub_710079AE40(u32 mask);        // reset
    bool sub_710079AE50(u32 mask) const;  // any of the bits set

    u32 _0 = 0;
};

// Unk_710079a8e8::_80e.
class Unk_710079c1c8 {
public:
    bool sub_710079C1C8(u8 mask) const;  // any of the bits set
    void sub_710079C1DC(u8 mask);        // set the bits
    void sub_710079C1EC();               // reset

    u8 _0 = 0;
};

// Unk_710079a8e8::_80f.
class Unk_710079c1f4 {
public:
    bool sub_710079C1F4(u8 mask) const;  // any of the bits set
    void sub_710079C208(u8 mask);        // set the bits
    void sub_710079C218();               // reset

    u8 _0 = 0;
};

// Placeholder name (out-of-line ctor 0x710079a8e8): the large sub-object of Camera at 0x860 that
// most camera actions (via Unk_7102459708::getCamera) read and write. Initial values from the ctor.
// TODO: incomplete (field meanings unknown; 0x164-0x170 not initialised by the ctor).
class Unk_710079a8e8 {
public:
    // Value-initialised member at 0x72c (memset over it in the ctor).
    struct Unk72c {
        /* 0x00 */ u32 _0;
        /* 0x04 */ Unk_71009214b8 _4;
        /* 0x3c */ s32 _3c = 2;
        /* 0x40 */ sead::Matrix34f _40 = sead::Matrix34f::ident;
        /* 0x70 */ sead::Vector3f _70 = sead::Vector3f::zero;
        /* 0x7c */ sead::Vector3f _7c = sead::Vector3f::zero;
    };

    Unk_710079a8e8();
    // 0x7100792408
    ~Unk_710079a8e8();

    void sub_710079AD90();
    f32 sub_710079ADA0() const;
    bool sub_710079ADBC() const;
    // 0x710079add8 / 0x710079ae88: _15c (near) / _160 (far) = value and set _804 bit 0x2000 /
    // 0x8000 (unless value is NaN or not positive).
    void sub_710079ADD8(f32 value);
    void sub_710079AE30();
    void sub_710079AE88(f32 value);
    void sub_710079AED0();
    // 0x710079aee0: zeroes _1a0 and _1c0 / _1c4, angleStuff(0) into _1b8 / _1bc, _1d0.sub_710079C510(1).
    void sub_710079AEE0();
    bool sub_710079B63C(u32 mask) const;
    void sub_710079BC8C();
    // 0x710079bc98: _240 = _230 and copies the _354 camera state into _39c.
    void sub_710079BC98();
    void sub_710079BD2C();
    void sub_710079BD5C();
    void sub_710079BD6C(f32 value);
    void sub_710079BD98();
    bool sub_710079BDA4() const;
    void sub_710079BE34();
    void sub_710079BEA8();
    void sub_710079BEB4();
    bool sub_710079BEBC() const;
    // 0x710079bed0: _7e0 = value (unless it is NaN or negative).
    void sub_710079BED0(f32 value);
    f32 sub_710079BF0C() const;
    void sub_710079BF14();
    bool sub_710079BF20() const;
    void sub_710079BF34(f32 value);
    void sub_710079BF58();
    void sub_710079C0AC();
    void sub_710079C0DC(int idx, f32 value);
    bool sub_710079C0F4(f32* out) const;
    bool sub_710079C120(u8 mask) const;
    bool sub_710079C134(u8 mask) const;
    void sub_710079C148(u8 mask);
    void sub_710079C158(u8 mask, bool on);
    void sub_710079C17C();
    bool sub_710079C184(u32 mask) const;

    /* 0x000 */ Unk_71009214b8 _0;
    /* 0x038 */ Unk_71009214b8 _38;
    /* 0x070 */ Unk_71009214b8 _70;
    /* 0x0a8 */ Unk_71009214b8 _a8;
    /* 0x0e0 */ Unk_71009214b8 _e0;
    /* 0x118 */ Unk_71009214b8 _118;
    /* 0x150 */ sead::Vector3f _150 = sead::Vector3f::ez;
    /* 0x15c */ f32 _15c = 0.1;
    /* 0x160 */ f32 _160 = 25000.0;
    /* 0x164 */ sead::Vector3f _164;  // the camera target set by Camera::sub_7100793DB4
    /* 0x170 */ bool _170 = false;
    /* 0x171 */ u8 _171[0x180 - 0x171];
    /* 0x180 */ bool _180 = false;
    /* 0x184 */ f32 _184 = 0;
    /* 0x188 */ f32 _188 = 1.0;
    /* 0x18c */ f32 _18c;  // initialised from a global float constant (1.0)
    /* 0x190 */ f32 _190 = -1.0;
    /* 0x198 */ const f32* _198 = nullptr;  // CameraRoot static param sideOffsetBowCus
    /* 0x1a0 */ sead::Vector3f _1a0 = sead::Vector3f::zero;
    /* 0x1ac */ sead::Vector3f _1ac = sead::Vector3f::zero;
    /* 0x1b8 */ f32 _1b8;  // angleStuff(0)
    /* 0x1bc */ f32 _1bc;  // angleStuff(0)
    /* 0x1c0 */ f32 _1c0 = 0;
    /* 0x1c4 */ f32 _1c4 = 1.5707964;
    /* 0x1c8 */ s32 _1c8 = 2;
    /* 0x1cc */ u32 _1cc = 0;
    /* 0x1d0 */ Unk_7102459dd8 _1d0;
    /* 0x1f0 */ const f32* _1f0 = nullptr;  // CameraRoot static param guardianDist
    /* 0x1f8 */ const f32* _1f8 = nullptr;  // CameraRoot static param guardianAngle
    /* 0x200 */ ksys::act::BaseProcLink _200;
    /* 0x210 */ ksys::act::BaseProcLink _210;
    /* 0x220 */ ksys::act::BaseProcLink _220;
    /* 0x230 */ ksys::act::BaseProcLink _230;
    /* 0x240 */ ksys::act::BaseProcLink _240;
    /* 0x250 */ ksys::act::BaseProcLink _250;
    /* 0x260 */ ksys::act::BaseProcLink _260;
    /* 0x270 */ sead::Matrix34f _270 = sead::Matrix34f::ident;
    /* 0x2a0 */ sead::Vector3f _2a0 = sead::Vector3f::zero;
    /* 0x2ac */ sead::Vector3f _2ac = sead::Vector3f::zero;
    /* 0x2b8 */ sead::Vector3f _2b8 = sead::Vector3f::zero;
    /* 0x2c4 */ sead::Vector3f _2c4 = sead::Vector3f::zero;
    /* 0x2d0 */ sead::Matrix34f _2d0 = sead::Matrix34f::ident;
    /* 0x300 */ sead::Vector3f _300 = sead::Vector3f::zero;
    /* 0x30c */ sead::Vector3f _30c = sead::Vector3f::zero;
    /* 0x318 */ sead::Vector3f _318 = sead::Vector3f::zero;
    /* 0x324 */ sead::Matrix34f _324 = sead::Matrix34f::ident;
    /* 0x354 */ sead::Matrix34f _354 = sead::Matrix34f::ident;
    /* 0x384 */ sead::Vector3f _384 = sead::Vector3f::zero;
    /* 0x390 */ sead::Vector3f _390 = sead::Vector3f::zero;
    /* 0x39c */ sead::Matrix34f _39c = sead::Matrix34f::ident;
    /* 0x3cc */ sead::Vector3f _3cc = sead::Vector3f::zero;
    /* 0x3d8 */ sead::Vector3f _3d8 = sead::Vector3f::zero;
    /* 0x3e4 */ sead::Matrix34f _3e4 = sead::Matrix34f::ident;
    /* 0x414 */ sead::Matrix34f _414 = sead::Matrix34f::ident;
    /* 0x444 */ sead::Matrix34f _444 = sead::Matrix34f::ident;
    /* 0x474 */ sead::Vector3f _474 = sead::Vector3f::zero;
    /* 0x480 */ sead::Vector3f _480 = sead::Vector3f::zero;
    /* 0x48c */ sead::Vector3f _48c = sead::Vector3f::zero;
    /* 0x498 */ f32 _498 = 0;
    /* 0x49c */ sead::Matrix34f _49c = sead::Matrix34f::ident;
    /* 0x4cc */ sead::Vector3f _4cc = sead::Vector3f::zero;
    /* 0x4d8 */ sead::Vector3f _4d8 = sead::Vector3f::zero;
    /* 0x4e4 */ sead::Vector3f _4e4 = sead::Vector3f::zero;
    /* 0x4f0 */ f32 _4f0;  // 1.125 (returned by 0x7100922134)
    /* 0x4f4 */ f32 _4f4;  // 0.5 (returned by 0x710092213c)
    /* 0x4f8 */ sead::FixedSafeString<32> _4f8;
    /* 0x530 */ Unk_7100791b1c _530;
    /* 0x5a0 */ Unk_7100791b1c _5a0[3]{};
    /* 0x6f0 */ void* _6f0 = nullptr;
    /* 0x6f8 */ u32 _6f8 = 0;
    /* 0x6fc */ sead::Matrix34f _6fc = sead::Matrix34f::ident;
    /* 0x72c */ Unk72c _72c{};
    /* 0x7b4 */ u32 _7b4 = 0;
    /* 0x7b8 */ u8 _7b8 = 0;
    /* 0x7b9 */ u8 _7b9 = 0;
    /* 0x7ba */ u8 _7ba[2]{};
    // Indexed by _81a (current) and (_81a + 1) % 2 (with the SafeArray bounds clamp).
    /* 0x7c0 */ sead::SafeArray<ksys::act::BaseProcLink, 2> _7c0{};
    /* 0x7e0 */ f32 _7e0 = -1.0;
    /* 0x7e4 */ f32 _7e4 = -1.0;
    /* 0x7e8 */ u32 _7e8 = 0;
    /* 0x7ec */ f32 _7ec;  // angleStuff(0)
    /* 0x7f0 */ sead::SafeArray<f32, 2> _7f0{{-1.0, -1.0}};
    // _7f8 bit 0 is restored from _7fa bit 0 by CameraRoot::m35.
    /* 0x7f8 */ sead::BitFlag16 _7f8;
    /* 0x7fa */ sead::BitFlag16 _7fa;
    /* 0x7fc */ Unk_710079b62c _7fc;
    /* 0x800 */ Unk_710079b62c _800;  // masks _7fc in sub_710079B63C
    /* 0x804 */ Unk_710079adc8 _804;
    /* 0x808 */ Unk_710079adc8 _808;  // masks _804 in sub_710079C184
    /* 0x80c */ sead::BitFlag8 _80c;
    /* 0x80d */ u8 _80d = 0;
    /* 0x80e */ Unk_710079c1c8 _80e;
    /* 0x80f */ Unk_710079c1f4 _80f;
    /* 0x810 */ u8 _810 = 3;
    /* 0x811 */ u8 _811 = 0;
    /* 0x812 */ u8 _812 = 2;
    /* 0x813 */ u8 _813 = 0;
    /* 0x814 */ u8 _814 = 2;
    /* 0x815 */ u8 _815[2]{};
    /* 0x817 */ u8 _817 = 0;  // saturating counter (CameraAction::m41)
    /* 0x818 */ u8 _818 = 0;
    /* 0x819 */ u8 _819 = 0;
    /* 0x81a */ u8 _81a = 0;  // selects the _7c0 link (Camera::sub_71007929E0 resets the other one)
    /* 0x81b */ u8 _81b[0x81d - 0x81b]{};
};
KSYS_CHECK_SIZE_NX150(Unk_710079a8e8, 0x820);

// Placeholder name (its vtable group in Camera's vtable starts at 0x7102459cc0): secondary base of
// Camera at 0x840. 12 virtual slots and no destructor: slots 0/1 return the owning Camera, 2-9 are
// overridden by Camera::m150-m157, 10/11 return Camera::_1088.
// TODO: virtual functions not declared (signatures unknown); only the layout is modelled.
class Unk_7102459cc0 {
public:
    virtual void* m0() = 0;

    /* 0x08 */ f32 _8 = 1.0;
};

// Placeholder name (out-of-line ctor 0x7100928b6c (this, camera), in the camera utility code):
// Camera::_1240.
class Unk_7100928b6c {
public:
    explicit Unk_7100928b6c(Camera* camera);

    // 0x7100928c10 / 0x7100928c20: set / clear `mask` in _140.
    void sub_7100928C10(u8 mask);
    void sub_7100928C20(u8 mask);
    // 0x7100928c30 / 0x7100928c40: set / clear bit 0 of _141.
    void sub_7100928C30();
    void sub_7100928C40();
    // 0x710092a83c: resets _11c-_124 to -1, _128 / _140-_142 / _148 to 0 and _145 to 1.
    void sub_710092A83C();

    /* 0x000 */ Camera* mCamera;
    /* 0x008 */ Unk_71009214b8 _8;
    /* 0x040 */ Unk_71009214b8 _40;
    /* 0x078 */ Unk_71009214b8 _78;
    /* 0x0b0 */ Unk_71009214b8 _b0;
    /* 0x0e8 */ u8 _e8[0xf4 - 0xe8];
    /* 0x0f4 */ bool _f4 = false;
    /* 0x0f8 */ sead::Vector3f _f8 = sead::Vector3f::zero;
    /* 0x104 */ sead::Vector3f _104 = sead::Vector3f::zero;
    /* 0x110 */ sead::Vector3f _110 = sead::Vector3f::zero;
    /* 0x11c */ f32 _11c = -1.0;
    /* 0x120 */ f32 _120 = -1.0;
    /* 0x124 */ f32 _124 = -1.0;
    /* 0x128 */ u32 _128 = 0;
    /* 0x12c */ u32 _12c = 0;
    /* 0x130 */ void* _130 = nullptr;
    /* 0x138 */ void* _138 = nullptr;
    /* 0x140 */ u8 _140 = 0;  // flags (sub_7100928C10 / sub_7100928C20)
    /* 0x141 */ u8 _141 = 0;  // bit 0: sub_7100928C30 / sub_7100928C40
    /* 0x142 */ u8 _142 = 0;
    /* 0x143 */ u8 _143[0x145 - 0x143]{};
    /* 0x145 */ u8 _145 = 0;
    /* 0x146 */ u8 _146[0x148 - 0x146]{};
    /* 0x148 */ bool _148 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7100928b6c, 0x150);

// Placeholder name (out-of-line ctor 0x7100928644, zeroes 0x18 bytes): Camera::_13a4.
class Unk_7100928644 {
public:
    Unk_7100928644();

    /* 0x00 */ u32 _0;
    /* 0x04 */ u32 _4;
    /* 0x08 */ u32 _8;
    /* 0x0c */ u32 _c;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
};
KSYS_CHECK_SIZE_NX150(Unk_7100928644, 0x18);

// Name from the CSV (act::Camera::*: construct 0x7100791ef4 = new(0x1428), ctor 0x7100791f38,
// vtable 0x7102459728 with 167 slots (Actor's 148 + m148-m166), RTTI static via GOT 0x710258d210).
// The camera actor; AI code gets it with Unk_7102459708::getCamera().
// TODO: incomplete (virtual functions not declared; 0x1090-0x10c0, 0x1130-0x11f0, 0x1230-0x1240
// not initialised by the ctor and untyped).
class Camera : public ksys::act::Actor, public Unk_7102459cc0 {
    SEAD_RTTI_OVERRIDE(Camera, ksys::act::Actor)
public:
    struct Unk13d8Entry {
        u8 _0[0xc];
    };

    // 0x7100795e08: copies `src` to `dst` and adjusts dst._24 (in place when they are the same).
    void sub_7100795E08(const Unk_71009214b8& src, Unk_71009214b8* dst);
    explicit Camera(const CreateArg& arg);

    // The new virtual functions (slots 148-166; lane4 s44; signatures from the small ones, the rest are declarations
    // only). m148 / m149 are empty (CSV m148_null / m149_null).
    /* 148 */ virtual void m148();
    /* 149 */ virtual void m149();
    /* 150 */ virtual void m150();
    /* 151 */ virtual void m151(const sead::Vector3f* pos, const sead::Vector3f* at, bool a3);  // lane1 s44: signature from PlayerResetPosMgr
    /* 152 */ virtual void m152();
    /* 153 */ virtual void m153(const sead::Vector3f* pos, bool a2);  // lane4 s51: arguments from Camera::sub_7100793DB4
    /* 154 */ virtual void m154(f32 value, bool a2);
    // `m154(deg2rad(degrees), true)`.
    /* 155 */ virtual void m155(f32 degrees);
    // The (x, y, z) angles of the camera state _860._e0 (sub_7100921C04 / C50 / C98).
    /* 156 */ virtual sead::Vector3f m156();
    // Stores `_1088 = a1` and the matrix `_1090 = mtx`.
    /* 157 */ virtual void m157(void* a1, const sead::Matrix34f& mtx);
    /* 158 */ virtual void* m158();
    /* 159 */ virtual sead::Matrix34f* m159();
    /* 160 */ virtual void m160();
    /* 161 */ virtual void m161();
    // `_860._804.sub_710079AE20(1)`.
    /* 162 */ virtual void m162();
    /* 163 */ virtual void m163();
    /* 164 */ virtual void m164();
    /* 165 */ virtual void* m165();
    /* 166 */ virtual void m166(ksys::act::BaseProc* proc);

    // 0x7100796174 (CSV m18) / 0x7100796200 (CSV m19) / 0x71007963f8 (CSV m7).
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    PreDeletePrepareResult prepareForPreDelete_() override;
    // 0x7100799cd4 (CSV m82): returns 1.
    int getCalcTiming() override;
    // 0x7100799a54 (CSV m73): `if (!sub_7100922428()) sub_710079691C()`.
    void m73() override;
    // 0x7100799a88 (CSV m75): if `_860._804` has bit 0 set nothing happens; otherwise sets `_1421` when
    // sub_7100922428() or calls sub_71007970E0().
    void m75() override;
    // 0x71007970e0 / 0x7100793f8c / 0x710079691c: declared only (called by m164 / m75 / m73).
    void sub_71007970E0();
    void sub_7100793F8C();
    void sub_710079691C();

    // 0x71007953c8: moves _860._0._28 towards 0 (unless sub_7100922078()).
    void sub_71007953C8();
    // 0x71007929e0: copies camera state _860._e0 into _860._0 / _38 / _70 / _a8 (and its look-at
    // point into _860._150), resets _1240, _860 and some flags, and the unused _860._7c0 link.
    void sub_71007929E0();
    // 0x7100794fd0: bit 0x8000 of _860._800.
    bool sub_7100794FD0() const;
    // 0x710079614c / 0x7100796164: bits 2-3 of _13fd equal 1 / bit 2 of _13fd.
    bool sub_710079614C() const;
    bool sub_7100796164() const;
    // 0x7100795c44: updates the _860 camera states (when _860._1c8 != 0).
    void sub_7100795C44();
    // 0x7100795c08 (CSV name; `idx` is not used by the function itself).
    void x_1(u8 idx);
    // 0x7100799920 (CSV nullsub_6133): empty.
    void sub_7100799920();
    // 0x7100793924 (CSV x) / 0x7100793bd8 (CSV x_0): declared only (called by m160 / m161).
    void sub_7100793924();
    // 0x7100793d88 (CSV x_2): `sub_7100793DB4(); _860._804.sub_710079AE20(0x80000)`. 0x7100793db4: declared only.
    void sub_7100793D88();
    // 0x7100793db4: takes the player's look-at position (or the current look-at point of `_860._0`) as the camera target:
    // stores it in `_860._164`, calls m153 with it and updates the matrix.
    void sub_7100793DB4();
    // 0x710079572c (CSV act::Camera::updateMatrix; declared only).
    void updateMatrix(bool a1);
    void sub_7100793BD8();
    // 0x7100795f40: `*out` = the current core's entry of the f32 array at 0x1230 (false if out is null).
    bool sub_7100795F40(f32** out);

    /* 0x0850 */ ksys::act::BaseProcLink _850;
    /* 0x0860 */ Unk_710079a8e8 _860;
    /* 0x1080 */ void* _1080 = nullptr;
    /* 0x1088 */ void* _1088 = nullptr;
    /* 0x1090 */ sead::Matrix34f _1090;
    /* 0x10c0 */ Unk_71009214b8 _10c0;
    /* 0x10f8 */ u32 _10f8 = 0;
    /* 0x1100 */ ksys::act::BaseProcLink _1100{};
    /* 0x1110 */ ksys::act::BaseProcLink _1110{};
    /* 0x1120 */ ksys::act::BaseProcLink _1120{};
    // Three 0x40-byte entries with a bool at +0x3c (cleared by the ctor body).
    /* 0x1130 */ u8 _1130[0x11f0 - 0x1130];
    /* 0x11f0 */ sead::Matrix34f _11f0;
    /* 0x1220 */ sead::Vector3f _1220;
    /* 0x122c */ bool _122c;
    /* 0x122d */ u8 _122d[0x1240 - 0x122d];
    /* 0x1240 */ Unk_7100928b6c _1240{this};
    /* 0x1390 */ void* _1390 = nullptr;
    // Angle indices (Player::x_5's value type): _1398 is computed with atan2Idx each frame and
    // copied to _139c (read through 0x710092dba4).
    /* 0x1398 */ ksys::util::Unk_7101EC6BAC _1398{0};
    /* 0x139c */ ksys::util::Unk_7101EC6BAC _139c{0};
    /* 0x13a0 */ u32 _13a0 = 0;
    /* 0x13a4 */ Unk_7100928644 _13a4;
    /* 0x13bc */ u32 _13bc[6]{};
    // 0x7100796174 (prepareInit_) allocates it (sub_7100922080() entries); 0x7100796200 frees it.
    /* 0x13d8 */ sead::RingBuffer<Unk13d8Entry> _13d8;
    /* 0x13f0 */ u32 _13f0 = 0;
    /* 0x13f4 */ f32 _13f4 = 1.0;
    /* 0x13f8 */ u32 _13f8 = 0;
    /* 0x13fc */ u8 _13fc = 0;
    /* 0x13fd */ u8 _13fd = 0;
    /* 0x13fe */ u8 _13fe = 0;
    /* 0x1400 */ sead::Delegate<Camera> _1400;
    // m163 waits for the worker task 1 when set, m164 / m75 use _1421.
    /* 0x1420 */ u8 _1420 = 0;
    /* 0x1421 */ u8 _1421 = 0;
};
KSYS_CHECK_SIZE_NX150(Camera, 0x1428);

}  // namespace uking::act

// Unnamed secondary base of the camera AI and action classes (CameraAI, CameraAction, ...; vtable
// 0x7102459708): a virtual destructor and a pointer to the owning AI / action. Its ctor
// (0x7100791ca8), destructors and getCamera functions live in the Camera actor's translation unit.
class Unk_7102459708 {
public:
    explicit Unk_7102459708(ksys::act::ai::ActionBase* owner);
    virtual ~Unk_7102459708() = default;

    // 0x7100791cc0 (CSV act::getCamera) / 0x7100791d54 (CSV getCameraActor): the owner's actor if
    // it is a Camera.
    uking::act::Camera* getCamera() const;
    uking::act::Camera* getCameraActor() const;
    // 0x7100791e44: the per-frame lerp factor for `t` (sub_710092523C with the camera's
    // sub_71009251C4 frame count).
    f32 sub_7100791E44(f32 t) const;

    ksys::act::ai::ActionBase* mOwner;
};

namespace ksys::act::acc {

// Access to a uking::act::Camera through an ActorConstDataAccess (CSV: act::acc::Camera; functions
// 0x7100799f60-0x710079a6xx in the Camera TU). Namespace as for the other acc:: accessors.
// TODO: incomplete (requestCameraPack, setSunazarashiTurnParam, setWaterRemainsData,
// getPlayerAlphaRate not declared).
class Camera : public ActorConstDataAccess {
public:
    // 0x7100799f60 / 0x710079a05c / 0x710079a158: Camera::sub_710079614C / sub_7100796164 /
    // sub_7100794FD0 (false if the actor is no Camera).
    bool sub_7100799F60() const;
    bool sub_710079A05C() const;
    bool sub_710079A158() const;

protected:
    uking::act::Camera* getCamera() const;
};
KSYS_CHECK_SIZE_NX150(Camera, 0x18);

}  // namespace ksys::act::acc
