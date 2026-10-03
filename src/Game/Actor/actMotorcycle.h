#pragma once

#include <aal/aalTimedFader.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/physDefines.h"
#include "Game/Actor/actMotorcycleStickControl.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"

namespace ksys::act {
class Actor;
}

namespace ksys::phys {
class Constraint;
class RigidBody;
}

namespace uking::act {

class Unk_7100e8b2b8;
struct MotorcycleStruct0;

// Placeholder name following the CSV's MotorcycleStruct0 (ctor 0x710006c824, size 0x1b0): a wheel of
// the motorcycle (two instances, Motorcycle +0xdd0 and +0xdd8). Not decompiled yet.
struct MotorcycleStruct2 {
    /* 0x000 */ ksys::phys::RigidBody* _0;
    /* 0x008 */ ksys::phys::RigidBody* _8;
    /* 0x010 */ MotorcycleStruct0* _10;
    /* 0x018 */ u8 _18[0x24 - 0x18];
    /* 0x024 */ sead::Matrix34f _24;
    /* 0x054 */ u8 _54[0x5c - 0x54];
    /* 0x05c */ sead::Vector3f _5c;
    /* 0x068 */ u8 _68[0x110 - 0x68];
    /* 0x110 */ ksys::phys::Material _110;  // the material under the wheel
    /* 0x114 */ u8 _114[0x128 - 0x114];
    /* 0x128 */ u64 _128;
    /* 0x130 */ sead::Vector3f _130;
    /* 0x13c */ bool _13c;
    /* 0x13d */ bool _13d;
    /* 0x13e */ u8 _13e;
    /* 0x13f */ u8 _13f;
    /* 0x140 */ u8 _140;
    /* 0x141 */ u8 _141[0x148 - 0x141];
    /* 0x148 */ ksys::phys::Constraint* _148;
    /* 0x150 */ ksys::phys::Constraint* _150;
    /* 0x158 */ u8 _158[0x1b0 - 0x158];
};
KSYS_CHECK_SIZE_NX150(MotorcycleStruct2, 0x1b0);

// CSV MotorcycleUserTag (no namespace in the CSV; vtable 0x71023612c0, RTTI parent PhysicsUserTag, size
// 0x60). Created inline by Motorcycle::prepareInit_ with the main body and both wheels; it records the
// biggest impulse each body received (and whether it was hit by a giant / golem).
class MotorcycleUserTag : public ksys::act::PhysicsUserTag {
    SEAD_RTTI_OVERRIDE(MotorcycleUserTag, ksys::act::PhysicsUserTag)
public:
    struct Entry {
        s32 _0;
        ksys::phys::RigidBody* body;
        f32 impulse;
        bool updated;
        bool hit_by_giant_or_golem;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x18);

    ~MotorcycleUserTag() override;
    void onImpulse(ksys::phys::RigidBody* body_a, ksys::phys::RigidBody* body_b,
                   f32 impulse_a) override;

    Entry mEntries[3];
};
KSYS_CHECK_SIZE_NX150(MotorcycleUserTag, 0x60);

// CSV MotorcycleStruct0 (ctor 0x710006bf34, size 0x1b0, at Motorcycle +0xbc8): the engine / steering
// model of the motorcycle (speeds in the first 0x70 bytes, aal::TimedFader members at 0x70, 0x98, 0xd0,
// 0x108 and 0x150, a stick-style controller at 0x178). Only the fields used by the decompiled
// functions have names beyond their offset.
struct MotorcycleStruct0 {
    explicit MotorcycleStruct0(ksys::act::Actor* actor);

    // 0x710006c270: converts the energy cost rate on the first call and drains the global motorcycle
    // energy; sets _19e when it is used up.
    void sub_710006C270();

    // The speeds / forces; has no constructor of its own in the original (inlined into the one below).
    struct Unk0 {
        Unk0() {
            _60 = {0.0f, 0.0065f};
            _68 = {1.0f, 0.0f};
        }

