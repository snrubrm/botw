#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class HorseAttackBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(HorseAttackBehavior, ksys::act::ai::Behavior)
public:
    explicit HorseAttackBehavior(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x710062852c)
    void m9() override;  // not decompiled yet (0x7100628d68)
    ~HorseAttackBehavior() override;  // not decompiled yet

    /* 0x28 */ const float* mChargeAttackOffsetY_s{};
    /* 0x30 */ const bool* mIsRemovedAllAtkCollision_s{};
    /* 0x38 */ sead::SafeString mAtkCollisionName_s{};
    /* 0x48 */ gsys::BoneAccessKeyEx _48;
    /* 0x80 */ gsys::BoneAccessKeyEx _80;
    /* 0xb8 */ gsys::BoneAccessKeyEx _b8;
    /* 0xf0 */ gsys::BoneAccessKeyEx _f0;
    /* 0x128 */ u32 _128 = 0;
};
KSYS_CHECK_SIZE_NX150(HorseAttackBehavior, 0x130);

}  // namespace uking::behavior
