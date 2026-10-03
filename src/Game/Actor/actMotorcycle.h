#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "Game/Actor/actMotorcycleStickControl.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

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
    /* 0x018 */ u8 _18[0x110 - 0x18];
    /* 0x110 */ s32 _110;
    /* 0x114 */ u8 _114[0x148 - 0x114];
    /* 0x148 */ ksys::phys::Constraint* _148;
    /* 0x150 */ ksys::phys::Constraint* _150;
    /* 0x158 */ u8 _158[0x1b0 - 0x158];
};
KSYS_CHECK_SIZE_NX150(MotorcycleStruct2, 0x1b0);

// Placeholder name following the CSV's MotorcycleStruct0 (ctor 0x710007027c, size 0x430, at Motorcycle +
// 0x11b0): the model bones of the motorcycle (looked up by Motorcycle::searchModelHandles).
struct MotorcycleStruct1 {
    MotorcycleStruct1();

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
    void m117() override;
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
    // 0x710007a938 / 0x7100071998 (declaration only; placeholder names): called by
    // MotorcycleAppear::enter_ after the warp effect starts.
    // 0x710007a928 (declaration only; placeholder name): called by MotorcycleDisappear::calc_ when the
    // effect has finished.
    // 0x710007a74c (declaration only; placeholder name): called with the warp effect ratio by
    // BikeWarpEffectValueSetter.
    void sub_710007A74C(f32 value);
    void sub_710007A928();
    void sub_710007A938();
    // 0x710007f8f8 (declaration only; placeholder name): fades the bike sound out (aal::TimedFader at _1058),
    // called by MotorcycleDisappear::enter_.
    void sub_710007F8F8();
    void sub_7100071998();
    // 0x7100070e48 (not decompiled)
    void x_7();
    // 0x710007a9c8 / 0x710007abc4 / 0x710007bf90 (not decompiled)
    // Not declared yet: x_4 0x710007a708 (the main body transform's y axis), x_2 0x710007f894 (takes a
    // SEAD_ENUM: compares the s32 at +0x110 of _dd0 / _dd8), x_1 / x_9 / x_0 ... (see the CSV).

    /* 0x0b90 */ Unk_71002c8918 _b90;
    /* 0x0b9c */ Unk_7100e72ac0 _b9c;  // left stick X
    /* 0x0ba8 */ Unk_7100e72ac0 _ba8;  // left stick Y
    /* 0x0bb4 */ f32 _bb4;
    /* 0x0bb8 */ ksys::phys::RigidBody* _bb8;
    /* 0x0bc0 */ u8 _bc0[0xdd0 - 0xbc0];  // incl. MotorcycleStruct0 at 0xbc8
    /* 0x0dd0 */ MotorcycleStruct2* _dd0;
    /* 0x0dd8 */ MotorcycleStruct2* _dd8;
    /* 0x0de0 */ u8 _de0[0xdf0 - 0xde0];
    /* 0x0df0 */ u64 _df0;
    /* 0x0df8 */ u8 _df8[0xe00 - 0xdf8];
    /* 0x0e00 */ f32 _e00;
    /* 0x0e04 */ u8 _e04[0xe3c - 0xe04];
    /* 0x0e3c */ f32 _e3c;  // acceleration (setAccelMaybe)
    /* 0x0e40 */ f32 _e40;
    /* 0x0e44 */ u8 _e44[0xf10 - 0xe44];
    /* 0x0f10 */ s32 _f10;
    /* 0x0f14 */ u8 _f14[0xf70 - 0xf14];
    /* 0x0f70 */ sead::Vector3f _f70;
    /* 0x0f7c */ u8 _f7c[0xf80 - 0xf7c];
    /* 0x0f80 */ bool _f80;
    /* 0x0f81 */ u8 _f81[0xf88 - 0xf81];
    /* 0x0f88 */ sead::BitFlag64 _f88;
    /* 0x0f90 */ u8 _f90[0x10a4 - 0xf90];
    /* 0x10a4 */ s32 _10a4;
    /* 0x10a8 */ u8 _10a8[0x10e8 - 0x10a8];
    /* 0x10e8 */ sead::CriticalSection _10e8;
    /* 0x1128 */ bool _1128;
    /* 0x112c */ f32 _112c;
    /* 0x1130 */ u8 _1130[0x11b0 - 0x1130];
    /* 0x11b0 */ MotorcycleStruct1 _11b0;
    /* 0x15e0 */ u8 _15e0[0x1648 - 0x15e0];
    /* 0x1648 */ Unk_7100e8b2b8* _1648;
    /* 0x1650 */ ksys::phys::NavMeshCharacter* _1650;
    /* 0x1658 */ u8 _1658[0x1670 - 0x1658];
};
KSYS_CHECK_SIZE_NX150(Motorcycle, 0x1670);

}  // namespace uking::act
