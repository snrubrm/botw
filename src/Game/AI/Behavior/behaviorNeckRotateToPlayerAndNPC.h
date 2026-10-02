#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
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
    void m7() override;  // not decompiled yet (0x710062da58)
    void m8() override;  // not decompiled yet (0x710062d6d0)

    /* 0x28 */ const int* mUpdateInterval_s{};
    /* 0x30 */ const float* mLimitDistance_s{};
    /* 0x38 */ const float* mLimitAngle_s{};
    /* 0x40 */ const bool* mIsUseAwnSight_s{};
    /* 0x48 */ ksys::act::BaseProcLink _48;
    /* 0x58 */ void* _58 = nullptr;
    /* 0x60 */ u32 _60 = 0;
};
KSYS_CHECK_SIZE_NX150(NeckRotateToPlayerAndNPC, 0x68);

}  // namespace uking::behavior
