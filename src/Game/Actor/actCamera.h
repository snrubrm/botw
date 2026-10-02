#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {
class ActionBase;
}

namespace uking::act {

class Camera;

// Placeholder name (out-of-line ctor 0x71009214b8, in the camera utility code): a camera state
// (position, look-at, up and four parameters). Camera embeds many of them (Camera::_860 starts with
// six; camera actions read state 0 at Camera+0x860 / +0x86c).
class Unk_71009214b8 {
public:
    Unk_71009214b8();

    /* 0x00 */ sead::Vector3f _0;   // Vector3f::zero
    /* 0x0c */ sead::Vector3f _c;   // Vector3f::ez
    /* 0x18 */ sead::Vector3f _18;  // Vector3f::ey
    /* 0x24 */ f32 _24;             // 1.5 (the Camera ctor sets pi/4 for Camera::_860._0)
    /* 0x28 */ f32 _28;             // 0
    /* 0x2c */ f32 _2c;             // 1.7
    /* 0x30 */ f32 _30;             // 1.0
    /* 0x34 */ f32 _34;             // 100.0
};
KSYS_CHECK_SIZE_NX150(Unk_71009214b8, 0x38);

// Placeholder name (vtable 0x7102459dd8: empty D1 0x710079c5a8 and D0 only; out-of-line ctor
// 0x710079c364).
class Unk_7102459dd8 {
public:
    Unk_7102459dd8();
    virtual ~Unk_7102459dd8();

    /* 0x08 */ f32 _8 = 0;
    /* 0x0c */ f32 _c = 1.0;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ u32 _18 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102459dd8, 0x20);

// Placeholder name (out-of-line ctor 0x7100791b1c): a 64-character name, an index and a link.
class Unk_7100791b1c {
public:
    Unk_7100791b1c();

    /* 0x00 */ sead::FixedSafeString<64> _0;
    /* 0x58 */ s32 _58 = -1;
    /* 0x60 */ ksys::act::BaseProcLink _60;
};
KSYS_CHECK_SIZE_NX150(Unk_7100791b1c, 0x70);

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

    /* 0x000 */ Unk_71009214b8 _0;
    /* 0x038 */ Unk_71009214b8 _38;
    /* 0x070 */ Unk_71009214b8 _70;
    /* 0x0a8 */ Unk_71009214b8 _a8;
    /* 0x0e0 */ Unk_71009214b8 _e0;
    /* 0x118 */ Unk_71009214b8 _118;
    /* 0x150 */ sead::Vector3f _150 = sead::Vector3f::ez;
    /* 0x15c */ f32 _15c = 0.1;
    /* 0x160 */ f32 _160 = 25000.0;
    /* 0x164 */ u8 _164[0x170 - 0x164];
    /* 0x170 */ bool _170 = false;
    /* 0x171 */ u8 _171[0x180 - 0x171];
    /* 0x180 */ bool _180 = false;
    /* 0x184 */ f32 _184 = 0;
    /* 0x188 */ f32 _188 = 1.0;
    /* 0x18c */ f32 _18c;  // initialised from a global float constant (1.0)
    /* 0x190 */ f32 _190 = -1.0;
    /* 0x198 */ void* _198 = nullptr;
    /* 0x1a0 */ sead::Vector3f _1a0 = sead::Vector3f::zero;
    /* 0x1ac */ sead::Vector3f _1ac = sead::Vector3f::zero;
    /* 0x1b8 */ f32 _1b8;  // angleStuff(0)
    /* 0x1bc */ f32 _1bc;  // angleStuff(0)
    /* 0x1c0 */ f32 _1c0 = 0;
    /* 0x1c4 */ f32 _1c4 = 1.5707964;
    /* 0x1c8 */ s32 _1c8 = 2;
    /* 0x1cc */ u32 _1cc = 0;
    /* 0x1d0 */ Unk_7102459dd8 _1d0;
    /* 0x1f0 */ void* _1f0 = nullptr;
    /* 0x1f8 */ void* _1f8 = nullptr;
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
    /* 0x7b8 */ u32 _7b8 = 0;
    /* 0x7c0 */ ksys::act::BaseProcLink _7c0{};
    /* 0x7d0 */ ksys::act::BaseProcLink _7d0{};
    /* 0x7e0 */ f32 _7e0 = -1.0;
    /* 0x7e4 */ f32 _7e4 = -1.0;
    /* 0x7e8 */ u32 _7e8 = 0;
    /* 0x7ec */ f32 _7ec;  // angleStuff(0)
    /* 0x7f0 */ f32 _7f0 = -1.0;
    /* 0x7f4 */ f32 _7f4 = -1.0;
    /* 0x7f8 */ void* _7f8 = nullptr;
    /* 0x800 */ void* _800 = nullptr;
    /* 0x808 */ void* _808 = nullptr;
    /* 0x810 */ u8 _810 = 3;
    /* 0x811 */ u8 _811 = 0;
    /* 0x812 */ u8 _812 = 2;
    /* 0x813 */ u8 _813 = 0;
    /* 0x814 */ u8 _814 = 2;
    /* 0x815 */ u8 _815[8]{};
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
    /* 0x128 */ void* _128 = nullptr;
    /* 0x130 */ void* _130 = nullptr;
    /* 0x138 */ void* _138 = nullptr;
    /* 0x140 */ void* _140 = nullptr;
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
    explicit Camera(const CreateArg& arg);

    /* 0x0850 */ ksys::act::BaseProcLink _850;
    /* 0x0860 */ Unk_710079a8e8 _860;
    /* 0x1080 */ void* _1080 = nullptr;
    /* 0x1088 */ void* _1088 = nullptr;
    /* 0x1090 */ u8 _1090[0x10c0 - 0x1090];
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
    /* 0x1398 */ void* _1398 = nullptr;
    /* 0x13a0 */ u32 _13a0 = 0;
    /* 0x13a4 */ Unk_7100928644 _13a4;
    /* 0x13bc */ u32 _13bc[6]{};
    /* 0x13d8 */ void* _13d8 = nullptr;
    /* 0x13e0 */ void* _13e0 = nullptr;
    /* 0x13e8 */ u32 _13e8 = 0;
    /* 0x13f0 */ u32 _13f0 = 0;
    /* 0x13f4 */ f32 _13f4 = 1.0;
    /* 0x13f8 */ u32 _13f8 = 0;
    /* 0x13fc */ u16 _13fc = 0;
    /* 0x13fe */ u8 _13fe = 0;
    /* 0x1400 */ sead::Delegate<Camera> _1400;
    /* 0x1420 */ u16 _1420 = 0;
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

    ksys::act::ai::ActionBase* mOwner;
};
