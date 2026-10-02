#pragma once

#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"

namespace uking::act {

// Name from the CSV (GelEnemy::*): Chuchus. vtable 0x7102358e58 (181 slots, no new virtuals), RTTI
// static 0x71025af0a0 (parent: Enemy). Factory 0x7100025074 (CSV GelEnemy::construct, which inlines
// the ctor): new(0x1680).
// TODO: incomplete. Members are public: AI code reads them directly.
class GelEnemy : public Enemy {
    SEAD_RTTI_OVERRIDE(GelEnemy, Enemy)
public:
    explicit GelEnemy(const CreateArg& arg);
    ~GelEnemy() override;

protected:
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m74() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void afterModelMatrixUpdate() override;
    void m79() override;
    bool m81(const ksys::Message& message) override;

    // BoneHandle (ctor 0x7100d3b3f0; the jump/pre-attack actions write its 0x68 / 0x78 / 0x88)
    /* 0x14c8 */ u8 _14c8[0x1570 - 0x14c8];
    // three gsys::BoneAccessKeyEx
    /* 0x1570 */ u8 _1570[0x1618 - 0x1570];
    /* 0x1618 */ void* _1618 = nullptr;
    /* 0x1620 */ sead::Vector3f _1620{1.0f, 1.0f, 0.0f};
    /* 0x162c */ sead::Vector3f _162c = sead::Vector3f::zero;
    /* 0x1638 */ sead::Vector3f _1638 = sead::Vector3f::zero;
    /* 0x1644 */ f32 _1644[6];  // = NaN (quiet) by the ctor
    /* 0x165c */ u64 _165c = 0;
    /* 0x1664 */ u64 _1664 = 0;
    /* 0x1670 */ void* _1670 = nullptr;
    /* 0x1678 */ u8 _1678 = 0;  // flags (~40 AI accesses)
};
KSYS_CHECK_SIZE_NX150(GelEnemy, 0x1680);

}  // namespace uking::act
