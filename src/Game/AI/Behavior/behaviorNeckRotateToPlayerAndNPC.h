#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::behavior {

class NeckRotateToPlayerAndNPC : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(NeckRotateToPlayerAndNPC, ksys::act::ai::Behavior)
public:
    explicit NeckRotateToPlayerAndNPC(const InitArg& arg);
    ~NeckRotateToPlayerAndNPC() override;
    bool m6(sead::Heap* heap) override;
    void m9() override;
    void loadParams() override;
    void m7() override;
    void m8() override;

    // 0x710062d70c (not decompiled): picks the nearest player / NPC within the limit distance and angle.
    void sub_710062D70C();

    /* 0x28 */ const int* mUpdateInterval_s{};
    /* 0x30 */ const float* mLimitDistance_s{};
    /* 0x38 */ const float* mLimitAngle_s{};
    /* 0x40 */ const bool* mIsUseAwnSight_s{};
    /* 0x48 */ ksys::act::BaseProcLink _48;
    /* 0x58 */ ksys::Timer _58;
};
KSYS_CHECK_SIZE_NX150(NeckRotateToPlayerAndNPC, 0x68);

}  // namespace uking::behavior
