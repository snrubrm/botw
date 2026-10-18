#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class SystemGroupHandler;
class Unk_71024f67c8;
}

namespace ksys::act {

// RTTI base class with vtable 0x71024eed28: D1 0x7100e9cf28 (empty), D0 0x7100e9cf2c,
// checkDerivedRuntimeTypeInfo 0x7100e9d414, getRuntimeTypeInfo 0x7100e9d484, m4 / m5 empty
// (0x7100e9d4e0 / 0x7100e9d4e4). Constructor 0x7100e9ceec; derived 0x108-byte objects are created by
// 0x710002da1c and held at Enemy + 0x12d8; Player / Enemy / NPC::m146 call sub_7100E9CF3C.
class Unk_71024eed28 {
public:
    explicit Unk_71024eed28(s32 a);
    // Declared before the RTTI functions: the destructor takes the first vtable slots.
    virtual ~Unk_71024eed28() = default;

    SEAD_RTTI_BASE(Unk_71024eed28)
public:

    virtual void m4() {}
    // Arguments from sub_7100E9CF3C, which forwards its own (`handler`: Enemy::m146 passes the first entry of
    // InstanceSet::_188).
    virtual void m5(const sead::Matrix34f& mtx, bool flag, f32 value, phys::SystemGroupHandler* handler) {}

    // 0x7100e9cf3c (placeholder name): when sUnk_71024eed20 is set, stores the translation of `mtx` in _20
    // and calls m5.
    void sub_7100E9CF3C(const sead::Matrix34f& mtx, bool flag, f32 value,
                        phys::SystemGroupHandler* handler);

    /* 0x08 */ s32 _8;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ void* _18 = nullptr;
    /* 0x20 */ sead::Vector3f _20 = sead::Vector3f::zero;
    /* 0x30 */ void* _30 = nullptr;
    /* 0x38 */ bool _38 = false;
    // Never accessed; the two 0xf0-byte / 0x108-byte derived children start their own fields at 0x40,
    // so the base's last member reaches 0x40 (the constructor only initialises _38).
    /* 0x39 */ u8 _39[7];
};
KSYS_CHECK_SIZE_NX150(Unk_71024eed28, 0x40);

// Placeholder name (vtable 0x7102359478; its RTTI static object is 0x71025af0d0, initialised with the
// Derive<Unk_71024eed28> vtable at 0x71023594b8). The 0xf0-byte child at GiantEnemy::_1558 + 0x10:
// created by 0x7100028c20 (called by the holder init 0x710002da1c) and filled by its init
// 0x7100028cf0, which creates a phys::Unk_71024f67c8 from the arg's bone data ("Skl_Root", "Waist",
// "Leg_1_L/R", "Ankle_L/R", "Arm_1_L/R", "Arm_2_L/R", "Wrist_L/R"). GiantEnemy::m119 and the
// PullOut / GiantDoubleGroundPunch actions reach it through the holder's slot-7 getter (m7).
// Fields from the factory's initialisation stores. Members are public: AI code reads them directly.
class Unk_7102359478 : public Unk_71024eed28 {
    SEAD_RTTI_OVERRIDE(Unk_7102359478, Unk_71024eed28)
public:
    ~Unk_7102359478() override;  // D1 0x7100028fd8, D0 0x7100029048; declared only.
    void m4() override;          // 0x7100028e28 (104 B); declared only.
    void m5(const sead::Matrix34f& mtx, bool flag, f32 value,
            phys::SystemGroupHandler* handler) override;  // 0x7100028e90 (328 B); declared only.

    /* 0x40 */ u8 _40 = 0;  // GiantDoubleGroundPunch keeps only the upper 6 bits (& 0xfc)
    /* 0x41 */ u8 _41[3] = {};
    /* 0x44 */ u32 _44 = 0;
    /* 0x48 */ u32 _48 = 0;
    /* 0x4c */ u32 _4c = 0;
    /* 0x50 */ u32 _50 = 0;
    /* 0x54 */ f32 _54 = 1.0f;
    /* 0x58 */ void* _58 = nullptr;
    /* 0x60 */ ksys::phys::Unk_71024f67c8* _60 = nullptr;  // created by the init 0x7100028cf0
    /* 0x68 */ u64 _68[3] = {};
    /* 0x80 */ void* _80 = nullptr;
    /* 0x88 */ void* _88 = nullptr;
    /* 0x90 */ u32 _90 = 0;
    /* 0x94 */ u32 _94;  // not initialised by the factory
    /* 0x98 */ u8 _98 = 0;  // flag byte; PullOut sets its bit 0 before writing _9c / _c8 / _d4
    /* 0x9c */ u32 _9c = 0;
    /* 0xa0 */ u32 _a0 = 0;
    /* 0xa4 */ u32 _a4 = 0;
    /* 0xa8 */ u32 _a8 = 0;
    /* 0xac */ f32 _ac = 1.0f;
    /* 0xb0 */ void* _b0 = nullptr;
    /* 0xb8 */ u64 _b8[2] = {};
    /* 0xc8 */ sead::Vector3f _c8 = sead::Vector3f::zero;
    /* 0xd4 */ sead::Vector3f _d4 = sead::Vector3f::zero;
    /* 0xe0 */ u32 _e0 = 0;
    /* 0xe4 */ u32 _e4 = 0;
    /* 0xe8 */ u32 _e8 = 0;
    /* 0xec */ u8 _ec[4];  // not initialised by the factory
};
KSYS_CHECK_SIZE_NX150(Unk_7102359478, 0xf0);

}  // namespace ksys::act
