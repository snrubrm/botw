#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class LynelGearAttackCollision : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(LynelGearAttackCollision, ksys::act::ai::Behavior)
public:
    explicit LynelGearAttackCollision(const InitArg& arg);
    ~LynelGearAttackCollision() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mAttackIntensity_s{};
    /* 0x30 */ const float* mDamageScaleGear0_s{};
    /* 0x38 */ const float* mDamageScaleGear1_s{};
    /* 0x40 */ const float* mDamageScaleGear2_s{};
    /* 0x48 */ const float* mDamageScaleGear3_s{};
    /* 0x50 */ const float* mDamageScaleGearTop_s{};
    /* 0x58 */ const bool* mIsGuardPierce_s{};
    /* 0x60 */ const bool* mIsForceGuardBreak_s{};
    /* 0x68 */ const bool* mIsIniviciblePierce_s{};
    /* 0x70 */ sead::SafeString mAttackRigidName_s{};
    /* 0x80 */ f32 _80 = 0;
    /* 0x84 */ f32 _84 = 0;
    /* 0x88 */ f32 _88 = 0;
    /* 0x8c */ u32 _8c = 0;
    /* 0x90 */ bool _90 = false;
};
KSYS_CHECK_SIZE_NX150(LynelGearAttackCollision, 0x98);

}  // namespace uking::behavior
