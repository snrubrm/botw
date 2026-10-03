#pragma once

#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::act {

class Unk_7100e8b2b8;

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
    bool shouldUnload() override;
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

    /* 0x0b90 */ u8 _b90[0xb9c - 0xb90];
    /* 0x0b9c */ u8 _b9c[0xbb4 - 0xb9c];  // left stick X / Y (motorcycleStickControlStuff objects at 0xb9c / 0xba8)
    /* 0x0bb4 */ f32 _bb4;
    /* 0x0bb8 */ ksys::phys::RigidBody* _bb8;
    /* 0x0bc0 */ u8 _bc0[0xdd0 - 0xbc0];  // incl. MotorcycleStruct0 at 0xbc8
    /* 0x0dd0 */ void* _dd0;
    /* 0x0dd8 */ void* _dd8;
    /* 0x0de0 */ u8 _de0[0xdf0 - 0xde0];
    /* 0x0df0 */ u64 _df0;
    /* 0x0df8 */ u8 _df8[0xe00 - 0xdf8];
    /* 0x0e00 */ f32 _e00;
    /* 0x0e04 */ u8 _e04[0xe3c - 0xe04];
    /* 0x0e3c */ f32 _e3c;  // acceleration (setAccelMaybe)
    /* 0x0e40 */ f32 _e40;
    /* 0x0e44 */ u8 _e44[0xf10 - 0xe44];
    /* 0x0f10 */ s32 _f10;
    /* 0x0f14 */ u8 _f14[0xf88 - 0xf14];
    /* 0x0f88 */ sead::BitFlag64 _f88;
    /* 0x0f90 */ u8 _f90[0x10a4 - 0xf90];
    /* 0x10a4 */ s32 _10a4;
    /* 0x10a8 */ u8 _10a8[0x112c - 0x10a8];
    /* 0x112c */ f32 _112c;
    /* 0x1130 */ u8 _1130[0x1648 - 0x1130];
    /* 0x1648 */ Unk_7100e8b2b8* _1648;
    /* 0x1650 */ ksys::phys::NavMeshCharacter* _1650;
    /* 0x1658 */ u8 _1658[0x1670 - 0x1658];
};
KSYS_CHECK_SIZE_NX150(Motorcycle, 0x1670);

}  // namespace uking::act
