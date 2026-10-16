#pragma once

#include <gsys/gsysModelAccessKey.h>
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

    // 0x71002cd930 (96 B, not decompiled; placeholder name, lane4 s85): writes `pos` into the 15 entries of the
    // object at +0x1588 (called by SandwormTeraPach::m8).
    void sub_71002CD930(const sead::Vector3f& pos);
    // 0x71002cd990 (80 B, not decompiled; placeholder name): called by SandwormTeraPach::m7 with the blended
    // node position.
    void sub_71002CD990(const sead::Vector3f& pos);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void killWithDropsAndEffects(int a1) override;
    // 0x71002cdb48 (CSV Sandworm::kill_; declared only).
    void sub_71002CDB48();
    // 0x71002cdde8 (unnamed in the CSV; declared only; SandwormRoot::calc_): with an active character controller,
    // moves the position at +0x1644 towards the actor (distance < 30, height difference < 15) via 0x710072fbd4.
    void sub_71002CDDE8();
    // Declaration only.
    void sub_71002CDAE4(bool on);
    // 0x71002ce2c8 (unnamed in the CSV; same shape as GiantEnemy::setNecklaceFlag, but another tag (hash 0x12ad8456, name
    // unknown) and it passes index + 1).
    void setNecklaceFlag(s32 index);
    void m56(sead::Vector3f* pos) override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message& message) override;
    bool m146() override;
    bool weaponDroppedByEnemy() override;
    // 0x71002cdfcc: creates an 8-byte Unk_710001adbc subclass (vtable GOT 0x7102584830) from `heap`. Body not
    // written: the class is undefined.
    Unk_710001adbc* m179(sead::Heap* heap) override;

    /* 0x14c8 */ s32 _14c8 = 2;
    /* 0x14cc */ s32 _14cc = 2;
    /* 0x14d0 */ void* _14d0 = nullptr;
    /* 0x14d8 */ gsys::BoneAccessKeyEx _14d8;
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
    /* 0x1590 */ ksys::VFRValue _1590{0.0f};
    /* 0x159c */ f32 _159c = 0;
    /* 0x15a0 */ u32 _15a0 = 0;
    /* 0x15a4 */ u32 _15a4 = 0;
    /* 0x15a8 */ u32 _15a8 = 0;
    /* 0x15ac */ f32 _15ac = 0;  // sand offset speed (SandwormASPlay)
    /* 0x15b0 */ f32 _15b0 = 0;  // target sand offset (SandwormASPlay)
    /* 0x15b4 */ u32 _15b4;
    /* 0x15b8 */ gsys::BoneAccessKeyEx _15b8;
    /* 0x15f0 */ gsys::BoneAccessKeyEx _15f0;
    /* 0x1628 */ sead::Random _1628;
    /* 0x1638 */ u8 _1638 = 0;
    /* 0x163c */ u32 _163c = 0;
    /* 0x1640 */ u32 _1640 = 0;
    /* 0x1644 */ sead::Vector3f _1644 = sead::Vector3f::zero;
    /* 0x1650 */ ksys::phys::RigidBody* _1650 = nullptr;  // m56
};
KSYS_CHECK_SIZE_NX150(Sandworm, 0x1658);

}  // namespace uking::act
