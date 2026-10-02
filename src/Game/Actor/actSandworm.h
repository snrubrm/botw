#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <random/seadRandom.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace uking::act {

// Name from the CSV (Sandworm::*): Molduga / Molduking. vtable 0x71023cf6d8 (181 slots, no new
// virtuals), RTTI static 0x71025b5838 (parent: Enemy). Factory 0x71002cbadc (CSV Sandworm::construct,
// which inlines the ctor): new(0x1658).
// TODO: incomplete. Members are public: AI code reads them directly.
class Sandworm : public Enemy {
    SEAD_RTTI_OVERRIDE(Sandworm, Enemy)
public:
    explicit Sandworm(const CreateArg& arg);
    ~Sandworm() override;

protected:
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void killWithDropsAndEffects(int a1) override;
    bool m56(sead::Vector3f* pos) override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message& message) override;
    bool m146() override;
    bool weaponDroppedByEnemy() override;
    // Not declared: slot 179 (creates an 8-byte object with vtable GOT 0x7102584830 from a heap;
    // Enemy declares `void m179()`).

    /* 0x14c8 */ s32 _14c8 = 2;
    /* 0x14cc */ s32 _14cc = 2;
    /* 0x14d0 */ void* _14d0 = nullptr;
    /* 0x14d8 */ u8 _14d8[0x1510 - 0x14d8];  // gsys::BoneAccessKeyEx
    /* 0x1510 */ u32 _1510 = 0;
    /* 0x1518 */ void* _1518 = nullptr;
    /* 0x1520 */ u32 _1520 = 0;
    /* 0x1528 */ void* _1528 = nullptr;
    /* 0x1530 */ void* _1530 = nullptr;
    /* 0x1538 */ f32 _1538 = 0.05;
    /* 0x153c */ u32 _153c = 0;
    /* 0x1540 */ u32 _1540 = 0;
    /* 0x1548 */ void* _1548 = nullptr;
    /* 0x1550 */ sead::Matrix34f _1550 = sead::Matrix34f::ident;
    /* 0x1580 */ f32 _1580 = 3.0;
    /* 0x1584 */ u8 _1584 = 0;
    /* 0x1588 */ void* _1588 = nullptr;
    /* 0x1590 */ ksys::VFRValue _1590;
    /* 0x159c */ u32 _159c = 0;
    /* 0x15a0 */ u32 _15a0 = 0;
    /* 0x15a4 */ u32 _15a4 = 0;
    /* 0x15a8 */ u32 _15a8 = 0;
    /* 0x15ac */ u32 _15ac = 0;
    /* 0x15b0 */ u32 _15b0;
    /* 0x15b8 */ u8 _15b8[0x1628 - 0x15b8];  // two gsys::BoneAccessKeyEx
    /* 0x1628 */ sead::Random _1628;
    /* 0x1638 */ u8 _1638 = 0;
    /* 0x163c */ u32 _163c = 0;
    /* 0x1640 */ u32 _1640 = 0;
    /* 0x1644 */ sead::Vector3f _1644;
    /* 0x1650 */ ksys::phys::RigidBody* _1650 = nullptr;  // m56
};
KSYS_CHECK_SIZE_NX150(Sandworm, 0x1658);

}  // namespace uking::act