        /* 0x000 */ f32 _0 = 1950.0f;
        /* 0x004 */ f32 _4 = -1.0f;
        /* 0x008 */ f32 _8 = 867.0f;
        /* 0x00c */ f32 _c = 300.0f;
        /* 0x010 */ f32 _10 = 1500.0f;
        /* 0x014 */ f32 _14 = 65.0f;
        /* 0x018 */ f32 _18 = 1000.0f;
        /* 0x01c */ f32 _1c = 10000.0f;
        /* 0x020 */ f32 _20 = 700.0f;
        /* 0x024 */ f32 _24 = 1000.0f;
        /* 0x028 */ f32 _28 = 500.0f;
        /* 0x02c */ f32 _2c = 130.0f;
        /* 0x030 */ f32 _30 = 7500.0f;
        /* 0x034 */ f32 _34 = 1000.0f;
        /* 0x038 */ f32 _38 = 1.0f / 30.0f;
        /* 0x03c */ f32 _3c = 2.0f / 30.0f;
        /* 0x040 */ f32 _40 = 2000.0f;
        /* 0x044 */ f32 _44 = 9500.0f;
        /* 0x048 */ f32 _48 = 0.0f;
        /* 0x04c */ f32 _4c = 1500.0f;
        /* 0x050 */ f32 _50 = 300.0f;
        /* 0x054 */ f32 _54 = 0.0f;
        /* 0x058 */ f32 _58 = 500.0f;
        /* 0x05c */ f32 _5c = 130.0f;
        /* 0x60 */ sead::Vector2f _60;
        /* 0x68 */ sead::Vector2f _68;
    };
    KSYS_CHECK_SIZE_NX150(Unk0, 0x70);

