#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SpeedEmitInterest : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SpeedEmitInterest, ksys::act::ai::Behavior)
public:
    explicit SpeedEmitInterest(const InitArg& arg);
    ~SpeedEmitInterest() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mLevel_s{};
    /* 0x30 */ const float* mSpeed_s{};
    /* 0x38 */ const bool* mIsTargetNPC_s{};
};
KSYS_CHECK_SIZE_NX150(SpeedEmitInterest, 0x40);

}  // namespace uking::behavior
