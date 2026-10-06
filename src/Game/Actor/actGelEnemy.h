#pragma once

#include <container/seadBuffer.h>
#include <limits>
#include <math/seadVector.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::act {

// Name from the CSV (GelEnemy::*): Chuchus. vtable 0x7102358e58 (181 slots, no new virtuals), RTTI
// static 0x71025af0a0 (parent: Enemy). Factory 0x7100025074 (CSV GelEnemy::construct, which inlines
// the ctor): new(0x1680).
// TODO: incomplete. Members are public: AI code reads them directly.
class GelEnemy : public Enemy {
    SEAD_RTTI_OVERRIDE(GelEnemy, Enemy)
public:
    explicit GelEnemy(const CreateArg& arg);
    // CSV GelEnemy::construct: the actor factory function.
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
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

    // Non-virtual functions of the TU (declared only; placeholder names). 0x7100026b00 is called by
    // m76; 0x7100026240 / 0x7100028128 by m79.
    void sub_7100026B00();
    void sub_7100026240();
    bool sub_7100028128();

    // 0x71000269c8 / 0x7100026a38 (declared only): set / clear bit 8 of the flag word at +0x18 of every
    // element (stride 0x40) of the physics sub-object's array at +0xd8 (the Gel's sensors).
    void sub_71000269C8();
    void sub_7100026A38();
    // lane4 s46 (placeholder names): 0x7100026aa8 / 0x7100026ad4: `_1620.x` = the GelEnemy param EyeUpMoveRate /
    // EyeDownMoveRate.
    void sub_7100026AA8();
    void sub_7100026AD4();

    // inline-only in the original; name is a guess: the loop over the model units that tests the
    // unit's `_50` vector for NaN and calls nullsub_4649() (a discarded call that is in the asm). It
    // is repeated in calcMaybe, updatePositionMaybe, m74, m76 and twice in m79.
    void checkModelUnitsNaN() {
        for (int i = 0; i < mModel->getUnits().size(); ++i) {
            if (mModel->getUnits()(i)->mModelUnit->get50()->isNan())
                nullsub_4649();
        }
    }

    // BoneHandle (ctor 0x7100d3b3f0; the jump/pre-attack actions write its 0x68 / 0x78 / 0x88)
    /* 0x14c8 */ ksys::act::BoneHandle _14c8;
    // Element of _1668 (0xb0 bytes; only the BoneAccessKeyEx at +0x68 has a destructor). Placeholder.
    struct Unk1668 {
        u8 _0[0x68];
        gsys::BoneAccessKeyEx _68;
        u8 _a0[0x10];
    };
    KSYS_CHECK_SIZE_NX150(Unk1668, 0xb0);

    // Bones searched by initMaybe: the body root and the left / right eye (GelEnemy GParamList)
    /* 0x1570 */ gsys::BoneAccessKeyEx _1570;
    /* 0x15a8 */ gsys::BoneAccessKeyEx _15a8;
    /* 0x15e0 */ gsys::BoneAccessKeyEx _15e0;
    /* 0x1618 */ void* _1618 = nullptr;
    /* 0x1620 */ sead::Vector3f _1620{1.0f, 1.0f, 0.0f};
    /* 0x162c */ sead::Vector3f _162c = sead::Vector3f::zero;
    /* 0x1638 */ sead::Vector3f _1638 = sead::Vector3f::zero;
    /* 0x1644 */ f32 _1644[6]{std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN(),
                              std::numeric_limits<f32>::quiet_NaN()};
    /* 0x165c */ f32 _165c = 0;
    /* 0x1660 */ f32 _1660 = 0;
    /* 0x1664 */ f32 _1664 = 0;
    // Freed by preDelete2_ (the ctor zeroes it; nothing allocates it in this class)
    /* 0x1668 */ sead::Buffer<Unk1668> _1668;
    /* 0x1678 */ u8 _1678 = 0;  // flags (~40 AI accesses)
};
KSYS_CHECK_SIZE_NX150(GelEnemy, 0x1680);

}  // namespace uking::act