    /* 0x000 */ Unk0 _0;
    /* 0x070 */ aal::TimedFader _70{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x098 */ aal::TimedFader _98{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x0c0 */ f32 _c0 = 0.0f;
    /* 0x0c4 */ f32 _c4 = 1.0f;
    /* 0x0c8 */ f32 _c8 = 1.0f;
    /* 0x0cc */ u8 _cc[4];
    /* 0x0d0 */ aal::TimedFader _d0{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x0f8 */ f32 _f8 = 0.0f;
    /* 0x0fc */ f32 _fc = 1.0f;
    /* 0x100 */ f32 _100 = 1.0f;
    /* 0x104 */ u8 _104[4];
    /* 0x108 */ aal::TimedFader _108{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x130 */ f32 _130 = 0.0f;
    /* 0x134 */ f32 _134 = 1.0f;
    /* 0x138 */ f32 _138 = 1.0f;
    /* 0x13c */ f32 _13c = 0.0f;
    /* 0x140 */ f32 _140 = 1.0f;
    /* 0x144 */ f32 _144 = 1.0f;
    /* 0x148 */ s32 _148 = 3;
    /* 0x14c */ s32 _14c = 0;
    /* 0x150 */ aal::TimedFader _150{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x178 */ Unk_71002c8e10 _178{2.0f, 1.0f, false};
    /* 0x184 */ s32 _184 = 1;
    /* 0x188 */ f32 _188 = 1.0f;
    /* 0x18c */ f32 _18c = 1.0f;
    /* 0x190 */ f32 _190 = 0.0f;
    /* 0x194 */ bool _194;
    /* 0x195 */ bool _195;
    /* 0x196 */ bool _196;
    /* 0x197 */ bool _197;
    /* 0x198 */ bool _198;
    /* 0x199 */ bool _199;
    /* 0x19a */ bool _19a;
    /* 0x19b */ bool _19b;
    /* 0x19c */ bool _19c;
    /* 0x19d */ bool _19d;
    /* 0x19e */ bool _19e;
    /* 0x1a0 */ u32 _1a0;
    /* 0x1a8 */ ksys::act::Actor* _1a8;
};
KSYS_CHECK_SIZE_NX150(MotorcycleStruct0, 0x1b0);

// Placeholder name following the CSV's MotorcycleStruct0 (ctor 0x710007027c, size 0x430, at Motorcycle +
// 0x11b0): the model bones of the motorcycle (looked up by Motorcycle::searchModelHandles).
struct MotorcycleStruct1 {
    MotorcycleStruct1();
    ~MotorcycleStruct1();

    /* 0x000 */ gsys::BoneAccessKeyEx mWheel_F;
    /* 0x038 */ gsys::BoneAccessKeyEx mWheel_R;
    /* 0x070 */ gsys::BoneAccessKeyEx mSwingArm_F;
    /* 0x0a8 */ gsys::BoneAccessKeyEx mSwingArm_R;
    /* 0x0e0 */ gsys::BoneAccessKeyEx mSuspension_F;
    /* 0x118 */ gsys::BoneAccessKeyEx mSuspension_R;
    /* 0x150 */ gsys::BoneAccessKeyEx mHandle;
    /* 0x188 */ gsys::BoneAccessKeyEx mBody_1;
    /* 0x1c0 */ gsys::BoneAccessKeyEx mHead_A;
    /* 0x1f8 */ gsys::BoneAccessKeyEx mSaddle_Root;
    /* 0x230 */ gsys::BoneAccessKeyEx mSeat_Front;
    /* 0x268 */ gsys::BoneAccessKeyEx mSeat_Rear;
    /* 0x2a0 */ gsys::BoneAccessKeyEx mRearCowl_A;
    /* 0x2d8 */ gsys::BoneAccessKeyEx mSeatArm_Front;
    /* 0x310 */ gsys::BoneAccessKeyEx mSeatArm_Rear;
    /* 0x348 */ f32 _348 = -42.0f;
    /* 0x34c */ f32 _34c = 7.0f;
    /* 0x350 */ u64 _350 = 0;
    /* 0x358 */ u64 _358 = 0;
    /* 0x360 */ u64 _360 = 0;
    /* 0x368 */ u64 _368 = 0;
    /* 0x370 */ u32 _370 = 0;
    /* 0x374 */ f32 _374 = 1.0f;
    /* 0x378 */ f32 _378 = 1.0f;
    /* 0x37c */ f32 _37c = 1.0f;
    /* 0x380 */ u32 _380 = 0;
    /* 0x384 */ u8 _384 = 0;
    /* 0x388 */ sead::Vector3f _388 = sead::Vector3f::zero;
    /* 0x394 */ sead::Vector3f _394 = sead::Vector3f::zero;
    /* 0x3a0 */ sead::Matrix34f _3a0 = sead::Matrix34f::ident;
    /* 0x3d0 */ sead::Matrix34f _3d0 = sead::Matrix34f::ident;
    /* 0x400 */ sead::Matrix34f _400 = sead::Matrix34f::ident;
};
KSYS_CHECK_SIZE_NX150(MotorcycleStruct1, 0x430);

// Placeholder name following the CSV's MotorcycleStruct0 (size 0x58, at Motorcycle +0xd78): the engine
// sound / boost state (methods 0x710006f97c / 0x710006fbf8, not decompiled). It has no out-of-line
// constructor: the Motorcycle constructor initializes it inline.
struct MotorcycleStruct3 {
    explicit MotorcycleStruct3(ksys::act::Actor* actor) : _28(actor) {}

    // 0x710006fbf8 (not decompiled): `flag` is whether the boost is active.
    void sub_710006FBF8(bool flag);
    // 0x710006f97c (not decompiled)
    void sub_710006F97C(f32 speed, bool flag);

    /* 0x00 */ f32 _0 = 3850.0f;
    /* 0x04 */ f32 _4 = 5.0f;
    /* 0x08 */ f32 _8 = 200.0f;
    /* 0x0c */ f32 _c = 0.2f;
    /* 0x10 */ f32 _10 = 0.25f;
    /* 0x14 */ f32 _14 = 0.0f;
    /* 0x18 */ f32 _18 = 0.0f;
    /* 0x1c */ f32 _1c = 0.0f;
    /* 0x20 */ bool _20 = false;
    /* 0x21 */ bool _21 = false;
    /* 0x22 */ bool _22 = false;
    /* 0x23 */ bool _23 = false;
    /* 0x24 */ bool _24 = false;
    /* 0x28 */ ksys::act::Actor* _28;
    /* 0x30 */ aal::TimedFader _30{1.0f, aal::FadeCurveType::Linear, 1.0f};
};
KSYS_CHECK_SIZE_NX150(MotorcycleStruct3, 0x58);

// Unnamed contact callback (vtable 0x71023618f8, invoke 0x710007f930; clone / isNoDummy are the
// IDelegate2R defaults), three instances at Motorcycle +0x1628 / +0x1630 / +0x1638. Placeholder name =
// vtable address.
class Unk_71023618f8 : public ksys::phys::ContactPointInfo::ContactCallback {
public:
    bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                const ksys::phys::ContactPointInfo::Event& event) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023618f8, 8);

// Name from the CSV (Motorcycle::*). vtable 0x7102361318 (GOT 0x7102361328; 165 slots: DynamicActor's
// 163 + m163 / m164), RTTI static 0x71025af458 (parent: DynamicActor). ctor 0x710006fd9c (CSV
// Motorcycle::ctor), factory 0x710006ba58: new(0x1670). The 0x1670 bytes include the CSV
// MotorcycleStruct0 (ctor 0x710006bf34, at 0xbc8) and several aal::TimedFader members.
// TODO: incomplete (the ctor and most functions are not decompiled; member types are placeholders).
// Members are public: AI code reads them directly.
class Motorcycle : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(Motorcycle, ksys::act::DynamicActor)
public:
    explicit Motorcycle(const CreateArg& arg);
    // CSV Motorcycle::construct: the actor factory function.
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~Motorcycle() override;

protected:
    InitResult init_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;
    IsSpecialJobTypeResult isSpecialJobType_(ksys::act::JobType type) override;

public:
    void m44() override;
    ksys::phys::NavMeshCharacter* m45() override { return _1650; }
    bool shouldUnload(s32* a1) override;
    void initMaybe() override;
    void calcMaybe() override;
    void m70() override;
    void updatePositionMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void afterModelMatrixUpdate() override;
    bool m81(const ksys::Message& message) override;
    void updateMtxFromPhysics() override;
    void setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) override;
    void m88() override;
    void m117(ksys::act::Unk117* arg) override;
    Unk_7100e8b2b8* getMotorcyclePriorityStuffMaybe() override { return _1648; }

    // FIXME: figure out return types, parameters and names
    virtual f32 m163() { return _112c; }
    virtual void m164();

    // Non-virtual functions (CSV names where they exist; the placeholders `sub_<ADDR>` otherwise).
    // 0x710007a6fc: bit 11 of the flags.
    bool x_6() const;
    // 0x710007aa74: when _f10 is 5 or 6: _e00 divided by a constant (0x1da253c).
    f32 x_8() const;
    // 0x710007a948 / 0x710007f8e8: set flag bits 0x40000 / 0x800000.
    void x_11();
    void x_5();
    // 0x710007a84c / 0x710007a8cc: the stick objects (the X one also stores the value in _bb4).
    void setLeftStickX(f32 x);
    void setLeftStickY(f32 y);
    // 0x710007a88c: updates _10a4 (1 / 2) from the previous and the new acceleration.
    void setAccelMaybe(f32 accel);
    // 0x710007a8d4
    void crashMaybe(bool crash);
    // 0x71000711e0 (CSV Motorcycle::searchModelHandles): looks up the bones of _11b0.
    void searchModelHandles();
    // 0x710007b68c: the centre of mass of the main body (_bb8).
    void x_1(sead::Vector3f* center) const;
    // 0x710007a708: the y axis of the main body transform ((0, 1, 0) without a body).
    sead::Vector3f x_4() const;
    // 0x7100077830: switches the motion type of the main body and both wheels to Fixed (once).
    void sub_7100077830();
    // 0x7100071cb0: clears flag bit 24 and sets it again when a ray cast from the main body (starting
    // 1.2 above it, 2 along its z axis) hits the ground or an object.
    void sub_7100071CB0();
    // 0x71000769b4: restores the inertia of the main body and both wheels (_eec / _ef8 / _f04) when it
    // differs.
    void sub_71000769B4();
    // 0x7100072204: switches the motion type of the main body and both wheels back to Dynamic.
    void sub_7100072204();
    // 0x710007a798: stores a direction in _f70 (flattened to the XZ plane and normalized if it has a y
    // component) and sets flag bit 28.
    void sub_710007A798(const sead::Vector3f& direction);
    // 0x710007a4a8: 0 while flag bits 17 and 37 are both set, _e4c otherwise.
    f32 sub_710007A4A8() const;
    // 0x710007a6e8: flag bit 25 while bit 8 or 9 is set.
    bool sub_710007A6E8() const;
    // 0x710007a74c: stores `value` in _112c and sets _1128 (under the _10e8 lock).
    void sub_710007A74C(f32 value);
    // 0x710007a928 / 0x710007a938: set / clear flag bit 44, then x_7().
    void sub_710007A928();
    void sub_710007A938();
    // 0x710007f8f8 (declaration only; placeholder name): fades the bike sound out (aal::TimedFader at _1058),
    // called by MotorcycleDisappear::enter_.
    void sub_710007F8F8();
    // 0x7100071998 (declaration only; placeholder name): called by MotorcycleAppear::enter_ after the warp
    // effect starts.
    void sub_7100071998();
    // 0x710007a958 / 0x710007a994: _e74 / _e78 scaled into [-1, 1] (x 20 for the first).
    f32 sub_710007A958() const;
    f32 sub_710007A994() const;
    // 0x710007aba4: the current left stick Y value (_ba8._8) when _f10 is 1 or 3.
    f32 sub_710007ABA4() const;
    // 0x710007f868: the centre of mass of the main body.
    sead::Vector3f sub_710007F868() const;
    // 0x7100077fdc: places both wheels relative to `mtx` (0.474 above and 1.41 in front of / 0.7762 behind
    // the origin, mirrored) and resets their state.
    void x_12(const sead::Matrix34f& mtx);
    // 0x71000715d8 / 0x71000717b8 (not decompiled): both take two output vectors.
    void sub_71000715D8(sead::Vector3f* a, sead::Vector3f* b);
    void sub_71000717B8(sead::Vector3f* a, sead::Vector3f* b);
    // 0x7100070e48 (not decompiled)
    void x_7();
    // 0x7100072afc (CSV Motorcycle::x_18): drift / wheelie state (flag bits 14-17, 37).
    void x_18();
    // 0x710007d034 (placeholder name): starts a wheelie launch.
    void sub_710007D034();
    // 0x710007dab8 (placeholder name): fades the throttle sound handle (_10a8) and starts the sound
    // selected by _10a4 (1-5), then clears _10a4.
    void sub_710007DAB8();
    // 0x7100076018 (CSV Motorcycle::x_31): ray casts from both wheels towards the main body; counts how long
    // that hits something (_1640) and sets flag bit 35 after 30; returns whether it did.
    bool x_31();
    // 0x710007257c (CSV Motorcycle::x_15): damps the angular velocity of the main body around its x axis
    // (PitchDampingCoefficient).
    void applyPitchDamping();
    // 0x7100074d18 (CSV Motorcycle::x_26): applies a drag-like impulse to the main body (name is a guess).
    void applyDragMaybe();
    // 0x710007f894 (CSV Motorcycle::x_2): whether a wheel's ground material is `material`.
    bool isAnyWheelOnMaterial(ksys::phys::Material material) const;
    // 0x710007626c (CSV Motorcycle::x_3): whether the constraint of a wheel is active.
    bool isWheelConstraintActiveMaybe() const;
    // 0x71000778f8 (CSV Motorcycle::collisionStuff): whether `body` touches a body of the Player profile
    // named "Cleaning" or of an actor of the profile "SweepCollision". Does not use `this`.
    bool collisionStuff(ksys::phys::RigidBody* body);
    // 0x7100077890 (CSV Motorcycle::x): deletes the actor when a body of it collides (MotorcycleMgr).
    bool deleteIfColliding();
    // 0x710007a478: whether the acceleration and the global energy are positive.
    bool sub_710007A478() const;
    // 0x710007ab7c
    f32 sub_710007AB7C() const;
    // 0x710007c00c
    bool sub_710007C00C() const;
    // 0x7100072750 (CSV Motorcycle::x_17): the engine sound and acceleration; stores the value in
    // _bc8._0._48.
    void x_17();
    // 0x710007a9c8 (CSV Motorcycle::speedStuff): the stick value scaled by a speed curve, divided by 45 and
    // clamped to [-1, 1].
    f32 speedStuff();
    // 0x710007bf90 (CSV Motorcycle::speedStuff_1).
    f32 speedStuff_1();
    // 0x710007abc4 (not decompiled)
    // Not declared yet: x_4 0x710007a708 (the main body transform's y axis), x_2 0x710007f894 (takes a
    // SEAD_ENUM: compares the s32 at +0x110 of _dd0 / _dd8), x_1 / x_9 / x_0 ... (see the CSV).

    /* 0x0b90 */ Unk_71002c8918 _b90{0.5f, 0.1f, 0.0f};
    /* 0x0b9c */ Unk_7100e72ac0 _b9c{0.06f, 0.09f, 0.0f};  // left stick X
    /* 0x0ba8 */ Unk_7100e72ac0 _ba8{0.5f, 0.125f, 0.0f};  // left stick Y
    /* 0x0bb4 */ f32 _bb4 = 0.0f;
    /* 0x0bb8 */ ksys::phys::RigidBody* _bb8 = nullptr;
    /* 0x0bc0 */ ksys::phys::RigidBody* _bc0 = nullptr;
    /* 0x0bc8 */ MotorcycleStruct0 _bc8{this};
    /* 0x0d78 */ MotorcycleStruct3 _d78{this};
    /* 0x0dd0 */ MotorcycleStruct2* _dd0 = nullptr;
    /* 0x0dd8 */ MotorcycleStruct2* _dd8 = nullptr;
    /* 0x0de0 */ ksys::phys::Constraint* _de0 = nullptr;
    /* 0x0de8 */ ksys::phys::Constraint* _de8 = nullptr;
    /* 0x0df0 */ u64 _df0 = 0;
    /* 0x0df8 */ f32 _df8 = 3.0f;
    /* 0x0dfc */ f32 _dfc = 3.0f;
    /* 0x0e00 */ f32 _e00 = 0.0f;
    /* 0x0e04 */ sead::Vector3f _e04;
    /* 0x0e10 */ sead::Vector3f _e10;
    /* 0x0e1c */ sead::Vector3f _e1c;
    /* 0x0e28 */ sead::Vector3f _e28;
    /* 0x0e34 */ f32 _e34 = 0.846f;
    /* 0x0e38 */ f32 _e38 = 0.758f;
    /* 0x0e3c */ f32 _e3c = 0.0f;  // acceleration (setAccelMaybe)
    /* 0x0e40 */ f32 _e40 = 0.0f;
    /* 0x0e44 */ f32 _e44 = 1.0f;
    /* 0x0e48 */ f32 _e48 = 1.0f;
    /* 0x0e4c */ f32 _e4c = 0.0f;
    /* 0x0e50 */ f32 _e50 = 0.0f;
    /* 0x0e54 */ f32 _e54 = 0.0f;
    /* 0x0e58 */ f32 _e58 = 0.0f;
    /* 0x0e5c */ sead::Vector3f _e5c = sead::Vector3f::zero;
    /* 0x0e68 */ f32 _e68 = -256.0f;
    /* 0x0e6c */ f32 _e6c = 0.0f;
    /* 0x0e70 */ f32 _e70 = 0.0f;
    /* 0x0e74 */ f32 _e74 = 0.0f;
    /* 0x0e78 */ f32 _e78 = 0.0f;
    /* 0x0e7c */ f32 _e7c = 0.0f;
    /* 0x0e80 */ f32 _e80 = 0.0f;
    /* 0x0e84 */ f32 _e84 = 0.0f;
    /* 0x0e88 */ f32 _e88 = 0.0f;
    /* 0x0e8c */ Unk_71002c8e10 _e8c{0.35f, 0.0f, false};
    /* 0x0e98 */ sead::Vector3f _e98 = sead::Vector3f::zero;
    /* 0x0ea4 */ f32 _ea4 = 0.0f;
    /* 0x0ea8 */ f32 _ea8 = 0.0f;
    /* 0x0eac */ f32 _eac = 0.0f;
    /* 0x0eb0 */ f32 _eb0 = 0.0f;
    /* 0x0eb4 */ f32 _eb4 = 0.0f;
    /* 0x0eb8 */ f32 _eb8 = 0.0f;
    /* 0x0ebc */ f32 _ebc = 0.033f;
    /* 0x0ec0 */ f32 _ec0 = 1.0f;
    /* 0x0ec4 */ s32 _ec4 = 0;
    /* 0x0ec8 */ sead::Vector3f _ec8 = sead::Vector3f::zero;
    /* 0x0ed4 */ sead::Vector3f _ed4 = sead::Vector3f::zero;
    /* 0x0ee0 */ bool _ee0 = false;
    /* 0x0ee1 */ bool _ee1 = false;
    /* 0x0ee4 */ f32 _ee4 = 0.0f;
    /* 0x0ee8 */ f32 _ee8 = 0.0f;
    /* 0x0eec */ sead::Vector3f _eec = sead::Vector3f::zero;  // target inertia of the main body / the wheels
    /* 0x0ef8 */ sead::Vector3f _ef8 = sead::Vector3f::zero;
    /* 0x0f04 */ sead::Vector3f _f04 = sead::Vector3f::zero;
    /* 0x0f10 */ s32 _f10 = 0;
    /* 0x0f18 */ aal::TimedFader _f18{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x0f40 */ aal::TimedFader _f40{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x0f68 */ f32 _f68 = 0.0f;
    /* 0x0f6c */ f32 _f6c = 0.0f;
    /* 0x0f70 */ sead::Vector3f _f70 = sead::Vector3f::zero;
    /* 0x0f7c */ f32 _f7c = 0.0f;
    /* 0x0f80 */ bool _f80 = false;
    /* 0x0f88 */ sead::BitFlag64 _f88;
    /* 0x0f90 */ xlink2::Handle _f90;
    /* 0x0fa0 */ xlink2::Handle _fa0;
    /* 0x0fb0 */ xlink2::HandleSLink _fb0;
    /* 0x0fc0 */ xlink2::HandleSLink _fc0;
    /* 0x0fd0 */ xlink2::HandleSLink _fd0;
    /* 0x0fe0 */ xlink2::Handle _fe0;
    /* 0x0ff0 */ xlink2::Handle _ff0;
    /* 0x1000 */ xlink2::Handle _1000;
    /* 0x1010 */ xlink2::Handle _1010;
    /* 0x1020 */ xlink2::Handle _1020;
    /* 0x1030 */ xlink2::Handle _1030;
    /* 0x1040 */ f32 _1040 = 0.0f;
    /* 0x1044 */ f32 _1044 = 0.0f;
    /* 0x1048 */ f32 _1048 = 0.0f;
    /* 0x104c */ s16 _104c = 0;
    /* 0x104e */ s16 _104e = 0;
    /* 0x1050 */ f32 _1050 = 0.0f;
    /* 0x1058 */ aal::TimedFader _1058{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x1080 */ f32 _1080 = 0.0f;
    /* 0x1084 */ f32 _1084 = 0.0f;
    /* 0x1088 */ s32 _1088 = 0;
    /* 0x108c */ f32 _108c = 0.87f;
    /* 0x1090 */ f32 _1090 = 0.0f;
    /* 0x1094 */ f32 _1094 = 0.0f;
    /* 0x1098 */ f32 _1098 = 0.0f;
    /* 0x109c */ f32 _109c = 0.5f;
    /* 0x10a0 */ f32 _10a0 = 0.0f;
    /* 0x10a4 */ s32 _10a4 = 0;
    /* 0x10a8 */ xlink2::HandleSLink _10a8;
    /* 0x10b8 */ f32 _10b8 = 0.0f;
    /* 0x10c0 */ aal::TimedFader _10c0{1.0f, aal::FadeCurveType::Linear, 1.0f};
    /* 0x10e8 */ sead::CriticalSection _10e8;
    /* 0x1128 */ bool _1128 = false;
    /* 0x112c */ f32 _112c = 0.0f;
    /* 0x1130 */ u8 _1130[8];
    /* 0x1138 */ sead::Vector3f _1138{0.0f, 0.0f, 0.0f};
    /* 0x1144 */ u8 _1144[4];
    /* 0x1148 */ sead::Vector3f _1148{0.0f, 0.0f, 0.0f};
    /* 0x1154 */ u8 _1154[4];
    /* 0x1158 */ sead::Vector3f _1158{0.0f, 0.0f, 0.0f};
    /* 0x1164 */ u8 _1164[4];
    /* 0x1168 */ sead::Vector3f _1168{0.0f, 0.0f, 0.0f};
    /* 0x1174 */ u8 _1174[4];
    /* 0x1178 */ sead::Vector3f _1178 = sead::Vector3f::zero;
    /* 0x1184 */ f32 _1184 = 3.0f;
    /* 0x1188 */ f32 _1188 = 0.1f;
    /* 0x118c */ f32 _118c = 0.1f;
    /* 0x1190 */ bool _1190 = true;
    /* 0x1194 */ f32 _1194 = 525.0f;
    /* 0x1198 */ f32 _1198 = 630.0f;
    /* 0x119c */ f32 _119c = 1400.0f;
    /* 0x11a0 */ f32 _11a0 = 1680.0f;
    /* 0x11a4 */ f32 _11a4 = 0.03f;
    /* 0x11a8 */ f32 _11a8 = 0.06f;
    /* 0x11b0 */ MotorcycleStruct1 _11b0;
    /* 0x15e0 */ f32 _15e0 = 0.0f;
    /* 0x15e4 */ f32 _15e4 = 0.3f;
    /* 0x15e8 */ f32 _15e8 = 1.26f;
    /* 0x15ec */ f32 _15ec = 0.2f;
    /* 0x15f0 */ f32 _15f0 = 0.8f;
    /* 0x15f4 */ f32 _15f4 = 0.0f;
    /* 0x15f8 */ f32 _15f8 = 0.0f;
    /* 0x15fc */ bool _15fc = true;
    /* 0x15fd */ bool _15fd = false;
    /* 0x1600 */ f32 _1600 = 0.0f;
    /* 0x1604 */ u16 _1604 = 1;
    /* 0x1608 */ sead::Vector3f _1608 = sead::Vector3f::zero;
    /* 0x1618 */ void* _1618 = nullptr;
    /* 0x1620 */ u32 _1620 = 0;
    /* 0x1628 */ Unk_71023618f8 _1628;
    /* 0x1630 */ Unk_71023618f8 _1630;
    /* 0x1638 */ Unk_71023618f8 _1638;
    /* 0x1640 */ f32 _1640 = 0.0f;  // seconds (frames) the main body touched the ground (x_31)
    /* 0x1648 */ Unk_7100e8b2b8* _1648 = nullptr;
    /* 0x1650 */ ksys::phys::NavMeshCharacter* _1650 = nullptr;
    /* 0x1658 */ void* _1658 = nullptr;
    /* 0x1660 */ void* _1660 = nullptr;
    /* 0x1668 */ void* _1668 = nullptr;
};
KSYS_CHECK_SIZE_NX150(Motorcycle, 0x1670);

// 0x710006c810: the global motorcycle energy (MotorcycleMgr::mEnergy).
f32 getMotorcycleEnergy();

}  // namespace uking::act
